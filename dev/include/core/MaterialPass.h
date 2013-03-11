#pragma once

namespace ld3d
{
	class MaterialPass
	{
	public:
		MaterialPass();
		virtual ~MaterialPass(void);

		virtual void											Apply();
		bool													Create(Sys_GraphicsPtr pGraphics);
		bool													Parse();
		void													Release();

		RenderStatePtr											GetRenderState();
		void													SetVertexShader(VertexShaderPtr pShader);
		void													SetPixelShader(PixelShaderPtr pShader);

		bool													Validate();
	private:
		RenderStatePtr											m_pRenderState;
		Sys_GraphicsPtr											m_pGraphics;

		VertexShaderPtr											m_pVertexShader;
		PixelShaderPtr											m_pPixelShader;

		GPUBufferPtr											m_pVSParameterBlock;
		GPUBufferPtr											m_pPSParameterBlock;
	};
}
