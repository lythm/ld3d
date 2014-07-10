#include "core_pch.h"
#include "RenderSystem_Deferred.h"
#include "core/RenderData.h"
#include "core/Sys_Graphics.h"
#include "core/Material.h"
#include "core/g_format.h"
#include "core_utils.h"
#include "core/LightManager.h"
#include "core/RenderTexture.h"
#include "core/DepthStencilBuffer.h"
#include "core/MaterialParameter.h"
#include "core/RenderManager.h"

#include "RenderQueue.h"
#include "RenderParameters.h"


namespace ld3d
{
	RenderSystem_Deferred::RenderSystem_Deferred(void)
	{
	}
	
	RenderSystem_Deferred::~RenderSystem_Deferred(void)
	{
	}
	bool RenderSystem_Deferred::Initialize(RenderManagerPtr pRenderManager, DepthStencilBufferPtr pDSBuffer)
	{
		m_pRenderManager = pRenderManager;

		m_pGraphics = pRenderManager->GetSysGraphics();

		m_pDSBuffer = pDSBuffer;
		m_pLightManager = pRenderManager->GetLightManager();
		m_pRenderParams = pRenderManager->GetRenderParams();


		int w = m_pGraphics->GetFrameBufferWidth();
		int h = m_pGraphics->GetFrameBufferHeight();

		if(false == ResizeGBuffer(w, h))
		{
			return false;
		}
		if(false == ResizeABuffer(w, h))
		{
			return false;
		}

		m_pMergePassMaterial = m_pRenderManager->CreateMaterialFromFile("./assets/standard/material/dr_render_merge.material");

		if(m_pMergePassMaterial == nullptr)
		{
			return false;
		}

		return true;
	}
	void RenderSystem_Deferred::Release()
	{
		_release_and_reset(m_pMergePassMaterial);

		_release_and_reset(m_pGBuffer);

		_release_and_reset(m_pABuffer);

		_release_and_reset(m_pDSBuffer);

		m_pGraphics.reset();
	}
	bool RenderSystem_Deferred::ResizeGBuffer(int w, int h)
	{
		_release_and_reset(m_pGBuffer);

		G_FORMAT formats[3] = 
		{
			G_FORMAT_R32_FLOAT,					// depth
			G_FORMAT_R16G16_FLOAT,				// normal.xy
			G_FORMAT_R8G8B8A8_UNORM,			// diffuse color : specular
		};

		m_pGBuffer = m_pGraphics->CreateRenderTexture();
		
		if(m_pGBuffer == nullptr)
		{
			return false;
		}

		for(int i = 0; i < 3; ++i)
		{
			TexturePtr pTex = m_pGraphics->CreateTexture2D(formats[i], w, h, 1, false);
			m_pGBuffer->AttachTexture(pTex);
		}
		
		m_pGBuffer->SetDepthStencilBuffer(m_pDSBuffer);
		return true;

	}
	bool RenderSystem_Deferred::ResizeABuffer(int w, int h)
	{
		if(m_pABuffer != nullptr)
		{
			m_pABuffer->Release();
			m_pABuffer.reset();
		}

		G_FORMAT format = G_FORMAT_R8G8B8A8_UNORM;
		m_pABuffer = m_pGraphics->CreateRenderTexture();

		if(m_pABuffer == nullptr)
		{
			return false;
		}

		TexturePtr pTex = m_pGraphics->CreateTexture2D(format, w, h, 1, false);
		m_pABuffer->AttachTexture(pTex);
		

		m_pABuffer->SetDepthStencilBuffer(m_pDSBuffer);
		return true;
	}
	void RenderSystem_Deferred::ResizeFrameBuffer(int w, int h, DepthStencilBufferPtr pDSBuffer)
	{
		m_pDSBuffer = pDSBuffer;
		ResizeABuffer(w, h);
		ResizeGBuffer(w, h);
	}
	void RenderSystem_Deferred::Render(RenderQueuePtr pRenderQueue, CameraPtr pCamera, RenderTargetPtr pTarget)
	{
		DR_G_Pass(pRenderQueue);

		DR_Light_Pass(pCamera);

		DR_Merge_Pass(pTarget);
	}
	RenderTexturePtr RenderSystem_Deferred::GetABuffer() const
	{
		return m_pABuffer;
	}
	RenderTexturePtr RenderSystem_Deferred::GetGBuffer() const
	{
		return m_pGBuffer;
	}
	void RenderSystem_Deferred::DR_G_Pass(RenderQueuePtr pRenderQueue)
	{
		m_pGraphics->SetRenderTarget(m_pGBuffer);
		m_pGraphics->ClearRenderTarget(0, math::Color4(1, 0, 0, 0));
		m_pGraphics->ClearRenderTarget(1, math::Color4(0, 0, 0, 0));
		m_pGraphics->ClearRenderTarget(2, math::Color4(0, 0, 0, 1));
		m_pGraphics->ClearDepthStencil(CLEAR_ALL, 1.0f, 0);

		for(uint32 iLayer = layer_deferred; iLayer < layer_forward; ++iLayer)
		{
			for(uint32 i = 0; i < pRenderQueue->GetRenderDataCount(iLayer); ++i)
			{
				RenderDataPtr pData = pRenderQueue->GetRenderData(iLayer, i);

				if(pData->dr_draw)
				{
					pData->dr_draw(m_pRenderManager);
					continue;
				}

				m_pRenderParams->SetMaterialMatrixBlock(pData->material, pData->world_matrix);

				m_pRenderManager->DrawRenderData(pData);
			}
		}
	}
	void RenderSystem_Deferred::DR_Light_Pass(CameraPtr pCamera)
	{
		m_pGraphics->SetRenderTarget(m_pABuffer);

		math::Color4 clr = m_pRenderParams->GetGlobalAmbientColor();
		clr.a = 0;
		m_pGraphics->ClearRenderTarget(0, clr);

		m_pLightManager->RenderLights(pCamera);
	}
	void RenderSystem_Deferred::DR_Merge_Pass(RenderTargetPtr pTarget)
	{
		m_pGraphics->SetRenderTarget(pTarget);

		SetMaterialABuffer(m_pMergePassMaterial);
		SetMaterialGBuffer(m_pMergePassMaterial);
		m_pRenderParams->SetMaterialMatrixBlock(m_pMergePassMaterial, math::MatrixIdentity());

		m_pRenderManager->DrawFullScreenQuad(m_pMergePassMaterial);
	}
	void RenderSystem_Deferred::SetMaterialABuffer(MaterialPtr pMaterial)
	{
		MaterialParameterPtr pParam = pMaterial->GetParameterByName("_DR_A_BUFFER");
		pParam ? pParam->SetParameterTexture(m_pABuffer->GetTexture(0)) : (void)0 ;
	}
	void RenderSystem_Deferred::SetMaterialGBuffer(MaterialPtr pMaterial)
	{
		MaterialParameterPtr pParam = pMaterial->GetParameterByName("_DR_G_BUFFER_0");
		pParam ? pParam->SetParameterTexture(m_pGBuffer->GetTexture(0)) : (void)0;

		pParam = pMaterial->GetParameterByName("_DR_G_BUFFER_1");

		pParam ? pParam->SetParameterTexture(m_pGBuffer->GetTexture(1)) : (void)0;

		pParam = pMaterial->GetParameterByName("_DR_G_BUFFER_2");
		pParam ? pParam->SetParameterTexture(m_pGBuffer->GetTexture(2)) : (void)0;

	}
}
