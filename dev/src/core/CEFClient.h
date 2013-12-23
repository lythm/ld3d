#pragma once

#include "cef3/include/cef_client.h"
#include "CEFRenderHandler.h"

namespace ld3d
{
	namespace cef
	{

		class CEFClient : public CefClient,
			public CefDisplayHandler,
			public CefLifeSpanHandler,
			public CefLoadHandler ,
			public CefRenderHandler
		{
		public:
			CEFClient(void);
			virtual ~CEFClient(void);

			CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE;

			CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE;

			CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE ;

			CefRefPtr<CefRenderHandler> GetRenderHandler();
			
			void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
			void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

			void OnLoadError(CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				ErrorCode errorCode,
				const CefString& errorText,
				const CefString& failedUrl) OVERRIDE;

			void CloseAllBrowsers(bool force_close);


			// render handlers
			bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect);

			void OnPaint(CefRefPtr<CefBrowser> browser,
				PaintElementType type,
				const RectList& dirtyRects,
				const void* buffer,
				int width, int height);

		private:

			CefRefPtr<CefRenderHandler>						m_pRenderHandler;

			
			typedef std::list<CefRefPtr<CefBrowser> > BrowserList;
			BrowserList browser_list_;

			// Include the default reference counting implementation.
			IMPLEMENT_REFCOUNTING(SimpleHandler);

		};
	}
}
