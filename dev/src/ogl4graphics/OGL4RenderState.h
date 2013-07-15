#pragma once


#include "core/RenderState.h"

namespace ld3d
{
	class OGL4RenderState : public RenderState2
	{
	public:
		OGL4RenderState(void);
		virtual ~OGL4RenderState(void);


		void										Begin();
		void										End();

		void										Release();
		void										Apply();


		void										SetBlendFactor(const math::Vector4& val);
		void										SetBlendEnable(bool bEnable);

		void										SetBlendOp(RS_BLEND_OP op, RS_BLEND_OP alpha_op);
		void										SetBlendVariable(RS_BLEND srcRGB, RS_BLEND dstRGB, RS_BLEND srcAlpha, RS_BLEND dstAlpha);

		void										SetColorWrite(RS_COLOR_WRITE val);

		void										SetFillMode(RS_FILL_MODE val);
		void										SetCullMode(RS_CULL_MODE val);
		void										SetFrontCounterClockwise(bool val);

		void										SetDepthBias(uint32 val);
		void										SetDepthBiasClamp(float val);
		void										SetSlopeScaledDepthBias(float val);
		void										SetDepthClipEnable(bool val);

		void										SetDepthEnable(bool val);
		void										SetDepthWriteMask(RS_DEPTH_WRITE val);
		void										SetDepthFunc(RS_COMPARISON_FUNC val);


		void										SetStencilEnable(bool val);
		void										SetFrontFaceStencilOP(RS_STENCIL_OP sfail, RS_STENCIL_OP dfaile, RS_STENCIL_OP pass);
		void										SetBackFaceStencilOP(RS_STENCIL_OP sfail, RS_STENCIL_OP dfaile, RS_STENCIL_OP pass);
		
		void										SetFrontFaceStencilWriteMask(uint8 mask);
		void										SetBackFaceStencilWriteMask(uint8 mask);
		
		void										SetFrontFaceStencilFunc(RS_COMPARISON_FUNC val, uint32 ref, uint32 mask);
		void										SetBackFaceStencilFunc(RS_COMPARISON_FUNC val, uint32 ref, uint32 mask);
		
	private:
		void										AddCommand(const std::function<void ()>& command);
		bool										m_bRecording;
	private:

		std::vector<std::function<void ()> >		m_commands;
	};
}

