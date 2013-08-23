#pragma once

#include "core/ShaderProgram.h"

namespace ld3d
{
	class _DLL_CLASS MaterialPass
	{
	public:

		MaterialPass(const std::string& name, Sys_GraphicsPtr pGraphics);
		virtual ~MaterialPass(void);

		virtual void											Apply();
		void													Release();

		RenderStatePtr											GetRenderState();

		bool													Validate();

		void													AttachProgram(ShaderProgramPtr pProgram);
		void													AttachRenderState(RenderStatePtr pState);
		void													AddSamplerLink(const std::string& tex, SamplerStatePtr pSampler);

		const std::string										GetName() const;

		ShaderProgramPtr										GetProgram();

	private:

		void													ApplySamplers();
	private:

		RenderStatePtr											m_pRenderState;
		Sys_GraphicsPtr										m_pGraphics;

		ShaderProgramPtr										m_pProgram;
		std::vector<SamplerStatePtr>							m_Samplers;

		std::string												m_name;
	};
}
