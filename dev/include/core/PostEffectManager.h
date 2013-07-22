#pragma once


namespace ld3d
{
	class EXPORT_CLASS PostEffectManager
	{
	public:
		PostEffectManager(void);
		virtual ~PostEffectManager(void);

		bool													Initialize(RenderManagerPtr pRenderManager);
		void													Release();

		void													Render();

		RenderTexture2Ptr										GetInput();
		RenderTexture2Ptr											GetOutput();

		int														GetEffectCount();

		void													Resize(int cx, int cy);

		void													RenderToFrameBuffer();

		void													AddEffect(PostEffectPtr pEffect);
	private:
		bool													CreateRT(int w, int h);
	private:
		void													SwapRenderTarget();

	private:
		RenderTexture2Ptr											m_pOutput;
		RenderTexture2Ptr											m_pInput;

		std::vector<PostEffectPtr>								m_effects;

		RenderManagerPtr											m_pRenderManager;

		Material2Ptr												m_pFinalMaterial;

		MaterialParameterPtr										m_pParamOutput;
	};


}