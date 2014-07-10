#pragma once


namespace ld3d
{
	class _DLL_CLASS RenderSystem_Post
	{
	public:
		RenderSystem_Post(void);
		virtual ~RenderSystem_Post(void);

		bool													Initialize(RenderManagerPtr pRenderManager);
		void													Release();

		void													Render(const std::vector<PostEffectPtr>& effects);
		void													Render(PostEffectPtr pEffect);

		RenderTexturePtr										GetIn();
		RenderTexturePtr										GetOut();

		void													Resize(int cx, int cy);

		void													RenderFinal(RenderTargetPtr pTarget);
	private:
		bool													CreateRT(int w, int h);
	private:
		void													SwapRenderTarget();

	private:
		RenderTexturePtr										m_pOut;
		RenderTexturePtr										m_pIn;

		RenderManagerPtr										m_pRenderManager;

		MaterialPtr												m_pFinalMaterial;

		MaterialParameterPtr									m_pFinalParam;
	};
}
