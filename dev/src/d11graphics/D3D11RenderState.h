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


		/* BOOL                       DepthEnable;
  D3D11_DEPTH_WRITE_MASK     DepthWriteMask;
  D3D11_COMPARISON_FUNC      DepthFunc;
  BOOL                       StencilEnable;
  UINT8                      StencilReadMask;
  UINT8                      StencilWriteMask;
  D3D11_DEPTH_STENCILOP_DESC FrontFace;
  D3D11_DEPTH_STENCILOP_DESC BackFace;*/

		void										SetDepthEnable();
		void										SetDepthWriteMask();
		void										SetDepthFunc();
		void										SetStencilEnable();
		void										SetStencilReadMask();
		void										SetStencilWriteMask();

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
