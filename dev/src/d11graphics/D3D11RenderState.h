#pragma once

#include "core\RenderState.h"

namespace ld3d
{
	class D3D11RenderState : public RenderState
	{
	public:
		D3D11RenderState(ID3D11DeviceContext* pContext);
		virtual ~D3D11RenderState(void);

		bool										Create();
		void										Release();

		void										Begin();

		void										SetBlendFactor(const math::Vector4& val);
		void										SetStencilRef(uint32 val);

		void										SetBlendEnable(bool bEnable);
		void										SetSrcBlend(RS_BLEND val);
		void										SetDestBlend(RS_BLEND val);
		void										SetBlendOp(RS_BLEND_OP op);
		void										SetSrcBlendAlpha(RS_BLEND val);
		void										SetDestBlendAlpha(RS_BLEND val);
		void										SetBlendOpAlpha(RS_BLEND_OP op);
		void										SetBlendColorWrite(RS_COLOR_WRITE val);

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
		void										SetStencilReadMask(uint8 mask);
		void										SetStencilWriteMask(uint8 mask);

		void										SetFrontFaceStencilFailOp(RS_STENCIL_OP op);
		void										SetFrontFaceStencilDepthFailOp(RS_STENCIL_OP op);
		void										SetFrontFaceStencilPassOp(RS_STENCIL_OP op);
		void										SetFrontFaceStencilFunc(RS_COMPARISON_FUNC val);

		void										SetBackFaceStencilFailOp(RS_STENCIL_OP op);
		void										SetBackFaceStencilDepthFailOp(RS_STENCIL_OP op);
		void										SetBackFaceStencilPassOp(RS_STENCIL_OP op);
		void										SetBackFaceStencilFunc(RS_COMPARISON_FUNC val);

		void										End();

		void										Apply();
	private:
		ID3D11DeviceContext*						m_pContext;
		ID3D11Device*								m_pDevice;

		ID3D11BlendState*							m_pBS;
		ID3D11RasterizerState*						m_pRS;
		ID3D11DepthStencilState*					m_pDSS;

		D3D11_BLEND_DESC							m_blendState;
		D3D11_RASTERIZER_DESC						m_rasterizeState;
		D3D11_DEPTH_STENCIL_DESC					m_depthStencilState;

		math::Vector4								m_blendFactor;
		unsigned int								m_sampleMask;
		unsigned int								m_stencilRef;
	};
}
