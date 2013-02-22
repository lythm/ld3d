#pragma once

namespace ld3d
{
	class MaterialPass
	{
	public:
		MaterialPass(Sys_GraphicsPtr pGraphics);
		virtual ~MaterialPass(void);

		virtual void											Apply();

		void													Release();

		RenderStatePtr											GetRenderState();
		void													SetVertexShader(VertexShaderPtr pShader);
		void													SetPixelShader(PixelShaderPtr pShader);
	private:
		RenderStatePtr											m_pRenderState;
		Sys_GraphicsPtr											m_pGraphics;

		VertexShaderPtr											m_pVertexShader;
		PixelShaderPtr											m_pPixelShader;
	};
}