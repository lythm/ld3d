#include "core_pch.h"
#include "core/PostEffectManager.h"
#include "core/PostEffect.h"
#include "core/RenderManager.h"
#include "core/Material.h"
#include "core/VertexFormat.h"
#include "core/RenderTexture.h"
#include "core/PostEffect_SSAO.h"
#include "core_utils.h"
#include "core/MaterialParameter.h"

namespace ld3d
{
	PostEffectManager::PostEffectManager(void)
	{
	}


	PostEffectManager::~PostEffectManager(void)
	{
	}
	bool PostEffectManager::Initialize(RenderManagerPtr pRenderManager)
	{
		m_pRenderManager = pRenderManager;

		int w = pRenderManager->GetFrameBufferWidth();
		int h = pRenderManager->GetFrameBufferHeight();

		if(false == CreateRT(w, h))
		{
			return false;
		}
		
		m_pFinalMaterial = pRenderManager->CreateMaterialFromFile("./assets/standard/material/dr_render_final.material");
		if(m_pFinalMaterial == nullptr)
		{
			return false;
		}

		m_pParamOutput = m_pFinalMaterial->GetParameterByName("final_image");

		if(m_pParamOutput == nullptr)
		{
			return false;
		}

		/*std::shared_ptr<PostEffect_SSAO> pSSAO = alloc_object<PostEffect_SSAO>();
		pSSAO->Initialize(m_pRenderManager);
		
		m_effects.push_back(pSSAO);*/

		return true;
	}
	void PostEffectManager::Release()
	{
		for(size_t i = 0; i < m_effects.size(); ++i)
		{
			m_effects[i]->Release();
		}

		m_effects.clear();

		_release_and_reset(m_pInput);

		_release_and_reset(m_pOutput);

		_release_and_reset(m_pFinalMaterial);
		
	}
	void PostEffectManager::Render()
	{
		return;
		for(size_t i = 0; i < m_effects.size(); ++i)
		{
			m_effects[i]->Render(m_pRenderManager, m_pInput, m_pOutput);
			SwapRenderTarget();
		}
		SwapRenderTarget();
	}
	void PostEffectManager::SwapRenderTarget()
	{
		RenderTexturePtr pTmp;
		pTmp = m_pInput;
		m_pInput = m_pOutput;
		m_pOutput = pTmp;
	}
	RenderTexturePtr PostEffectManager::GetInput()
	{
		return m_pInput;
	}
	RenderTexturePtr PostEffectManager::GetOutput()
	{
		return m_pOutput;
	}
	int	PostEffectManager::GetEffectCount()
	{
		return (int)m_effects.size();
	}
	void PostEffectManager::Resize(int cx, int cy)
	{
		if(cx == 0 || cy == 0)
		{
			return;
		}

		CreateRT(cx, cy);
	}
	bool PostEffectManager::CreateRT(int w, int h)
	{
		_release_and_reset(m_pInput);

		_release_and_reset(m_pOutput);

		G_FORMAT formats[1] = {G_FORMAT_R8G8B8A8_UNORM,};
		m_pInput = m_pRenderManager->CreateRenderTexture(1, w, h, formats);

		if(m_pInput == nullptr)
		{
			return false;
		}

		m_pInput->SetDepthStencilBuffer(m_pRenderManager->GetDepthStencilBuffer());

		m_pOutput = m_pRenderManager->CreateRenderTexture(1, w, h, formats);

		if(m_pOutput == nullptr)
		{
			return false;
		}
		m_pOutput->SetDepthStencilBuffer(m_pRenderManager->GetDepthStencilBuffer());
		return true;
	}
	void PostEffectManager::RenderToFrameBuffer()
	{
		m_pRenderManager->SetRenderTarget(nullptr);
		m_pRenderManager->ClearRenderTarget(0, m_pRenderManager->GetClearColor());
		m_pRenderManager->ClearDepthBuffer(CLEAR_DEPTH, 1.0f, 0);

		//m_pParamOutput->SetParameterTexture(m_pOutput->GetTexture(0));
		m_pParamOutput->SetParameterTexture(m_pInput->GetTexture(0));

		m_pRenderManager->DrawFullScreenQuad(m_pFinalMaterial);
	}
	void PostEffectManager::AddEffect(PostEffectPtr pEffect)
	{
		m_effects.push_back(pEffect);
	}
}

