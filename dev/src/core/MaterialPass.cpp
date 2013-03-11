#include "core_pch.h"
#include "..\..\include\core\MaterialPass.h"

#include "core\Sys_Graphics.h"
#include "core\RenderState.h"
#include "core\VertexShader.h"
#include "core\PixelShader.h"
#include "core\GPUBuffer.h"

namespace ld3d
{
	MaterialPass::MaterialPass()
	{
		
	}


	MaterialPass::~MaterialPass(void)
	{
	}
	bool MaterialPass::Create(Sys_GraphicsPtr pGraphics)
	{	
		m_pGraphics = pGraphics;

		m_pRenderState = m_pGraphics->CreateRenderState();

		return true;
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
		if(m_pVSParameterBlock)
		{
			m_pVSParameterBlock->Release();
			m_pVSParameterBlock.reset();
		}

		if(m_pPSParameterBlock)
		{
			m_pPSParameterBlock->Release();
			m_pPSParameterBlock.reset();
		}

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
	bool MaterialPass::Validate()
	{
		return true;
	}
	bool MaterialPass::Parse()
	{
		return true;
	}
}
