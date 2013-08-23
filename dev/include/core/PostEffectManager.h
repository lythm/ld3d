#pragma once


namespace ld3d
{
	class _DLL_CLASS PostEffectManager
	{
	public:
		PostEffectManager(void);
		virtual ~PostEffectManager(void);

		bool													Initialize(RenderManagerPtr pRenderManager);
		void													Release();

		void													Render();

		RenderTexturePtr										GetInput();
		RenderTexturePtr											GetOutput();

		int														GetEffectCount();

		void													Resize(int cx, int cy);

		void													RenderToFrameBuffer();

		void													AddEffect(PostEffectPtr pEffect);
	private:
		bool													CreateRT(int w, int h);
	private:
		void													SwapRenderTarget();

	private:
		RenderTexturePtr										m_pOutput;
		RenderTexturePtr										m_pInput;

		std::vector<PostEffectPtr>								m_effects;

		RenderManagerPtr										m_pRenderManager;

		MaterialPtr												m_pFinalMaterial;

		MaterialParameterPtr									m_pParamOutput;
	};
}
