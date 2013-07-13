#include "ogl4graphics_pch.h"
#include "OGL4RenderState.h"


namespace ld3d
{
	OGL4RenderState::OGL4RenderState(void)
	{
		m_bRecording = false;
	}


	OGL4RenderState::~OGL4RenderState(void)
	{
	}
	void OGL4RenderState::Begin()
	{
		m_bRecording = true;
		m_commands.clear();
	}
	void OGL4RenderState::End()
	{
		m_bRecording = false;
	}

	void OGL4RenderState::Release()
	{
		m_commands.clear();

	}
	void OGL4RenderState::SetBlendFactor(const math::Vector4& val)
	{
		//glBlendColor
	}
	void OGL4RenderState::SetStencilRef(uint32 val)
	{

	}
	void OGL4RenderState::SetBlendEnable(bool bEnable)
	{
	}
	void OGL4RenderState::SetSrcBlend(RS_BLEND val)
	{
	}
	void OGL4RenderState::SetDestBlend(RS_BLEND val)
	{
	}
	void OGL4RenderState::SetBlendOp(RS_BLEND_OP op)
	{
	}
	void OGL4RenderState::SetSrcBlendAlpha(RS_BLEND val)
	{
	}
	void OGL4RenderState::SetDestBlendAlpha(RS_BLEND val)
	{
	}
	void OGL4RenderState::SetBlendOpAlpha(RS_BLEND_OP op)
	{
	}
	void OGL4RenderState::SetBlendColorWrite(RS_COLOR_WRITE val)
	{
	}
	void OGL4RenderState::SetFillMode(RS_FILL_MODE val)
	{
	}
	void OGL4RenderState::SetCullMode(RS_CULL_MODE val)
	{
	}
	void OGL4RenderState::SetFrontCounterClockwise(bool val)
	{
	}
	void OGL4RenderState::SetDepthBias(uint32 val)
	{
	}
	void OGL4RenderState::SetDepthBiasClamp(float val)
	{
	}
	void OGL4RenderState::SetSlopeScaledDepthBias(float val)
	{
	}
	void OGL4RenderState::SetDepthClipEnable(bool val)
	{
	}
	void OGL4RenderState::SetDepthEnable(bool val)
	{
	}
	void OGL4RenderState::SetDepthWriteMask(RS_DEPTH_WRITE val)
	{
	}
	void OGL4RenderState::SetDepthFunc(RS_COMPARISON_FUNC val)
	{
	}
	void OGL4RenderState::SetStencilEnable(bool val)
	{
	}
	void OGL4RenderState::SetStencilReadMask(uint8 mask)
	{
	}
	void OGL4RenderState::SetStencilWriteMask(uint8 mask)
	{
	}
	void OGL4RenderState::SetFrontFaceStencilFailOp(RS_STENCIL_OP op)
	{
	}
	void OGL4RenderState::SetFrontFaceStencilDepthFailOp(RS_STENCIL_OP op)
	{
	}
	void OGL4RenderState::SetFrontFaceStencilPassOp(RS_STENCIL_OP op)
	{
	}
	void OGL4RenderState::SetFrontFaceStencilFunc(RS_COMPARISON_FUNC val)
	{
	}
	void OGL4RenderState::SetBackFaceStencilFailOp(RS_STENCIL_OP op)
	{
	}
	void OGL4RenderState::SetBackFaceStencilDepthFailOp(RS_STENCIL_OP op)
	{
	}
	void OGL4RenderState::SetBackFaceStencilPassOp(RS_STENCIL_OP op)
	{
	}
	void OGL4RenderState::SetBackFaceStencilFunc(RS_COMPARISON_FUNC val)
	{
	}
	void OGL4RenderState::Apply()
	{
		for(auto f : m_commands)
		{
			f();
		}
	}
	void OGL4RenderState::AddCommand(const std::function<void ()>& command)
	{
		m_bRecording ? m_commands.push_back(command) : 0;
	}
}
