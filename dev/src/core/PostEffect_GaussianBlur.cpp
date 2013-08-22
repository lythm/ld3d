#include "core_pch.h"
#include "core/PostEffect_GaussianBlur.h"
#include "core/RenderManager.h"
#include "core/Material.h"
#include "core/VertexFormat.h"
#include "core/RenderTexture.h"
#include "core/MaterialParameter.h"

namespace ld3d
{
	PostEffect_GaussianBlur::PostEffect_GaussianBlur(void)
	{
	}


	PostEffect_GaussianBlur::~PostEffect_GaussianBlur(void)
	{
	}
	bool PostEffect_GaussianBlur::Initialize(RenderManagerPtr pRenderManager)
	{
		m_pRenderManager = pRenderManager;

		m_pMaterial = pRenderManager->CreateMaterialFromFile("./assets/standard/material/dr_render_GBlur.fx");

		if(m_pMaterial == nullptr)
		{
			return false;
		}
		
		m_pParamInputSize = m_pMaterial->GetParameterByName("g_input_size");
		m_pParamInputTex = m_pMaterial->GetParameterByName("tex_input");
		return true;
	}
	void PostEffect_GaussianBlur::Render(RenderManagerPtr pRenderer, RenderTexturePtr pInput, RenderTexturePtr pOutput)
	{
		pRenderer->SetRenderTarget(pOutput);
		pRenderer->ClearRenderTarget(0, math::Color4(0, 0, 0,0));
		
		m_pParamInputSize->SetParameterVector(math::Vector2((Real)pRenderer->GetFrameBufferWidth(), (Real)pRenderer->GetFrameBufferHeight()));
		m_pParamInputTex->SetParameterTexture(pInput->GetTexture(0));
		
		pRenderer->DrawFullScreenQuad(m_pMaterial);
	}
	void PostEffect_GaussianBlur::Release()
	{
		m_pParamInputSize	= nullptr;
		m_pParamInputTex	= nullptr;

		if(m_pMaterial)
		{
			m_pMaterial->Release();
			m_pMaterial.reset();
		}
	}
}
