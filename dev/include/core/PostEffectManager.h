#pragma once


namespace ld3d
{
	class EXPORT_CLASS PostEffectManager
	{
	public:
		PostEffectManager(void);
		virtual ~PostEffectManager(void);

		bool										Initialize(RenderManagerPtr pRenderManager);
		void										Release();

		void										Render();

		RenderTargetPtr								GetInput();
		RenderTargetPtr								GetOutput();

		int											GetEffectCount();

		void										Resize(int cx, int cy);

		void										RenderToFrameBuffer();

		void										AddEffect(PostEffectPtr pEffect);
	private:
		bool										CreateRT(int w, int h);
	private:
		void										SwapRenderTarget();

	private:
		RenderTargetPtr								m_pOutput;
		RenderTargetPtr								m_pInput;

		std::vector<PostEffectPtr>					m_effects;

		RenderManagerPtr								m_pRenderManager;

		MaterialPtr									m_pFinalMaterial;
	};


}