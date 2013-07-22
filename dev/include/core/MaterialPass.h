#pragma once

#include "core/ShaderProgram.h"

namespace ld3d
{
	class EXPORT_CLASS MaterialPass
	{
	public:

		MaterialPass(const std::string& name, Sys_Graphics2Ptr pGraphics);
		virtual ~MaterialPass(void);

		virtual void											Apply();
		void													Release();

		RenderState2Ptr											GetRenderState();

		bool													Validate();

		void													AttachProgram(ShaderProgramPtr pProgram);
		void													AttachRenderState(RenderState2Ptr pState);
		void													AddSamplerLink(const std::string& tex, SamplerStatePtr pSampler);

		const std::string										GetName() const;

		ShaderProgramPtr										GetProgram();

	private:

		void													ApplySamplers();
	private:

		RenderState2Ptr											m_pRenderState;
		Sys_Graphics2Ptr										m_pGraphics;

		ShaderProgramPtr										m_pProgram;
		std::vector<SamplerStatePtr>							m_Samplers;

		std::string												m_name;
	};
}
