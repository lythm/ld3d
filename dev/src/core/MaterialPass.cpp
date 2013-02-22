#include "core_pch.h"
#include "..\..\include\core\MaterialPass.h"

#include "core\Sys_Graphics.h"
#include "core\RenderState.h"
#include "core\VertexShader.h"
#include "core\PixelShader.h"

namespace ld3d
{
	MaterialPass::MaterialPass(Sys_GraphicsPtr pGraphics)
	{
		m_pGraphics = pGraphics;
	}


	MaterialPass::~MaterialPass(void)
	{
	}
	void MaterialPass::Apply()
	{
		m_pGraphics->SetRenderState(m_pRenderState);
		m_pGraphics->SetVertexShader(m_pVertexShader);
		m_pGraphics->SetPixelShader(m_pPixelShader);

	}
	RenderStatePtr MaterialPass::GetRenderState()
	{
		return m_pRenderState;
	}
	void MaterialPass::SetVertexShader(VertexShaderPtr pShader)
	{
		m_pVertexShader = pShader;
	}
	void MaterialPass::SetPixelShader(PixelShaderPtr pShader)
	{
		m_pPixelShader = pShader;
	}
	void MaterialPass::Release()
	{
		if(m_pRenderState)
		{
			m_pRenderState->Release();
			m_pRenderState.reset();
		}

		if(m_pVertexShader)
		{
			m_pVertexShader->Release();
			m_pVertexShader.reset();
		}

		if(m_pPixelShader)
		{
			m_pPixelShader->Release();
			m_pPixelShader.reset();
		}

	}
}
