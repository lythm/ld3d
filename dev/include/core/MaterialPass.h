#pragma once

namespace ld3d
{
	class EXPORT_CLASS MaterialPass
	{
	public:
		MaterialPass();
		virtual ~MaterialPass(void);

		virtual void											Apply();
		bool													Create(Sys_GraphicsPtr pGraphics);
		bool													Parse();
		void													Release();

		RenderStatePtr											GetRenderState();

		bool													Validate();
	private:
		RenderStatePtr											m_pRenderState;
		Sys_GraphicsPtr											m_pGraphics;

		

		GPUBufferPtr											m_pVSParameterBlock;
		GPUBufferPtr											m_pPSParameterBlock;
	};
}
