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
		void											AddOverLay(OverlayPtr pParent, OverlayPtr pLayer);

		void											PrepareForRendering();
	private:
		void											_on_key(EventPtr pEvent);
		void											_on_mouse_move(EventPtr pEvent);
		void											_on_mouse_button(EventPtr pEvent);

		void											_collect_render_data(OverlayPtr pRoot);
	private:
		CoreApiPtr										m_pCore;
		RenderManagerPtr								m_pRenderManager;
		OverlayPtr										m_pOverlayRoot;
	};
}
