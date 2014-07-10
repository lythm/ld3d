#pragma once

namespace ld3d
{
	class RenderSystem_Deferred
	{
	public:
		RenderSystem_Deferred(void);
		virtual ~RenderSystem_Deferred(void);

		bool												Initialize(RenderManagerPtr pRenderManager, DepthStencilBufferPtr pDSBuffer);
		void												Release();

		void												ResizeFrameBuffer(int w, int h, DepthStencilBufferPtr pDSBuffer);
		void												Render(RenderQueuePtr pRenderQueue, CameraPtr pCamera, RenderTargetPtr pTarget);

		RenderTexturePtr									GetABuffer() const;
		RenderTexturePtr									GetGBuffer() const;

		void												SetMaterialABuffer(MaterialPtr pMaterial);
		void												SetMaterialGBuffer(MaterialPtr pMaterial);
	private:
		bool												ResizeABuffer(int w, int h);
		bool												ResizeGBuffer(int w, int h);

		void												DR_Light_Pass(CameraPtr pCamera);
		void												DR_G_Pass(RenderQueuePtr pRenderQueue);
		void												DR_Merge_Pass(RenderTargetPtr pTarget);
	private:

		RenderManagerPtr									m_pRenderManager;
		Sys_GraphicsPtr										m_pGraphics;
		LightManagerPtr										m_pLightManager;
		RenderParametersPtr									m_pRenderParams;

		RenderTexturePtr									m_pGBuffer;
		RenderTexturePtr									m_pABuffer;
		DepthStencilBufferPtr								m_pDSBuffer;

		MaterialPtr											m_pMergePassMaterial;
	};
}