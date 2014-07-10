#include "core_pch.h"
#include "core/RenderManager.h"
#include "core/RenderData.h"
#include "core/Sys_Graphics.h"
#include "core/Material.h"
#include "core/g_format.h"
#include "core/RenderTarget.h"
#include "core_utils.h"
#include "core/GPUBuffer.h"
#include "core/LightManager.h"
#include "core/Light.h"
#include "core/RenderSystem_Post.h"
#include "core/Camera.h"
#include "core/Event.h"
#include "core/GeometryData.h"
#include "core/RenderTexture.h"
#include "core/DepthStencilBuffer.h"
#include "core/MaterialParameter.h"
#include "core/MaterialCompiler.h"
#include "RenderQueue.h"
#include "RenderParameters.h"
#include "RenderSystem_Deferred.h"
#include "RenderSystem_Forward.h"

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

		m_pGeometryData = pGraphics->CreateGeometryData();
		VertexLayout layout;
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);

		m_pGeometryData->BeginGeometry(PT_TRIANGLE_LIST);
		{
			m_pGeometryData->AllocVertexBuffer(sizeof(math::Vector3) * 6, verts, false, layout);
		}
		m_pGeometryData->EndGeometry();
		return true;
	}
	void RenderManager::ScreenQuad::Release()
	{
		_release_and_reset(m_pGeometryData);
	}
	void RenderManager::ScreenQuad::Render(Sys_GraphicsPtr pGraphics, MaterialPtr pMaterial)
	{
		int nPass = 0;

		nPass = pMaterial->Begin();

		for(int i = 0; i < nPass; ++i)
		{
			pMaterial->ApplyPass(i);
			pGraphics->Draw(m_pGeometryData, 6, 0);
		}

		pMaterial->End();
	}
}
namespace ld3d
{
	RenderManager::RenderManager(void)
	{
	}


	RenderManager::~RenderManager(void)
	{
	}

	bool RenderManager::Initialize(Sys_GraphicsPtr pGraphics, EventDispatcherPtr pED)
	{
		m_pGraphics = pGraphics;
		m_pEventDispatcher = pED;

		m_pRenderParams = alloc_object<RenderParameters>();
		
		m_pRenderQueue = alloc_object<RenderQueue>();

		if(m_pRenderQueue->Initialize(layer_max) == false)
		{
			return false;
		}

		int w = pGraphics->GetFrameBufferWidth();
		int h = pGraphics->GetFrameBufferHeight();


		m_pDSBuffer = m_pGraphics->CreateDepthStencilBuffer(G_FORMAT_D24_UNORM_S8_UINT, w, h);

		if(m_pDSBuffer == nullptr)
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

		m_pPR = alloc_object<RenderSystem_Post>();
		if(m_pPR->Initialize(shared_from_this()) == false)
		{
			return false;
		}

		m_pDR			= alloc_object<RenderSystem_Deferred>();
		if(false == m_pDR->Initialize(shared_from_this(), m_pDSBuffer))
		{
			return false;
		}

		m_pFR			= alloc_object<RenderSystem_Forward>();
		if(false == m_pFR->Initialize(shared_from_this()))
		{
			return false;
		}
		m_pDrawTextureMaterial = CreateMaterialFromFile("./assets/standard/material/draw_screen_texture.material");
		if(m_pDrawTextureMaterial == nullptr)
		{
			return false;
		}

		m_pShadowMapMaterial = CreateMaterialFromFile("./assets/standard/material/geo_shadow_map.material");
		if(m_pShadowMapMaterial == nullptr)
		{
			return false;
		}
		
		return true;
	}

	void RenderManager::Release()
	{
		Clear();

		_release_and_reset(m_pShadowMapMaterial);

		_release_and_reset(m_pDrawTextureMaterial);
		
		_release_and_reset(m_pLightManager);

		_release_and_reset(m_pPR);

		_release_and_reset(m_pScreenQuad);

		_release_and_reset(m_pFR);
		_release_and_reset(m_pDR);

		_release_and_reset(m_pDSBuffer);

		_release_and_reset(m_pRenderQueue);

	}

	void RenderManager::AddRenderData(RENDER_LAYER layer, RenderDataPtr pData)
	{
		m_pRenderQueue->AddRenderData(layer, pData);

	}
	void RenderManager::Clear()
	{
		m_pRenderQueue->ClearAll();

	}
	
	void RenderManager::DrawRenderData(RenderDataPtr pData, MaterialPtr pMaterial)
	{
		MaterialPtr pDrawMaterial = pMaterial == nullptr ? pData->material : pMaterial;
		if(pDrawMaterial == nullptr)
		{
			return;
		}
		int nPass = pDrawMaterial->Begin();
		for(int i = 0; i < nPass; ++i)
		{
			pDrawMaterial->ApplyPass(i);
			pData->geometry->GetIndexBuffer() ? 
				m_pGraphics->DrawIndexed(pData->geometry, pData->index_count, pData->start_index, pData->base_vertex) :
				m_pGraphics->Draw(pData->geometry, pData->vertex_count, pData->base_vertex);
		}
		pDrawMaterial->End();
	}

	void RenderManager::RenderOverlay()
	{
		for(uint32 iLayer = layer_overlay; iLayer < layer_max; ++iLayer)
		{
			for(uint32 i = 0; i < m_pRenderQueue->GetRenderDataCount(iLayer); ++i)
			{
				RenderDataPtr pData = m_pRenderQueue->GetRenderData(iLayer, i);
				
				SetMatrixBlock(pData->material, pData->world_matrix);
				
				if(pData->fr_draw)
				{
					pData->fr_draw(shared_from_this());
					continue;
				}
				
				DrawRenderData(pData);
			}
		}
	}
	
	void RenderManager::DrawShadowMapGeometry(const math::Matrix44& view, const math::Matrix44& proj)
	{
		SetViewMatrix(view);
		SetProjMatrix(proj);

		for(uint32 iLayer = layer_deferred; iLayer < layer_forward; ++iLayer)
		{
			for(uint32 i = 0; i < m_pRenderQueue->GetRenderDataCount(iLayer); ++i)
			{
				RenderDataPtr pData = m_pRenderQueue->GetRenderData(iLayer, i);
				
				SetMatrixBlock(m_pShadowMapMaterial, pData->world_matrix);
				
				if(pData->sm_draw)
				{
					pData->sm_draw(shared_from_this(), m_pShadowMapMaterial);
					continue;
				}
				
				DrawRenderData(pData, m_pShadowMapMaterial);
			}
		}
	}
	void RenderManager::EmitViewFrustumCullEvent(const math::ViewFrustum& vf)
	{
		std::shared_ptr<Event_FrustumCull> pEvent = alloc_object<Event_FrustumCull>((math::ViewFrustum*)&vf);

		m_pEventDispatcher->DispatchEvent(pEvent);
	}
	void RenderManager::Render(CameraPtr pCamera)
	{
		pCamera->UpdateViewFrustum();
		
		RenderShadowMaps(pCamera);
		

		const math::RectI& vp = pCamera->GetViewport();
		SetViewport(vp);

		SetViewMatrix(pCamera->GetViewMatrix());
		SetProjMatrix(pCamera->GetProjMatrix());

		math::ViewFrustum vf = pCamera->GetViewFrustum();
		EmitViewFrustumCullEvent(vf);

		RenderTexturePtr pTarget = m_pPR->GetIn();

		RenderBackground(pTarget);
		

		// render deferred
		m_pDR->Render(m_pRenderQueue, pCamera, pTarget);

		// Forward and transparent pass
		m_pFR->Render(m_pRenderQueue, pTarget);

		// post effects pass
		m_pPR->Render(pCamera->GetEffectList());

		// Final Pass
		m_pPR->RenderFinal(nullptr);
				
		// overlays

	//	SetRenderTarget(nullptr);
	//	ClearRenderTarget(0, GetClearColor());
	//	ClearDepthBuffer(CLEAR_DEPTH, 1.0f, 0);
		
	//	RenderTexturePtr pTex = m_pLightManager->GetNextLight(LightPtr())->GetShadowMap();

		//Draw_Texture(pTex->GetTexture(0));

		//Draw_Texture(m_pGBuffer->GetTexture(0));
		//Draw_Texture(m_pABuffer->GetTexture(0));
		//Draw_Texture(m_pPR->GetOutput()->GetTexture(0));

	}
	void RenderManager::Render()
	{
		m_cameras.sort(Camera::SortFunction);

		std::list<CameraPtr>::iterator it = m_cameras.begin();
		for(it; it != m_cameras.end(); ++it)
		{
			Render(*it);
		}

		RenderOverlay();
	}
	void RenderManager::Present()
	{
		m_pGraphics->Present();
	}
	void RenderManager::SetViewMatrix(const math::Matrix44& view)
	{
		m_pRenderParams->SetViewMatrix(view);
	}
	void RenderManager::SetProjMatrix(const math::Matrix44& proj)
	{
		m_pRenderParams->SetProjMatrix(proj);
	}

	Sys_GraphicsPtr RenderManager::GetSysGraphics()
	{
		return m_pGraphics;
	}
	void RenderManager::SetClearColor(const math::Color4& clr)
	{
		m_pRenderParams->SetClearColor(clr);
	}
	const math::Color4&	RenderManager::GetClearColor()
	{
		return m_pRenderParams->GetClearColor();
	}
	void RenderManager::SetClearDepth(float d)
	{
		m_pRenderParams->SetClearDepth(d);
	}
	void RenderManager::SetClearStencil(int s)
	{
		m_pRenderParams->SetClearStencil(s);
	}
	void RenderManager::ResizeFramebuffer(int cx, int cy, bool fullscreen)
	{
		if(cx == 0 || cy == 0)
		{
			return;
		}

		m_pGraphics->SetRenderTarget(nullptr);

		m_pGraphics->ResizeRenderWindow(cx, cy, fullscreen);


		if(m_pDSBuffer)
		{
			m_pDSBuffer->Release();
		}

		m_pDSBuffer = m_pGraphics->CreateDepthStencilBuffer(G_FORMAT_D24_UNORM_S8_UINT, cx, cy);

		m_pDR->ResizeFrameBuffer(cx, cy, m_pDSBuffer);
		
		m_pPR->Resize(cx, cy);


		std::shared_ptr<Event_ResizeFrameBuffer> pEvent = alloc_object<Event_ResizeFrameBuffer>(cx, cy);

		m_pEventDispatcher->DispatchEvent(pEvent);

	}
	void RenderManager::OnResizeFramebuffer(int cx, int cy)
	{
		if(cx == 0 || cy == 0)
		{
			return;
		}

		m_pGraphics->SetRenderTarget(nullptr);

		m_pGraphics->OnResizeRenderWindow(cx, cy);


		if(m_pDSBuffer)
		{
			m_pDSBuffer->Release();
		}

		m_pDSBuffer = m_pGraphics->CreateDepthStencilBuffer(G_FORMAT_D24_UNORM_S8_UINT, cx, cy);

		m_pDR->ResizeFrameBuffer(cx, cy, m_pDSBuffer);

		m_pPR->Resize(cx, cy);

		std::shared_ptr<Event_ResizeFrameBuffer> pEvent = alloc_object<Event_ResizeFrameBuffer>(cx, cy);

		m_pEventDispatcher->DispatchEvent(pEvent);
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

	void RenderManager::RenderShadowMaps(CameraPtr pCamera)
	{
		m_pLightManager->RenderShadowMaps(pCamera);
	}


	RenderTexturePtr RenderManager::GetGBuffer()
	{
		return m_pDR->GetGBuffer();
	}
	RenderTexturePtr RenderManager::GetABuffer()
	{
		return m_pDR->GetABuffer();
	}
	const math::Matrix44& RenderManager::GetViewMatrix()
	{
		return m_pRenderParams->GetViewMatrix();
	}
	const math::Matrix44& RenderManager::GetProjMatrix()
	{
		return m_pRenderParams->GetProjMatrix();
	}
	void RenderManager::DrawFullScreenQuad(MaterialPtr pMaterial)
	{
		m_pScreenQuad->Render(m_pGraphics, pMaterial);
	}
	const math::Color4& RenderManager::GetGlobalAmbient()
	{
		return m_pRenderParams->GetGlobalAmbientColor();
	}
	void RenderManager::SetGlobalAmbient(const math::Color4& clr)
	{
		m_pRenderParams->SetGlobalAmbientColor(clr);
	}
	void RenderManager::SetRenderTarget(RenderTargetPtr pRT)
	{
		m_pGraphics->SetRenderTarget(pRT);
	}
	void RenderManager::ClearRenderTarget(int index, const math::Color4 & clr)
	{
		m_pGraphics->ClearRenderTarget(index, clr);
	}
	void RenderManager::ClearDepthBuffer(CLEAR_DS_FLAG flag, float d, int s)
	{
		m_pGraphics->ClearDepthStencil(flag, d, s);
	}
	RenderTexturePtr RenderManager::CreateRenderTexture(int c, int w, int h, G_FORMAT format[], int lvls)
	{
		RenderTexturePtr pRT = m_pGraphics->CreateRenderTexture();

		for(int i = 0; i < c; ++i)
		{
			TexturePtr pTex = m_pGraphics->CreateTexture2D(format[i], w, h, lvls, false);
			pRT->AttachTexture(pTex);
		}

		return pRT;
	}
	RenderTexturePtr RenderManager::CreateRenderTextureMS(int c, int w, int h, G_FORMAT format[], int samples)
	{
		RenderTexturePtr pRT = m_pGraphics->CreateRenderTexture();

		for(int i = 0; i < c; ++i)
		{
			TexturePtr pTex = m_pGraphics->CreateTexture2DMS(format[i], w, h, samples);
			pRT->AttachTexture(pTex);
		}

		return pRT;
	}
	int	RenderManager::GetFrameBufferWidth()
	{
		return m_pGraphics->GetFrameBufferWidth();
	}
	int	RenderManager::GetFrameBufferHeight()
	{
		return m_pGraphics->GetFrameBufferHeight();
	}
	
	MaterialPtr RenderManager::CreateMaterialFromFile(const char* szFile)
	{
		using namespace material_script;
		Compiler cl;
		return cl.CompileFromFile(m_pGraphics, szFile);
	}
	TexturePtr RenderManager::CreateTextureFromFile(const char* szFile)
	{
		return m_pGraphics->CreateTextureFromFile(szFile);
	}
	
	void RenderManager::AddCamera(CameraPtr pCamera)
	{
		m_cameras.push_back(pCamera);
	}
	void RenderManager::RemoveCamera(CameraPtr pCamera)
	{
		m_cameras.remove(pCamera);
	}
	GeometryDataPtr RenderManager::CreateGeometryData()
	{
		return m_pGraphics->CreateGeometryData();
	}
	void RenderManager::SetMatrixBlock(MaterialPtr pMaterial, const math::Matrix44& world)
	{
		m_pRenderParams->SetMaterialMatrixBlock(pMaterial, world);
	}
	void RenderManager::SetDRBuffer(MaterialPtr pMaterial)
	{
		SetABuffer(pMaterial);
		SetGBuffer(pMaterial);
	}
	void RenderManager::SetABuffer(MaterialPtr pMaterial)
	{
		RenderTexturePtr pABuffer = m_pDR->GetABuffer();
		MaterialParameterPtr pParam = pMaterial->GetParameterByName("_DR_A_BUFFER");
		pParam ? pParam->SetParameterTexture(pABuffer->GetTexture(0)) : (void)0 ;
	}
	void RenderManager::SetGBuffer(MaterialPtr pMaterial)
	{
		RenderTexturePtr pGBuffer = m_pDR->GetGBuffer();

		MaterialParameterPtr pParam = pMaterial->GetParameterByName("_DR_G_BUFFER_0");
		pParam ? pParam->SetParameterTexture(pGBuffer->GetTexture(0)) : (void)0;

		pParam = pMaterial->GetParameterByName("_DR_G_BUFFER_1");

		pParam ? pParam->SetParameterTexture(pGBuffer->GetTexture(1)) : (void)0;

		pParam = pMaterial->GetParameterByName("_DR_G_BUFFER_2");
		pParam ? pParam->SetParameterTexture(pGBuffer->GetTexture(2)) : (void)0;

	}
	void RenderManager::Draw_Texture(TexturePtr pTex)
	{
		MaterialParameterPtr pParam = m_pDrawTextureMaterial->GetParameterByName("final_image");
		pParam->SetParameterTexture(pTex);

		DrawFullScreenQuad(m_pDrawTextureMaterial);
	}
	void RenderManager::RenderTest(CameraPtr pCamera)
	{
	}
	DepthStencilBufferPtr RenderManager::GetDepthStencilBuffer()
	{
		return m_pDSBuffer;
	}
	void RenderManager::SetViewport(const math::RectI& vp)
	{
		m_pGraphics->SetViewPort(vp.left , vp.top, vp.width(), vp.height());
	}
	bool RenderManager::IsFullscreen()
	{
		return m_pGraphics->IsFullscreen();
	}
	TexturePtr RenderManager::Create2DTextureArrayFromFileList(const std::vector<std::string>& files)
	{
		return m_pGraphics->Create2DArrayFromFiles(files);
	}
	RenderParametersPtr RenderManager::GetRenderParams() const
	{
		return m_pRenderParams;
	}
	LightManagerPtr RenderManager::GetLightManager()
	{
		return m_pLightManager;
	}

	void RenderManager::RenderBackground(RenderTargetPtr pTarget)
	{
		SetRenderTarget(pTarget);
		ClearRenderTarget(0, m_pRenderParams->GetClearColor());
		ClearDepthBuffer(CLEAR_DEPTH, 1.0f, 0);
		for(uint32 i = 0; i < m_pRenderQueue->GetRenderDataCount(layer_background); ++i)
		{
			RenderDataPtr pData = m_pRenderQueue->GetRenderData(layer_background, i);
			if(pData->fr_draw)
			{
				pData->fr_draw(shared_from_this());
				continue;
			}
			SetMatrixBlock(pData->material, pData->world_matrix);

			DrawRenderData(pData);
		}
	}
}
