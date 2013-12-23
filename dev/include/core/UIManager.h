#pragma once


namespace ld3d
{

	class _DLL_CLASS UIManager
	{
	public:
		UIManager(void);
		virtual ~UIManager(void);

		bool											Initialize(CoreApiPtr pCore);
		void											Release();

		bool											LoadUI(const std::string& src);
		void											Update(float dt);

		bool											DispatchInputEvent(EventPtr pEvent);

		void											AddOverlay(OverlayPtr pLayer);

		void											PrepareForRendering();

		OverlayPtr										CreateOverlay(const std::string& name, const math::RectI& rect);
		TextureOverlayPtr								CreateTextureOverlay(const std::string& name, const math::RectI& rect, TexturePtr pTex);
		HtmlOverlayPtr									CreateHtmlOverlay(const std::string& name, const math::RectI& rect, const std::string& url);
	private:
		void											_on_key(EventPtr pEvent);
		void											_on_mouse_move(EventPtr pEvent);
		void											_on_mouse_button(EventPtr pEvent);

		void											_prepare_render_data(OverlayPtr pRoot);
	private:
		CoreApiPtr										m_pCore;
		RenderManagerPtr								m_pRenderManager;
		OverlayPtr										m_pOverlayRoot;

		cef::CEFManagerPtr								m_pCEFManager;
	};
}
