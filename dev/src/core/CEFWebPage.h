#pragma once

#include "cef3/include/cef_browser.h"
#include "cef3/include/cef_client.h"
#include "core/WebpageRenderer.h"

namespace ld3d
{
	namespace cef
	{
		class CEFWebPage : public CefClient,
			public CefDisplayHandler,
			public CefLifeSpanHandler,
			public CefLoadHandler ,
			public CefRenderHandler
		{
		public:
			CEFWebPage(void);
			virtual ~CEFWebPage(void);

			void												SetRenderTarget(TexturePtr pTexture);


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


			bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect);

			void OnPaint(CefRefPtr<CefBrowser> browser,
				PaintElementType type,
				const RectList& dirtyRects,
				const void* buffer,
				int width, int height);


			void												Destroy();
		private:

			TexturePtr											m_pTexture;

			CefRefPtr<CefBrowser>								m_pBrowser;

			IMPLEMENT_REFCOUNTING(CEFWebPage);
		};


		class CEFWebpageRenderer : public WebpageRenderer
		{
		public:
			CEFWebpageRenderer(CefRefPtr<CEFWebPage> pPage);

			virtual ~CEFWebpageRenderer();

			void												SetRenderTarget(TexturePtr pTexture);

			void												Release();
		private:
			CefRefPtr<CEFWebPage>								m_pPage;
		};
	}
}
