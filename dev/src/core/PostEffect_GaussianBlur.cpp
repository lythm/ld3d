#include "core_pch.h"
#include "..\..\include\core\PostEffect_GaussianBlur.h"
#include "core\RenderManager.h"
#include "core\Material.h"
#include "core\VertexFormat.h"
#include "core\RenderTarget.h"

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
		VertexElement vf[] = 
		{
			VertexElement(0, VertexElement::POSITION,G_FORMAT_R32G32B32_FLOAT),
		};
		VertexFormat format;

		format.SetElement(vf, 1);

		m_pMaterial->SetVertexFormat(format);

	
		return true;

	}
	void PostEffect_GaussianBlur::Render(RenderManagerPtr pRenderer, RenderTargetPtr pInput, RenderTargetPtr pOutput)
	{
		pRenderer->SetRenderTarget(pOutput);
		pRenderer->ClearRenderTarget(pOutput, 0, math::Color4(0, 0, 0,0));
		
		m_pMaterial->SetTextureByName("tex_input", pInput->AsTexture(0));
		m_pMaterial->SetVectorByName("g_input_size", math::Vector2(pRenderer->GetFrameBufferWidth(), pRenderer->GetFrameBufferHeight()));

		pRenderer->DrawFullScreenQuad(m_pMaterial);
	}
	void PostEffect_GaussianBlur::Release()
	{
		if(m_pMaterial)
		{
			m_pMaterial->Release();
			m_pMaterial.reset();
		}
	}
}
