#include "core_pch.h"
#include "core/PostEffect_FXAA.h"
#include "core/RenderManager.h"
#include "core/Material.h"
#include "core/RenderTexture.h"
#include "core/RenderManager.h"
#include "core/MaterialParameter.h"

namespace ld3d
{
	PostEffect_FXAA::PostEffect_FXAA(void)
	{
	}


	PostEffect_FXAA::~PostEffect_FXAA(void)
	{
	}
	void PostEffect_FXAA::Render(RenderManagerPtr pRenderer, RenderTexturePtr pInput, RenderTexturePtr pOutput)
	{
		pRenderer->SetRenderTarget(pOutput);
		pRenderer->ClearRenderTarget(0, pRenderer->GetClearColor());
		pRenderer->ClearDepthBuffer(CLEAR_DEPTH, 1.0f, 0);

		m_pSrcImage->SetParameterTexture(pInput->GetTexture(0));

		pRenderer->DrawFullScreenQuad(m_pMaterial);
	}
	void PostEffect_FXAA::Release()
	{
		_release_and_reset(m_pMaterial);
	}
	bool PostEffect_FXAA::Initialize(RenderManagerPtr pRenderManager)
	{
		m_pMaterial = pRenderManager->CreateMaterialFromFile("./assets/standard/material/fxaa.material");
		if(m_pMaterial == nullptr)
		{
			return false;
		}

		m_pSrcImage = m_pMaterial->GetParameterByName("final_image");

		if(m_pSrcImage == nullptr)
		{
			return false;
		}

		return true;
	}
}
