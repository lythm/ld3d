#pragma once


namespace ld3d
{

	class _DLL_CLASS UIManager : public std::enable_shared_from_this<UIManager>
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

		

		OverlayPtr										CreateOverlay(const std::string& name, const math::RectI& rect);
		TextureOverlayPtr								CreateTextureOverlay(const std::string& name, const math::RectI& rect, TexturePtr pTex);
		HtmlOverlayPtr									CreateHtmlOverlay(const std::string& name, const math::RectI& rect, const std::string& url);

		OverlayPtr										PickOverlay();
	private:
		void											PrepareForRendering();
		void											_traverse_tree_preorder(OverlayPtr pRoot, std::function<bool(OverlayPtr)> handler);
		void											_on_frustum_cull(EventPtr pEvent);
	private:
		CoreApiPtr										m_pCore;
		RenderManagerPtr								m_pRenderManager;
		OverlayPtr										m_pOverlayRoot;

		cef::CEFManagerPtr								m_pCEFManager;

		OverlayPtr										m_pFocusOverlay;

		EventHandlerID									m_ehFrustumCull;
	};
}
