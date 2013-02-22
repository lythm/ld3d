#include "d11graphics_pch.h"
#include "D3D11RenderState.h"

namespace ld3d
{
	D3D11RenderState::D3D11RenderState(ID3D11DeviceContext* pContext)
	{
		m_pContext = pContext;

		m_pDevice = nullptr;

		m_pContext->GetDevice(&m_pDevice);

		ZeroMemory(&m_blendState, sizeof(m_blendState));
		m_blendState.AlphaToCoverageEnable							= false;
		m_blendState.IndependentBlendEnable							= false;
		m_blendState.RenderTarget[0].BlendEnable					= false;
		m_blendState.RenderTarget[0].SrcBlend						= D3D11_BLEND_ONE;
		m_blendState.RenderTarget[0].DestBlend						= D3D11_BLEND_ZERO;
		m_blendState.RenderTarget[0].BlendOp						= D3D11_BLEND_OP_ADD ;
		m_blendState.RenderTarget[0].SrcBlendAlpha					= D3D11_BLEND_ONE;
		m_blendState.RenderTarget[0].DestBlendAlpha					= D3D11_BLEND_ZERO ;
		m_blendState.RenderTarget[0].BlendOpAlpha					= D3D11_BLEND_OP_ADD;
		m_blendState.RenderTarget[0].RenderTargetWriteMask			= D3D11_COLOR_WRITE_ENABLE_ALL ;

		ZeroMemory(&m_rasterizeState, sizeof(m_rasterizeState));
		m_rasterizeState.FillMode									= D3D11_FILL_SOLID;
		m_rasterizeState.CullMode									= D3D11_CULL_BACK;
		m_rasterizeState.FrontCounterClockwise						= FALSE;
		m_rasterizeState.DepthBias									= 0 ;
		m_rasterizeState.SlopeScaledDepthBias						= 0.0f ;
		m_rasterizeState.DepthBiasClamp								= 0.0f ;
		m_rasterizeState.DepthClipEnable							= TRUE ;
		m_rasterizeState.ScissorEnable								= FALSE ;
		m_rasterizeState.MultisampleEnable							= FALSE ;
		m_rasterizeState.AntialiasedLineEnable						= FALSE ;


		ZeroMemory(&m_depthStencilState, sizeof(m_depthStencilState));
		m_depthStencilState.DepthEnable								= TRUE ;
		m_depthStencilState.DepthWriteMask							= D3D11_DEPTH_WRITE_MASK_ALL;
		m_depthStencilState.DepthFunc								= D3D11_COMPARISON_LESS ;
		m_depthStencilState.StencilEnable							= FALSE ;
		m_depthStencilState.StencilReadMask							= D3D11_DEFAULT_STENCIL_READ_MASK ;
		m_depthStencilState.StencilWriteMask						= D3D11_DEFAULT_STENCIL_WRITE_MASK ;
		m_depthStencilState.FrontFace.StencilFunc					= D3D11_COMPARISON_ALWAYS ;
		m_depthStencilState.FrontFace.StencilDepthFailOp			= D3D11_STENCIL_OP_KEEP ;
		m_depthStencilState.FrontFace.StencilPassOp					= D3D11_STENCIL_OP_KEEP ;
		m_depthStencilState.FrontFace.StencilFailOp					= D3D11_STENCIL_OP_KEEP;

		m_depthStencilState.BackFace.StencilFunc					= D3D11_COMPARISON_ALWAYS ;
		m_depthStencilState.BackFace.StencilDepthFailOp				= D3D11_STENCIL_OP_KEEP ;
		m_depthStencilState.BackFace.StencilPassOp					= D3D11_STENCIL_OP_KEEP ;
		m_depthStencilState.BackFace.StencilFailOp					= D3D11_STENCIL_OP_KEEP;


		m_blendFactor = math::Vector4();
		m_sampleMask = 0xffffffff;
		m_stencilRef = 0;
	}


	D3D11RenderState::~D3D11RenderState(void)
	{
	}
	bool D3D11RenderState::Create()
	{

		if(m_pBS)
		{
			m_pBS->Release();
			m_pBS = nullptr;
		}

		if(m_pRS)
		{
			m_pRS->Release();
			m_pRS = nullptr;
		}

		if(m_pDSS)
		{
			m_pDSS->Release();
			m_pDSS = nullptr;
		}

		if(FAILED(m_pDevice->CreateBlendState(&m_blendState, &m_pBS)))
		{
			return false;
		}


		if(FAILED(m_pDevice->CreateRasterizerState(&m_rasterizeState, &m_pRS)))
		{
			return false;
		}


		if(FAILED(m_pDevice->CreateDepthStencilState(&m_depthStencilState, &m_pDSS)))
		{
			return false;
		}

		return true;
	}
	void D3D11RenderState::Release()
	{
		if(m_pBS)
		{
			m_pBS->Release();
			m_pBS = nullptr;
		}

		if(m_pRS)
		{
			m_pRS->Release();
			m_pRS = nullptr;
		}

		if(m_pDSS)
		{
			m_pDSS->Release();
			m_pDSS = nullptr;
		}



		if(m_pDevice)
		{
			m_pDevice->Release();
			m_pDevice = nullptr;
		}

		m_pContext = nullptr;
	}
	void D3D11RenderState::Apply()
	{
		m_pContext->RSSetState(m_pRS);
		m_pContext->OMSetBlendState(m_pBS, m_blendFactor.v, m_sampleMask);
		m_pContext->OMSetDepthStencilState(m_pDSS, m_stencilRef);
	}
	void D3D11RenderState::Begin()
	{

	}

	void D3D11RenderState::End()
	{
		Create();
	}
	void D3D11RenderState::SetBlendFactor(const math::Vector4& val)
	{
		m_blendFactor = val;
	}
	void D3D11RenderState::SetStencilRef(uint32 val)
	{
		m_stencilRef = val;
	}
	void D3D11RenderState::SetBlendEnable(bool bEnable)
	{
		m_blendState.RenderTarget[0].BlendEnable = bEnable;
	}
	void D3D11RenderState::SetSrcBlend(RS_BLEND val)
	{
		m_blendState.RenderTarget[0].SrcBlend = (D3D11_BLEND)val;
	}
	void D3D11RenderState::SetDestBlend(RS_BLEND val)
	{
		m_blendState.RenderTarget[0].DestBlend = (D3D11_BLEND)val;
	}
	void D3D11RenderState::SetBlendOp(RS_BLEND_OP op)
	{
		m_blendState.RenderTarget[0].BlendOp = (D3D11_BLEND_OP)op;
	}
	void D3D11RenderState::SetSrcBlendAlpha(RS_BLEND val)
	{
		m_blendState.RenderTarget[0].SrcBlendAlpha = (D3D11_BLEND)val;
	}
	void D3D11RenderState::SetDestBlendAlpha(RS_BLEND val)
	{
		m_blendState.RenderTarget[0].DestBlendAlpha = (D3D11_BLEND)val;
	}
	void D3D11RenderState::SetBlendOpAlpha(RS_BLEND_OP op)
	{
		m_blendState.RenderTarget[0].BlendOpAlpha = (D3D11_BLEND_OP)op;
	}
	void D3D11RenderState::SetBlendColorWrite(RS_COLOR_WRITE val)
	{
		m_blendState.RenderTarget[0].RenderTargetWriteMask = val;
	}
	void D3D11RenderState::SetFillMode(RS_FILL_MODE val)
	{
		m_rasterizeState.FillMode = (D3D11_FILL_MODE)val;
	}
	void D3D11RenderState::SetCullMode(RS_CULL_MODE val)
	{
		m_rasterizeState.CullMode = (D3D11_CULL_MODE)val;
	}
	void D3D11RenderState::SetFrontCounterClockwise(bool val)
	{
		m_rasterizeState.FrontCounterClockwise = val;
	}
	void D3D11RenderState::SetDepthBias(uint32 val)
	{
		m_rasterizeState.DepthBias = val;
	}
	void D3D11RenderState::SetDepthBiasClamp(float val)
	{
		m_rasterizeState.DepthBiasClamp = val;
	}
	void D3D11RenderState::SetSlopeScaledDepthBias(float val)
	{
		m_rasterizeState.SlopeScaledDepthBias = val;
	}
	void D3D11RenderState::SetDepthClipEnable(bool val)
	{
		m_rasterizeState.DepthClipEnable = val;
	}
	void D3D11RenderState::SetDepthEnable(bool val)
	{
		m_depthStencilState.DepthEnable = val;
	}
	void D3D11RenderState::SetDepthWriteMask(RS_DEPTH_WRITE val)
	{
		m_depthStencilState.DepthWriteMask = (D3D11_DEPTH_WRITE_MASK)val;
	}
	void D3D11RenderState::SetDepthFunc(RS_COMPARISON_FUNC val)
	{
		m_depthStencilState.DepthFunc = (D3D11_COMPARISON_FUNC)val;
	}
	void D3D11RenderState::SetStencilEnable(bool val)
	{
		m_depthStencilState.StencilEnable = val;
	}
	void D3D11RenderState::SetStencilReadMask(uint8 mask)
	{
		m_depthStencilState.StencilReadMask = mask;
	}
	void D3D11RenderState::SetStencilWriteMask(uint8 mask)
	{
		m_depthStencilState.StencilWriteMask = mask;
	}
	void D3D11RenderState::SetFrontFaceStencilFailOp(RS_STENCIL_OP op)
	{
		m_depthStencilState.FrontFace.StencilFailOp = (D3D11_STENCIL_OP)op;
	}
	void D3D11RenderState::SetFrontFaceStencilDepthFailOp(RS_STENCIL_OP op)
	{
		m_depthStencilState.FrontFace.StencilDepthFailOp = (D3D11_STENCIL_OP)op;
	}
	void D3D11RenderState::SetFrontFaceStencilPassOp(RS_STENCIL_OP op)
	{
		m_depthStencilState.FrontFace.StencilPassOp = (D3D11_STENCIL_OP)op;
	}
	void D3D11RenderState::SetFrontFaceStencilFunc(RS_COMPARISON_FUNC val)
	{
		m_depthStencilState.FrontFace.StencilFunc = (D3D11_COMPARISON_FUNC)val;
	}
	void D3D11RenderState::SetBackFaceStencilFailOp(RS_STENCIL_OP op)
	{
		m_depthStencilState.BackFace.StencilFailOp = (D3D11_STENCIL_OP)op;
	}
	void D3D11RenderState::SetBackFaceStencilDepthFailOp(RS_STENCIL_OP op)
	{
		m_depthStencilState.BackFace.StencilDepthFailOp = (D3D11_STENCIL_OP)op;
	}
	void D3D11RenderState::SetBackFaceStencilPassOp(RS_STENCIL_OP op)
	{
		m_depthStencilState.BackFace.StencilPassOp = (D3D11_STENCIL_OP)op;
	}
	void D3D11RenderState::SetBackFaceStencilFunc(RS_COMPARISON_FUNC val)
	{
		m_depthStencilState.BackFace.StencilFunc = (D3D11_COMPARISON_FUNC)val;
	}
}
