#pragma once

namespace ld3d
{
	class RenderState2
	{
	public:
		virtual void										Begin()													= 0;
		virtual void										End()													= 0;
		
		virtual void										Release()												= 0;
		
		
		virtual void										SetBlendFactor(const math::Vector4& val)				= 0;
		virtual void										SetBlendEnable(bool bEnable)							= 0;
		
		virtual void										SetBlendOp(RS_BLEND_OP op, RS_BLEND_OP alpha_op)		= 0;
		virtual void										SetBlendVariable(RS_BLEND srcRGB, 
																		RS_BLEND dstRGB, 
																		RS_BLEND srcAlpha, 
																		RS_BLEND dstAlpha)							= 0;
		
		virtual void										SetColorWrite(RS_COLOR_WRITE val)						= 0;
		
		virtual void										SetFillMode(RS_FILL_MODE val)							= 0;
		virtual void										SetCullMode(RS_CULL_MODE val)							= 0;
		virtual void										SetFrontCounterClockwise(bool val)						= 0;

		virtual void										SetDepthBias(uint32 val)								= 0;
		virtual void										SetDepthBiasClamp(float val)							= 0;
		virtual void										SetSlopeScaledDepthBias(float val)						= 0;
		virtual void										SetDepthClipEnable(bool val)							= 0;

		virtual void										SetDepthEnable(bool val)								= 0;
		virtual void										SetDepthWriteMask(RS_DEPTH_WRITE val)					= 0;
		virtual void										SetDepthFunc(RS_COMPARISON_FUNC val)					= 0;
		
		
		virtual void										SetStencilEnable(bool val)								= 0;
		virtual void										SetFrontFaceStencilOP(RS_STENCIL_OP sfail, 
																		RS_STENCIL_OP dfaile, 
																		RS_STENCIL_OP pass)							= 0;
		virtual void										SetBackFaceStencilOP(RS_STENCIL_OP sfail, 
																		RS_STENCIL_OP dfaile, 
																		RS_STENCIL_OP pass)							= 0;
		
		virtual void										SetFrontFaceStencilWriteMask(uint8 mask)				= 0;
		virtual void										SetBackFaceStencilWriteMask(uint8 mask)					= 0;

		virtual void										SetFrontFaceStencilFunc(RS_COMPARISON_FUNC val, 
																		uint32 ref, 
																		uint32 mask)								= 0;
		virtual void										SetBackFaceStencilFunc(RS_COMPARISON_FUNC val, 
																		uint32 ref, 
																		uint32 mask)								= 0;
		
	protected:
		RenderState2(void){}
		virtual ~RenderState2(void){}
	};
	
}
