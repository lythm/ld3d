#include "core_pch.h"
#include "..\..\include\core\RenderManager.h"
#include "core\RenderData.h"
#include "core\Sys_Graphics.h"
#include "core\Material.h"
#include "core\g_format.h"
#include "core\RenderTarget.h"
#include "core_utils.h"
#include "core\GPUBuffer.h"
#include "core\LightManager.h"
#include "core\Light.h"
#include "core\PostEffectManager.h"
#include "core\Camera.h"
#include "core\Event.h"

namespace ld3d
{
	RenderManager::RenderManager(void)
	{
		m_viewMatrix.MakeIdentity();
		m_projMatrix.MakeIdentity();

		m_clearClr						= math::Color4(0.0f, 0.2f, 0.3f, 1.0f);
		m_clearDepth					= 1.0f;
		m_clearStencil					= 0;
		m_globalAmbientColor			= math::Color4(0.3f, 0.3f, 0.3f, 1.0f);

	}


	RenderManager::~RenderManager(void)
	{
	}

	bool RenderManager::Initialize(Sys_GraphicsPtr pGraphics, EventDispatcherPtr pED)
	{
		m_pGraphics = pGraphics;
		m_pEventDispatcher = pED;

		int w = pGraphics->GetFrameBufferWidth();
		int h = pGraphics->GetFrameBufferHeight();

		if(false == CreateGBuffer(w, h))
		{
			return false;
		}
		if(false == CreateABuffer(w, h))
		{
			return false;
		}

		m_pScreenQuad = alloc_object<ScreenQuad>();
		if(m_pScreenQuad->Init(m_pGraphics) == false)
		{
			return false;
		}

		m_pLightManager = alloc_object<LightManager>();
		if(m_pLightManager->Initialize(shared_from_this()) == false)
		{
			return false;
		}

		m_pPostEffectManager = alloc_object<PostEffectManager>();
		if(m_pPostEffectManager->Initialize(shared_from_this()) == false)
		{
			return false;
		}

		m_pScreenQuadMaterial = pGraphics->CreateMaterialFromFile("./assets/standard/material/dr_render_merge.fx");

		VertexElement vf[] = 
		{
			VertexElement(0, VertexElement::POSITION,G_FORMAT_R32G32B32_FLOAT),
		};
		VertexFormat format;

		format.SetElement(vf, 1);

		m_pScreenQuadMaterial->SetVertexFormat(format);

		
		return true;
	}
	bool RenderManager::CreateGBuffer(int w, int h)
	{
		if(m_pGBuffer != nullptr)
		{
			m_pGBuffer->Release();
			m_pGBuffer.reset();
		}

		G_FORMAT formats[3] = 
		{
			G_FORMAT_R32_FLOAT,					// depth
			G_FORMAT_R16G16_FLOAT,				// normal.xy
			G_FORMAT_R8G8B8A8_UNORM,			// diffuse color : specular
		};

		m_pGBuffer = CreateRenderTarget(3, w, h, formats);

		return true;

	}
	void RenderManager::Release()
	{
		Clear();

		if(m_pScreenQuadMaterial)
		{
			m_pScreenQuadMaterial->Release();
			m_pScreenQuadMaterial.reset();
		}
		if(m_pLightManager)
		{
			m_pLightManager->Release();
			m_pLightManager.reset();
		}

		if(m_pPostEffectManager)
		{
			m_pPostEffectManager->Release();
			m_pPostEffectManager.reset();
		}
		if(m_pScreenQuad)
		{
			m_pScreenQuad->Release();
			m_pScreenQuad.reset();
		}
		if(m_pGBuffer != nullptr)
		{
			m_pGBuffer->Release();
			m_pGBuffer.reset();
		}
		if(m_pABuffer != nullptr)
		{
			m_pABuffer->Release();
			m_pABuffer.reset();
		}
	}

	void RenderManager::AddRenderData(RenderDataPtr pData)
	{
		if(pData->IsDeferred())
		{
			m_deferredQueue.push_back(pData);
		}
		else
		{
			m_forwardQueue.push_back(pData);
		}
	}
	void RenderManager::Clear()
	{
		m_forwardQueue.clear();
		m_deferredQueue.clear();
		m_transparentQueue.clear();
	}
	void RenderManager::DR_G_Pass()
	{
		m_pGraphics->SetRenderTarget(m_pGBuffer);
		m_pGraphics->ClearRenderTarget(m_pGBuffer, 0, math::Color4(0, 0, 0, 1));
		m_pGraphics->ClearRenderTarget(m_pGBuffer, 1, math::Color4(0, 0, 0, 0));
		m_pGraphics->ClearRenderTarget(m_pGBuffer, 2, math::Color4(0, 0, 0, 1));
		m_pGraphics->ClearDepthStencilBuffer(DepthStencilBufferPtr(), CLEAR_ALL, 1.0f, 0);


		for(size_t i = 0; i < m_deferredQueue.size(); ++i)
		{
			SetSemanticsValue(m_deferredQueue[i]);
			
			m_deferredQueue[i]->Render(m_pGraphics);
		}
	}
	void RenderManager::DR_Merge_Pass()
	{
		RenderTargetPtr pOutput = m_pPostEffectManager->GetInput();

		m_pGraphics->SetRenderTarget(pOutput);
		m_pGraphics->ClearRenderTarget(pOutput, 0, m_clearClr);

		m_pScreenQuadMaterial->SetGBuffer(m_pGBuffer);
		m_pScreenQuadMaterial->SetABuffer(m_pABuffer);
		m_pScreenQuadMaterial->SetProjMatrix(m_projMatrix);
		m_pScreenQuadMaterial->SetViewMatrix(m_viewMatrix);
		m_pScreenQuadMaterial->SetWorldMatrix(math::MatrixIdentity());

		DrawFullScreenQuad(m_pScreenQuadMaterial);
	}
	void RenderManager::RenderForward()
	{
		for(size_t i = 0; i < m_forwardQueue.size(); ++i)
		{
			SetSemanticsValue(m_forwardQueue[i]);
			
			m_forwardQueue[i]->Render(m_pGraphics);
		}

		for(size_t i = 0; i < m_transparentQueue.size(); ++i)
		{
			SetSemanticsValue(m_transparentQueue[i]);
			
			m_transparentQueue[i]->Render(m_pGraphics);
		}
	}
	void RenderManager::Render(const math::Matrix44& view, const math::Matrix44& proj)
	{
		SetViewMatrix(view);
		SetProjMatrix(proj);

		DR_G_Pass();
		DR_Light_Pass();
		DR_Merge_Pass();
		
		RenderForward();

		RenderPostEffects();
		
		RenderFinal();
	}
	void RenderManager::Render(CameraPtr pCamera)
	{

		pCamera->UpdateViewFrustum();

		boost::shared_ptr<Event_FrustumCull> pEvent = alloc_object<Event_FrustumCull, BaseCameraPtr>(pCamera);
			
		m_pEventDispatcher->DispatchEvent(pEvent);


		RenderShadowMaps();

		Render(pCamera->GetViewMatrix(), pCamera->GetProjMatrix());

	}
	void RenderManager::Render()
	{
		m_cameras.sort(Camera::SortFunction);

		std::list<CameraPtr>::iterator it = m_cameras.begin();
		for(it; it != m_cameras.end(); ++it)
		{
			Render(*it);
		}
	}
	void RenderManager::Present()
	{
		m_pGraphics->Present();
	}
	void RenderManager::SetViewMatrix(const math::Matrix44& view)
	{
		m_viewMatrix = view;
	}
	void RenderManager::SetProjMatrix(const math::Matrix44& proj)
	{
		m_projMatrix = proj;
	}
	void RenderManager::SetSemanticsValue(RenderDataPtr pData)
	{
		MaterialPtr pMaterial = pData->GetMaterial();
		math::Matrix44 world = pData->GetWorldMatrix();
		pMaterial->SetProjMatrix(m_projMatrix);
		pMaterial->SetViewMatrix(m_viewMatrix);
		pMaterial->SetWorldMatrix(world);
	}
	Sys_GraphicsPtr	RenderManager::GetSysGraphics()
	{
		return m_pGraphics;
	}
	void RenderManager::SetClearColor(const math::Color4& clr)
	{
		m_clearClr	 = clr;
	}
	const math::Color4&	RenderManager::GetClearColor()
	{
		return m_clearClr;
	}
	void RenderManager::SetClearDepth(float d)
	{
		m_clearDepth = d;
	}
	void RenderManager::SetClearStencil(int s)
	{
		m_clearStencil = s;
	}
	void RenderManager::ResizeFrameBuffer(int cx, int cy)
	{
		if(cx == 0 || cy == 0)
		{
			return;
		}

		m_pGraphics->SetRenderTarget(ld3d::RenderTargetPtr());

		m_pGraphics->ResizeFrameBuffer(cx, cy);
		

		CreateGBuffer(cx, cy);
		CreateABuffer(cx, cy);

		m_pPostEffectManager->Resize(cx, cy);
	}
	void RenderManager::AddLight(LightPtr pLight)
	{
		m_pLightManager->AddLight(pLight);
	}
	void RenderManager::RemoveLight(LightPtr pLight)
	{
		m_pLightManager->RemoveLight(pLight);
	}
	int	RenderManager::GetLightCount()
	{
		return m_pLightManager->GetLightCount();
	}
	
	void RenderManager::DR_Light_Pass()
	{
		m_pGraphics->SetRenderTarget(m_pABuffer);

		math::Color4 clr = m_globalAmbientColor;
		clr.a = 0;

		m_pGraphics->ClearRenderTarget(m_pABuffer, 0, clr);

		m_pLightManager->RenderLights();
	}
	void RenderManager::RenderShadowMaps()
	{
		LightPtr pLight = m_pLightManager->GetNextAffectingLight(LightPtr(), ViewFrustum());
		while(pLight)
		{
			if(pLight->GetCastShadow() == true)
			{
				pLight->RenderShadowMap();
			}
			pLight = m_pLightManager->GetNextAffectingLight(pLight, ViewFrustum());
		}
	}
	
	bool RenderManager::CreateABuffer(int w, int h)
	{
		if(m_pABuffer != nullptr)
		{
			m_pABuffer->Release();
			m_pABuffer.reset();
		}

		G_FORMAT formats[1] = {G_FORMAT_R8G8B8A8_UNORM,};
		m_pABuffer = CreateRenderTarget(1, w, h, formats);

		return true;
	}
	RenderTargetPtr RenderManager::GetGBuffer()
	{
		return m_pGBuffer;
	}
	RenderTargetPtr RenderManager::GetABuffer()
	{
		return m_pABuffer;
	}
	const math::Matrix44& RenderManager::GetViewMatrix()
	{
		return m_viewMatrix;
	}
	const math::Matrix44& RenderManager::GetProjMatrix()
	{
		return m_projMatrix;
	}
	void RenderManager::DrawFullScreenQuad(MaterialPtr pMaterial)
	{
		m_pScreenQuad->Render(m_pGraphics, pMaterial);
	}
}







namespace ld3d
{
	bool RenderManager::ScreenQuad::Init(Sys_GraphicsPtr pGraphics)
	{
		math::Vector3 verts[] = 
		{
			math::Vector3(-1, 1, 0),
			math::Vector3(1, 1, 0),
			math::Vector3(1, -1, 0),
			math::Vector3(-1, 1, 0),
			math::Vector3(1, -1, 0),
			math::Vector3(-1, -1, 0),
		};

		m_pVB = pGraphics->CreateBuffer(BT_VERTEX_BUFFER, sizeof(math::Vector3) * 6, verts, true);

		return true;
	}
	void RenderManager::ScreenQuad::Release()
	{
		if(m_pVB)
		{
			m_pVB->Release();
			m_pVB.reset();
		}
	}
	void RenderManager::ScreenQuad::Render(Sys_GraphicsPtr pGraphics, MaterialPtr pMaterial)
	{
		pGraphics->SetVertexBuffer(m_pVB, 0, sizeof(math::Vector3));
		pGraphics->SetPrimitiveType(PT_TRIANGLE_LIST);

		pMaterial->ApplyVertexFormat();

		int nPass = 0;

		pMaterial->Begin(nPass);

		for(int i = 0; i < nPass; ++i)
		{
			pMaterial->ApplyPass(i);
			pGraphics->Draw(6, 0);
		}

		pMaterial->End();
	}
	const math::Color4& RenderManager::GetGlobalAmbient()
	{
		return m_globalAmbientColor;
	}
	void RenderManager::SetGlobalAmbient(const math::Color4& clr)
	{
		m_globalAmbientColor = clr;
	}
	void RenderManager::SetRenderTarget(RenderTargetPtr pRT)
	{
		m_pGraphics->SetRenderTarget(pRT);
	}
	void RenderManager::ClearRenderTarget(RenderTargetPtr pRT, int index, const math::Color4 & clr)
	{
		m_pGraphics->ClearRenderTarget(pRT, index, clr);
	}
	void RenderManager::ClearDepthBuffer(DepthStencilBufferPtr pDS, CLEAR_DS_FLAG flag, float d, int s)
	{
		m_pGraphics->ClearDepthStencilBuffer(pDS, flag, d, s);
	}
	RenderTargetPtr	RenderManager::CreateRenderTarget(int c, int w, int h, G_FORMAT format[])
	{
		return m_pGraphics->CreateRenderTarget(c, w, h, format);
	}
	int	RenderManager::GetFrameBufferWidth()
	{
		return m_pGraphics->GetFrameBufferWidth();
	}
	int	RenderManager::GetFrameBufferHeight()
	{
		return m_pGraphics->GetFrameBufferHeight();
	}
	void RenderManager::RenderPostEffects()
	{
		m_pPostEffectManager->Render();
	}
	void RenderManager::RenderFinal()
	{
		m_pPostEffectManager->RenderToFrameBuffer();
	}
	MaterialPtr	RenderManager::CreateMaterialFromFile(const char* szFile)
	{
		return m_pGraphics->CreateMaterialFromFile(szFile);
	}
	TexturePtr RenderManager::CreateTextureFromFile(const char* szFile)
	{
		return m_pGraphics->CreateTextureFromFile(szFile);
	}
	void RenderManager::AddPostEffect(PostEffectPtr pEffect)
	{
		m_pPostEffectManager->AddEffect(pEffect);
	}
	void RenderManager::AddCamera(CameraPtr pCamera)
	{
		m_cameras.push_back(pCamera);
	}
	void RenderManager::RemoveCamera(CameraPtr pCamera)
	{
		m_cameras.remove(pCamera);
	}
	GPUBufferPtr RenderManager::CreateBuffer(BUFFER_TYPE type,  int bytes, void* pInitData, bool dynamic)
	{
		return m_pGraphics->CreateBuffer(type, bytes, pInitData, dynamic);
	}
}
