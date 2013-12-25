#pragma once

namespace ld3d
{
	class _DLL_CLASS Overlay : public std::enable_shared_from_this<Overlay>
	{
	public:

		typedef std::function<bool (EventPtr)>		InputEventHandler;

		Overlay(UIManagerPtr pUIManager);
		virtual ~Overlay(void);

		OverlayPtr									GetParent();
		std::list<OverlayPtr>						GetChildList();
		
		void										LinkTo(OverlayPtr pParent);
		void										Unlink();

		void										SortChildren();

		int32										GetZOrder();
		void										SetZOrder(int32 z);

		bool										IsVisible();
		virtual void								Show(bool show);

		math::RectI									GetRect();
		void										SetRect(const math::RectI& r);

		void										Release();

		const std::string&							GetName();
		void										SetName(const std::string& name);

		virtual RenderDataPtr						PrepareRenderData();
		virtual void								OnRelease();

		void										GetScreenCoord(int& x, int& y);
		void										GetSize(uint32& w, uint32& h);

		void										MoveTo(int x, int y);
		void										Move(int offset_x, int offset_y);
		void										Resize(uint32 w, uint32 h);

		virtual void								OnResize(uint32 w, uint32 h);

		bool										IsFocus() const;
		void										SetFocus(bool bFocus);
		bool										DispatchInputEvent(EventPtr pEvent);

		InputEventHandler							on_input;

	protected:
		int32										m_zOrder;
		OverlayPtr									m_pParent;
		std::list<OverlayPtr>						m_children;
		bool										m_visible;
		math::RectI									m_rect;
		std::string									m_name;
		bool										m_inputFocus;

		UIManagerPtr								m_pUIManager;
	};
}
