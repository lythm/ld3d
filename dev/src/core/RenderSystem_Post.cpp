#include "core_pch.h"
#include "core/RenderSystem_Post.h"
#include "core/PostEffect.h"
#include "core/RenderManager.h"
#include "core/Material.h"
#include "core/VertexFormat.h"
#include "core/RenderTexture.h"
#include "core/PostEffect_SSAO.h"
#include "core_utils.h"
#include "core/MaterialParameter.h"
#include "core/Sys_Graphics.h"

namespace ld3d
{
	RenderSystem_Post::RenderSystem_Post(void)
	{
	}


	RenderSystem_Post::~RenderSystem_Post(void)
	{
	}
	bool RenderSystem_Post::Initialize(RenderManagerPtr pRenderManager)
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

		int rw = m_pRenderManager->GetSysGraphics()->GetRenderWindowWidth();
		int rh = m_pRenderManager->GetSysGraphics()->GetRenderWindowHeight();

		m_pFinalMaterial->GetParameterByName("render_window_width")->SetParameterInt(rw);
		m_pFinalMaterial->GetParameterByName("render_window_height")->SetParameterInt(rh);

		m_pFinalParam = m_pFinalMaterial->GetParameterByName("final_image");

		if(m_pFinalParam == nullptr)
		{
			return false;
		}

		/*std::shared_ptr<PostEffect_SSAO> pSSAO = alloc_object<PostEffect_SSAO>();
		pSSAO->Initialize(m_pRenderManager);
		
		m_effects.push_back(pSSAO);*/

		return true;
	}
	void RenderSystem_Post::Release()
	{
		_release_and_reset(m_pIn);

		_release_and_reset(m_pOut);

		_release_and_reset(m_pFinalMaterial);
		
	}
	void RenderSystem_Post::Render(PostEffectPtr pEffect)
	{
		pEffect->Render(m_pRenderManager, m_pIn, m_pOut);
		SwapRenderTarget();
	}
	void RenderSystem_Post::Render(const std::vector<PostEffectPtr>& effects)
	{
		if(effects.size() == 0)
		{
			return;
		}
		for(size_t i = 0; i < effects.size(); ++i)
		{
			Render(effects[i]);
		}
	}
	
	void RenderSystem_Post::SwapRenderTarget()
	{
		std::swap(m_pIn, m_pOut);
	}
	RenderTexturePtr RenderSystem_Post::GetIn()
	{
		return m_pIn;
	}
	RenderTexturePtr RenderSystem_Post::GetOut()
	{
		return m_pOut;
	}
	
	void RenderSystem_Post::Resize(int cx, int cy)
	{
		if(cx == 0 || cy == 0)
		{
			return;
		}

		CreateRT(cx, cy);

		int w = m_pRenderManager->GetSysGraphics()->GetRenderWindowWidth();
		int h = m_pRenderManager->GetSysGraphics()->GetRenderWindowHeight();

		m_pFinalMaterial->GetParameterByName("render_window_width")->SetParameterInt(w);
		m_pFinalMaterial->GetParameterByName("render_window_height")->SetParameterInt(h);
	}
	bool RenderSystem_Post::CreateRT(int w, int h)
	{
		_release_and_reset(m_pIn);

		_release_and_reset(m_pOut);

		G_FORMAT formats[1] = {G_FORMAT_R8G8B8A8_UNORM,};
		m_pIn = m_pRenderManager->CreateRenderTexture(1, w, h, formats);

		if(m_pIn == nullptr)
		{
			return false;
		}

		m_pIn->SetDepthStencilBuffer(m_pRenderManager->GetDepthStencilBuffer());

		m_pOut = m_pRenderManager->CreateRenderTexture(1, w, h, formats);

		if(m_pOut == nullptr)
		{
			return false;
		}
		m_pOut->SetDepthStencilBuffer(m_pRenderManager->GetDepthStencilBuffer());
		return true;
	}
	
	void RenderSystem_Post::RenderFinal(RenderTargetPtr pTarget)
	{
		m_pRenderManager->SetRenderTarget(pTarget);
		m_pRenderManager->ClearRenderTarget(0, m_pRenderManager->GetClearColor());
		m_pRenderManager->ClearDepthBuffer(CLEAR_DEPTH, 1.0f, 0);

		m_pFinalParam->SetParameterTexture(m_pIn->GetTexture(0));

		m_pRenderManager->DrawFullScreenQuad(m_pFinalMaterial);
	}
}

