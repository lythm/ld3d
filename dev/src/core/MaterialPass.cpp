#include "core_pch.h"
#include "core/MaterialPass.h"

#include "core/Sys_Graphics.h"
#include "core/RenderState.h"
#include "core/SamplerState.h"


namespace ld3d
{
	MaterialPass::MaterialPass(const std::string& name, Sys_GraphicsPtr pGraphics)
	{
		m_name = name;
		m_pGraphics = pGraphics;
	}


	MaterialPass::~MaterialPass(void)
	{
	}
	
	void MaterialPass::Apply()
	{
		m_pGraphics->SetRenderState(m_pRenderState);

		m_pGraphics->SetShaderProgram(m_pProgram);

	}
	RenderStatePtr MaterialPass::GetRenderState()
	{
		return m_pRenderState;
	}
	
	void MaterialPass::Release()
	{
		_release_and_reset(m_pRenderState);


		for(auto v : m_Samplers)
		{
			v->Release();
		}
		m_Samplers.clear();

		_release_and_reset(m_pProgram);

	}
	bool MaterialPass::Validate()
	{
		return m_pProgram->Validate();
	}
	void MaterialPass::AttachProgram(ShaderProgramPtr pProgram)
	{
		m_pProgram = pProgram;
	}
	void MaterialPass::AttachRenderState(RenderStatePtr pState)
	{
		m_pRenderState = pState;
	}
	void MaterialPass::AddSamplerLink(const std::string& tex, SamplerStatePtr pSampler)
	{
		if(pSampler == nullptr || m_pProgram == nullptr)
		{
			return;
		}

		ShaderProgram::ParameterID param = m_pProgram->FindParameterByName(tex.c_str());
		
		m_pProgram->SetParameterSampler(param, pSampler);

		m_Samplers.push_back(pSampler);
	}
	const std::string MaterialPass::GetName() const
	{
		return m_name;
	}
	ShaderProgramPtr MaterialPass::GetProgram()
	{
		return m_pProgram;
	}
}

