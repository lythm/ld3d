#include "ogl4graphics_pch.h"
#include "OGL4RenderState.h"
#include "OGL4Convert.h"


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
		AddCommand(std::bind(glBlendColor, val.x, val.y, val.z, val.w));
		
	}
	void OGL4RenderState::SetBlendEnable(bool bEnable)
	{
		AddCommand(std::bind(bEnable ? glEnable : glDisable, GL_BLEND));
	}
	void OGL4RenderState::SetBlendOp(RS_BLEND_OP op, RS_BLEND_OP alpha_op)
	{
		AddCommand(std::bind(glBlendEquationSeparate, OGL4Convert::BlendOPToGL(op), OGL4Convert::BlendOPToGL(alpha_op)));
		
	}
	void OGL4RenderState::SetBlendVariable(RS_BLEND srcRGB, RS_BLEND dstRGB, RS_BLEND srcAlpha, RS_BLEND dstAlpha)
	{
		AddCommand(std::bind(glBlendFuncSeparate, OGL4Convert::BlendToGL(srcRGB), OGL4Convert::BlendToGL(dstRGB), OGL4Convert::BlendToGL(srcAlpha), OGL4Convert::BlendToGL(dstAlpha)));
	}

	void OGL4RenderState::SetColorWrite(RS_COLOR_WRITE val)
	{
		AddCommand(std::bind(glColorMask,
				val & RS_COLOR_WRITE_ENABLE_RED ? GL_TRUE : GL_FALSE,
				val & RS_COLOR_WRITE_ENABLE_GREEN ? GL_TRUE : GL_FALSE,
				val & RS_COLOR_WRITE_ENABLE_BLUE ? GL_TRUE : GL_FALSE,
				val & RS_COLOR_WRITE_ENABLE_ALPHA ? GL_TRUE : GL_FALSE));

	}

	

	void OGL4RenderState::SetFillMode(RS_FILL_MODE val)
	{
		AddCommand(std::bind(glPolygonMode, GL_FRONT_AND_BACK, OGL4Convert::FillModeToGL(val)));
	}
	void OGL4RenderState::SetCullMode(RS_CULL_MODE val)
	{
		switch(val)
		{
		case RS_CULL_NONE:
			AddCommand(std::bind(glDisable, GL_CULL_FACE));
			break;
		case RS_CULL_BACK:
			AddCommand(std::bind(glEnable, GL_CULL_FACE));
			AddCommand(std::bind(glCullFace, GL_BACK));
			break;
		case RS_CULL_FRONT:
			AddCommand(std::bind(glEnable, GL_CULL_FACE));
			AddCommand(std::bind(glCullFace, GL_FRONT));
			break;
		default:
			assert(0);
			break;
		}
	}
	void OGL4RenderState::SetFrontCounterClockwise(bool val)
	{
		AddCommand(std::bind(glFrontFace, val ? GL_CCW : GL_CW));
	}
	void OGL4RenderState::SetDepthBias(uint32 val)
	{
		AddCommand(std::bind(glPolygonOffset, 0, val));
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
		AddCommand(std::bind(val ? glEnable : glDisable, GL_DEPTH_TEST));
	}
	void OGL4RenderState::SetDepthWriteMask(RS_DEPTH_WRITE val)
	{
		switch(val)
		{
		case RS_DEPTH_WRITE_MASK_ZERO:
			AddCommand(std::bind(glDepthMask, GL_FALSE));
			break;
		case RS_DEPTH_WRITE_MASK_ALL:
			AddCommand(std::bind(glDepthMask, GL_TRUE));
			break;
		default:
			assert(0);
			break;
		}
	}
	void OGL4RenderState::SetDepthFunc(RS_COMPARISON_FUNC val)
	{
		AddCommand(std::bind(glDepthFunc, OGL4Convert::CompareFuncToGL(val))); 
	}
	void OGL4RenderState::SetStencilEnable(bool val)
	{
		AddCommand(std::bind(glEnable, GL_STENCIL_TEST));
	}
	void OGL4RenderState::SetFrontFaceStencilOP(RS_STENCIL_OP sfail, RS_STENCIL_OP dfaile, RS_STENCIL_OP pass)
	{
		AddCommand(std::bind(glStencilOpSeparate, GL_FRONT, OGL4Convert::StencilOPToGL(sfail), OGL4Convert::StencilOPToGL(sfail), OGL4Convert::StencilOPToGL(sfail)));
	}
	void OGL4RenderState::SetBackFaceStencilOP(RS_STENCIL_OP sfail, RS_STENCIL_OP dfaile, RS_STENCIL_OP pass)
	{
		AddCommand(std::bind(glStencilOpSeparate, GL_BACK, OGL4Convert::StencilOPToGL(sfail), OGL4Convert::StencilOPToGL(sfail), OGL4Convert::StencilOPToGL(sfail)));
	}


	void OGL4RenderState::SetFrontFaceStencilWriteMask(uint8 mask)
	{
		AddCommand(std::bind(glStencilMaskSeparate, GL_FRONT, mask));
	}
	void OGL4RenderState::SetBackFaceStencilWriteMask(uint8 mask)
	{
		AddCommand(std::bind(glStencilMaskSeparate, GL_BACK, mask));
	}
		
	void OGL4RenderState::SetFrontFaceStencilFunc(RS_COMPARISON_FUNC val, uint32 ref, uint32 mask)
	{
		AddCommand(std::bind(glStencilFuncSeparate, GL_FRONT, OGL4Convert::CompareFuncToGL(val), ref, mask));
	}
	void OGL4RenderState::SetBackFaceStencilFunc(RS_COMPARISON_FUNC val, uint32 ref, uint32 mask)
	{
		AddCommand(std::bind(glStencilFuncSeparate, GL_BACK, OGL4Convert::CompareFuncToGL(val), ref, mask));
	}

	void OGL4RenderState::Apply()
	{
		for(const auto& f : m_commands)
		{
			f();
		}
	}
	void OGL4RenderState::AddCommand(const std::function<void ()>& command)
	{
		if(command == false)
		{
			return;
		}
		m_bRecording ? m_commands.push_back(command) : (void)0;
	
	}
}
