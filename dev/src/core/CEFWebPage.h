#pragma once


#ifdef WIN32
#include "cef3/include/cef_browser.h"
#include "cef3/include/cef_client.h"
#endif

#ifdef __APPLE__
#include "cef3-mac/include/cef_browser.h"
#include "cef3-mac/include/cef_client.h"

#endif

#include "core/WebpageRenderer.h"

namespace ld3d
{
	namespace cef
	{
		class CEFWebpage : public CefClient,
			public CefDisplayHandler,
			public CefLifeSpanHandler,
			public CefLoadHandler ,
			public CefRenderHandler
		{
		public:
			CEFWebpage(void);
			virtual ~CEFWebpage(void);

			void														SetRenderTarget(TexturePtr pTexture);


			CefRefPtr<CefDisplayHandler>								GetDisplayHandler() OVERRIDE;

			CefRefPtr<CefLifeSpanHandler>								GetLifeSpanHandler() OVERRIDE;

			CefRefPtr<CefLoadHandler>									GetLoadHandler() OVERRIDE ;

			CefRefPtr<CefRenderHandler>									GetRenderHandler();


			void														OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
			void														OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

			void														OnLoadStart(CefRefPtr<CefBrowser> browser,
																			CefRefPtr<CefFrame> frame);

			void														OnLoadEnd(CefRefPtr<CefBrowser> browser,
																			CefRefPtr<CefFrame> frame,
																			int httpStatusCode);

			void														OnLoadError(CefRefPtr<CefBrowser> browser,
																			CefRefPtr<CefFrame> frame,
																			ErrorCode errorCode,
																			const CefString& errorText,
																			const CefString& failedUrl) OVERRIDE;


			bool														GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect);

			void														OnPaint(CefRefPtr<CefBrowser> browser,
																			PaintElementType type,
																			const RectList& dirtyRects,
																			const void* buffer,
																			int width, int height);

			bool														OnBeforePopup(CefRefPtr<CefBrowser> browser,
																			CefRefPtr<CefFrame> frame,
																			const CefString& target_url,
																			const CefString& target_frame_name,
																			const CefPopupFeatures& popupFeatures,
																			CefWindowInfo& windowInfo,
																			CefRefPtr<CefClient>& client,
																			CefBrowserSettings& settings,
																			bool* no_javascript_access);

			bool														OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
																			CefProcessId source_process,
																			CefRefPtr<CefProcessMessage> message);

			void														Destroy();
			void														SetVisible(bool bVisible);
			bool														IsVisible();

			void														LoadPage(const std::string& url);

#ifdef WIN32
			void														HandleWinMsg(MSG& msg);
#endif
			void														SetScreenCoord(int x, int y);

			void														ExecuteJS(const std::string& code);

			void														RegisterScriptCallHandler(const std::string& call_name, const std::function<void(const std::string&)>& handler);
		private:
			bool														IsPointInside(int screenX, int screenY);
			
#ifdef WIN32
			void														GetMouseLocalCoord(LPARAM lParam, int& x, int& y);
			int															GetCefMouseModifiers(WPARAM wparam);
			int															GetCefKeyboardModifiers(WPARAM wparam, LPARAM lparam);
			bool														IsKeyDown(WPARAM wparam);
#endif
		private:

			int															m_screenX;
			int															m_screenY;

			bool														m_visible;

			TexturePtr													m_pTexture;

			CefRefPtr<CefBrowser>										m_pBrowser;

			bool														m_isTargetBlank;

			bool														m_isLoaded;

			std::map<std::string, 
				std::function<void(const std::string&)>>				m_scriptHandlerMap;


			IMPLEMENT_REFCOUNTING(CEFWebpage);
		};


		class CEFWebpageRenderer : public WebpageRenderer
		{
		public:
			CEFWebpageRenderer(CoreApiPtr pCore, CefRefPtr<CEFWebpage> pPage);

			virtual ~CEFWebpageRenderer();

			void														SetRenderTarget(TexturePtr pTexture);

			void														Release();

			void														SetVisible(bool visible);

			void														LoadPage(const std::string& url);

			void														SetScreenCoord(int x, int y);

			void														ExecuteJS(const std::string& code);

			void														RegisterScriptCallHandler(const std::string& call_name, const std::function<void(const std::string&)>& handler);
		private:
			void														_on_win_msg(EventPtr pEvent);
		private:
			CefRefPtr<CEFWebpage>										m_pPage;
			CoreApiPtr													m_pCore;

			EventHandlerID												m_winMsgHandlerId;


		};
	}
}
