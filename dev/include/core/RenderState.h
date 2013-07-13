#pragma once

namespace ld3d
{
	class RenderState
	{
	public:

		


		virtual void										Begin()														= 0;

		virtual void										End()														= 0;

		virtual void										Release()													= 0;


		virtual void										SetBlendFactor(const math::Vector4& val)					= 0;
		virtual void										SetStencilRef(uint32 val)									= 0;
		
		virtual void										SetBlendEnable(bool bEnable)								= 0;
		virtual void										SetSrcBlend(RS_BLEND val)									= 0;
		virtual void										SetDestBlend(RS_BLEND val)									= 0;
		virtual void										SetBlendOp(RS_BLEND_OP op)									= 0;
		virtual void										SetSrcBlendAlpha(RS_BLEND val)								= 0;
		virtual void										SetDestBlendAlpha(RS_BLEND val)								= 0;
		virtual void										SetBlendOpAlpha(RS_BLEND_OP op)								= 0;
		virtual void										SetBlendColorWrite(RS_COLOR_WRITE val)						= 0;
		
		virtual void										SetFillMode(RS_FILL_MODE val)								= 0;
		virtual void										SetCullMode(RS_CULL_MODE val)								= 0;
		virtual void										SetFrontCounterClockwise(bool val)							= 0;
		virtual void										SetDepthBias(uint32 val)									= 0;
		virtual void										SetDepthBiasClamp(float val)								= 0;
		virtual void										SetSlopeScaledDepthBias(float val)							= 0;
		virtual void										SetDepthClipEnable(bool val)								= 0;
		
		virtual void										SetDepthEnable(bool val)									= 0;
		virtual void										SetDepthWriteMask(RS_DEPTH_WRITE val)						= 0;
		virtual void										SetDepthFunc(RS_COMPARISON_FUNC val)						= 0;
		virtual void										SetStencilEnable(bool val)									= 0;
		virtual void										SetStencilReadMask(uint8 mask)								= 0;
		virtual void										SetStencilWriteMask(uint8 mask)								= 0;
		
		virtual void										SetFrontFaceStencilFailOp(RS_STENCIL_OP op)					= 0;
		virtual void										SetFrontFaceStencilDepthFailOp(RS_STENCIL_OP op)			= 0;
		virtual void										SetFrontFaceStencilPassOp(RS_STENCIL_OP op)					= 0;
		virtual void										SetFrontFaceStencilFunc(RS_COMPARISON_FUNC val)				= 0;
		
		virtual void										SetBackFaceStencilFailOp(RS_STENCIL_OP op)					= 0;
		virtual void										SetBackFaceStencilDepthFailOp(RS_STENCIL_OP op)				= 0;
		virtual void										SetBackFaceStencilPassOp(RS_STENCIL_OP op)					= 0;
		virtual void										SetBackFaceStencilFunc(RS_COMPARISON_FUNC val)				= 0;
		
	protected:
		RenderState(void){}
		virtual ~RenderState(void){}
	};


	struct DepthStencilState
	{
		DepthStencilState();

		void												ResetToDefault()
		{

		}



	};
}
