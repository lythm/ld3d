#pragma once

#include "cef3/include/cef_render_handler.h"

namespace ld3d
{
	namespace cef
	{
		class CEFRenderHandler : public CefRenderHandler
		{
		public:
			CEFRenderHandler(void);
			virtual ~CEFRenderHandler(void);



			bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect);

			void OnPaint(CefRefPtr<CefBrowser> browser,
				PaintElementType type,
				const RectList& dirtyRects,
				const void* buffer,
				int width, int height);


			///
			// Called to retrieve the root window rectangle in screen coordinates. Return
			// true if the rectangle was provided.
			///
			/*--cef()--*/
			virtual bool GetRootScreenRect(CefRefPtr<CefBrowser> browser,
				CefRect& rect) { return false; }

			

			///
			// Called to retrieve the translation from view coordinates to actual screen
			// coordinates. Return true if the screen coordinates were provided.
			///
			/*--cef()--*/
			virtual bool GetScreenPoint(CefRefPtr<CefBrowser> browser,
				int viewX,
				int viewY,
				int& screenX,
				int& screenY) { return false; }

			///
			// Called to allow the client to fill in the CefScreenInfo object with
			// appropriate values. Return true if the |screen_info| structure has been
			// modified.
			//
			// If the screen info rectangle is left empty the rectangle from GetViewRect
			// will be used. If the rectangle is still empty or invalid popups may not be
			// drawn correctly.
			///
			/*--cef()--*/
			virtual bool GetScreenInfo(CefRefPtr<CefBrowser> browser,
				CefScreenInfo& screen_info) { return false; }

			///
			// Called when the browser wants to show or hide the popup widget. The popup
			// should be shown if |show| is true and hidden if |show| is false.
			///
			/*--cef()--*/
			virtual void OnPopupShow(CefRefPtr<CefBrowser> browser,
				bool show) {}

			///
			// Called when the browser wants to move or resize the popup widget. |rect|
			// contains the new location and size.
			///
			/*--cef()--*/
			virtual void OnPopupSize(CefRefPtr<CefBrowser> browser,
				const CefRect& rect) {}

		

			///
			// Called when the browser window's cursor has changed.
			///
			/*--cef()--*/
			virtual void OnCursorChange(CefRefPtr<CefBrowser> browser,
				CefCursorHandle cursor) {}

			///
			// Called when the scroll offset has changed.
			///
			/*--cef()--*/
			virtual void OnScrollOffsetChanged(CefRefPtr<CefBrowser> browser) {}

		private:
			IMPLEMENT_REFCOUNTING(CEFRenderHandler);
		};


	}
}