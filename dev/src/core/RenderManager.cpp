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
#include "core/GeometryData.h"
#include "core/RenderTexture.h"
#include "core/MaterialParameter.h"
#include "core/MaterialCompiler.h"

namespace ld3d
{
	class RenderManager_DebugPanel
	{
	public:

		RenderManager_DebugPanel(RenderManagerPtr pManager)
		{
			m_pRenderManager = pManager;


		}


		void											Draw()
		{
		}
	private:
		GeometryDataPtr									m_pGeom;
		MaterialPtr										m_pMaterial;
		RenderManagerPtr								m_pRenderManager;
	};
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
		if(m_pGeometryData)
		{
			m_pGeometryData->Release();
			m_pGeometryData.reset();
		}
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

		m_pScreenQuadMaterial = CreateMaterialFromFile("./assets/standard/material/dr_render_merge.material");

		if(m_pScreenQuadMaterial == nullptr)
		{
			return false;
		}

		m_pDrawTextureMaterial = CreateMaterialFromFile("./assets/standard/material/dr_render_final.material");
		if(m_pDrawTextureMaterial == nullptr)
		{
			return false;

		}
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

		m_pGBuffer = CreateRenderTexture(3, w, h, formats);

		if(m_pGBuffer == nullptr)
		{
			return false;
		}

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
		if(pData->dr)
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
		m_pGraphics->ClearRenderTarget(0, math::Color4(1, 0, 0, 0));
		m_pGraphics->ClearRenderTarget(1, math::Color4(0, 0, 0, 0));
		m_pGraphics->ClearRenderTarget(2, math::Color4(0, 0, 0, 1));
		m_pGraphics->ClearDepthStencil(CLEAR_ALL, 1.0f, 0);

		for(size_t i = 0; i < m_deferredQueue.size(); ++i)
		{
			UpdateMatrixBlock(m_deferredQueue[i]->material, m_deferredQueue[i]->world_matrix);
			DR_DrawRenderData(m_deferredQueue[i]);
		}
	}
	void RenderManager::DR_DrawRenderData(RenderDataPtr pData)
	{
		if(pData->dr_draw)
		{
			pData->dr_draw(shared_from_this());
			return;
		}

		int nPass = pData->material->Begin();
		for(int i = 0; i < nPass; ++i)
		{
			pData->material->ApplyPass(i);
			pData->geometry->GetIndexBuffer() ? 
				m_pGraphics->DrawIndexed(pData->geometry, pData->index_count, pData->start_index, pData->base_vertex) :
				m_pGraphics->Draw(pData->geometry, pData->vertex_count, pData->base_vertex);
		}
		pData->material->End();
	}
	void RenderManager::FR_DrawRenderData(RenderDataPtr pData)
	{
		if(pData->fr_draw)
		{
			pData->fr_draw(shared_from_this());
			return;
		}

		int nPass = pData->material->Begin();
		for(int i = 0; i < nPass; ++i)
		{
			pData->material->ApplyPass(i);
			pData->geometry->GetIndexBuffer() ? 
				m_pGraphics->DrawIndexed(pData->geometry, pData->index_count, pData->start_index, pData->base_vertex) :
				m_pGraphics->Draw(pData->geometry, pData->vertex_count, pData->base_vertex);
		}
		pData->material->End();
	}
	void RenderManager::DR_Merge_Pass()
	{
		RenderTexturePtr pOutput = m_pPostEffectManager->GetInput();

		m_pGraphics->SetRenderTarget(pOutput);
		m_pGraphics->ClearRenderTarget(0, m_clearClr);

		UpdateDRBuffer(m_pScreenQuadMaterial);
		UpdateMatrixBlock(m_pScreenQuadMaterial, math::MatrixIdentity());

		DrawFullScreenQuad(m_pScreenQuadMaterial);
	}
	void RenderManager::RenderForward()
	{
		for(size_t i = 0; i < m_forwardQueue.size(); ++i)
		{
			UpdateMatrixBlock(m_forwardQueue[i]->material, m_forwardQueue[i]->world_matrix);
			
			FR_DrawRenderData(m_forwardQueue[i]);
		}

		for(size_t i = 0; i < m_transparentQueue.size(); ++i)
		{
			UpdateMatrixBlock(m_transparentQueue[i]->material, m_transparentQueue[i]->world_matrix);
			FR_DrawRenderData(m_transparentQueue[i]);
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


	//	Draw_Texture(m_pABuffer->GetTexture(0));
	}
	void RenderManager::Render(CameraPtr pCamera)
	{

		pCamera->UpdateViewFrustum();

		std::shared_ptr<Event_FrustumCull> pEvent = alloc_object<Event_FrustumCull>(pCamera);
			
		m_pEventDispatcher->DispatchEvent(pEvent);


		//RenderShadowMaps();

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
	
	Sys_GraphicsPtr RenderManager::GetSysGraphics()
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
	void RenderManager::OnResizeRenderWindow(int cx, int cy)
	{
		if(cx == 0 || cy == 0)
		{
			return;
		}

		m_pGraphics->SetRenderTarget(nullptr);

		m_pGraphics->OnResizeRenderWindow(cx, cy);
		

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

		m_pGraphics->ClearRenderTarget(0, clr);

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
		m_pABuffer = CreateRenderTexture(1, w, h, formats);
		
		if(m_pABuffer == nullptr)
		{
			return false;
		}

		return true;
	}
	RenderTexturePtr RenderManager::GetGBuffer()
	{
		return m_pGBuffer;
	}
	RenderTexturePtr RenderManager::GetABuffer()
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
	void RenderManager::ClearRenderTarget(int index, const math::Color4 & clr)
	{
		m_pGraphics->ClearRenderTarget(index, clr);
	}
	void RenderManager::ClearDepthBuffer(CLEAR_DS_FLAG flag, float d, int s)
	{
		m_pGraphics->ClearDepthStencil(flag, d, s);
	}
	RenderTexturePtr RenderManager::CreateRenderTexture(int c, int w, int h, G_FORMAT format[])
	{
		RenderTexturePtr pRT = m_pGraphics->CreateRenderTexture();

		for(int i = 0; i < c; ++i)
		{
			TexturePtr pTex = m_pGraphics->CreateTexture2D(format[i], w, h, 1, false);
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
	void RenderManager::RenderPostEffects()
	{
		m_pPostEffectManager->Render();
	}
	void RenderManager::RenderFinal()
	{
		m_pPostEffectManager->RenderToFrameBuffer();
	}
	MaterialPtr RenderManager::CreateMaterialFromFile(const char* szFile)
	{
		using namespace material_script;
		Compiler cl;
		return cl.CompileFromFile(m_pGraphics, szFile);
	}
	TexturePtr RenderManager::CreateTextureFromFile(const char* szFile)
	{
		return m_pGraphics->CreateTextureFromFile(szFile, false);
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
	GeometryDataPtr RenderManager::CreateGeometryData()
	{
		return m_pGraphics->CreateGeometryData();
	}
	void RenderManager::UpdateMatrixBlock(MaterialPtr pMaterial, const math::Matrix44& world)
	{
		m_matrixBlock.MATRIX_WORLD				= world;
		m_matrixBlock.MATRIX_VIEW				= m_viewMatrix;
		m_matrixBlock.MATRIX_PROJ				= m_projMatrix;

		m_matrixBlock.MATRIX_I_WORLD			= math::MatrixInverse(world);
		m_matrixBlock.MATRIX_I_VIEW				= math::MatrixInverse(m_viewMatrix);
		m_matrixBlock.MATRIX_I_PROJ				= math::MatrixInverse(m_projMatrix);

		m_matrixBlock.MATRIX_WV					= world * m_viewMatrix;
		m_matrixBlock.MATRIX_WVP				= world * m_viewMatrix * m_projMatrix;

		m_matrixBlock.MATRIX_I_WV				= math::MatrixInverse(m_matrixBlock.MATRIX_WV);	
		m_matrixBlock.MATRIX_I_WVP				= math::MatrixInverse(m_matrixBlock.MATRIX_WVP);
		m_matrixBlock.MATRIX_I_VP				= math::MatrixInverse(m_viewMatrix * m_projMatrix);

		MaterialParameterPtr pParam = pMaterial->GetParameterByName("_MATRIX");
		if(pParam)
		{
			pParam->SetParameterBlock(&m_matrixBlock, sizeof(MATRIX_BLOCK));
		}
	}
	void RenderManager::UpdateDRBuffer(MaterialPtr pMaterial)
	{
		MaterialParameterPtr pParam = pMaterial->GetParameterByName("_DR_A_BUFFER");
		if(pParam)
		{
			pParam->SetParameterTexture(m_pABuffer->GetTexture(0));
		}


		pParam = pMaterial->GetParameterByName("_DR_G_BUFFER[0]");

		if(pParam == nullptr)
		{
			return;
		}

		if(pParam)
		{
			pParam->SetParameterTexture(m_pGBuffer->GetTexture(0));
		}

		pParam = pMaterial->GetParameterByName("_DR_G_BUFFER[1]");
		if(pParam)
		{
			pParam->SetParameterTexture(m_pGBuffer->GetTexture(1));
		}

		pParam = pMaterial->GetParameterByName("_DR_G_BUFFER[2]");
		if(pParam)
		{
			pParam->SetParameterTexture(m_pGBuffer->GetTexture(2));
		}
	}
	void RenderManager::Draw_Texture(TexturePtr pTex)
	{
		MaterialParameterPtr pParam = m_pDrawTextureMaterial->GetParameterByName("final_image");
		pParam->SetParameterTexture(pTex);

		DrawFullScreenQuad(m_pDrawTextureMaterial);
	}
}
