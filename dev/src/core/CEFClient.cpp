#include "core_pch.h"
#include "CEFClient.h"
#include "include/cef_app.h"
#include "include/cef_runnable.h"

#define REQUIRE_UI_THREAD()   assert(CefCurrentlyOn(TID_UI));

namespace ld3d
{
	namespace cef
	{
		CEFClient::CEFClient(void)
		{
			m_pRenderHandler				= new CEFRenderHandler;
		}


		CEFClient::~CEFClient(void)
		{
		}
		CefRefPtr<CefDisplayHandler> CEFClient::GetDisplayHandler()
		{
			return this;
		}
		CefRefPtr<CefLifeSpanHandler> CEFClient::GetLifeSpanHandler()
		{
			return this;
		}
		CefRefPtr<CefLoadHandler> CEFClient::GetLoadHandler()
		{
			return this;
		}
		CefRefPtr<CefRenderHandler> CEFClient::GetRenderHandler()
		{
			return m_pRenderHandler;
		}
		void CEFClient::OnAfterCreated(CefRefPtr<CefBrowser> browser)
		{
			REQUIRE_UI_THREAD();

			// Add to the list of existing browsers.
			browser_list_.push_back(browser);
		}
		void CEFClient::OnBeforeClose(CefRefPtr<CefBrowser> browser)
		{
			REQUIRE_UI_THREAD();

			// Remove from the list of existing browsers.
			BrowserList::iterator bit = browser_list_.begin();
			for (; bit != browser_list_.end(); ++bit) {
				if ((*bit)->IsSame(browser)) {
					browser_list_.erase(bit);
					break;
				}
			}

			//if (browser_list_.empty())
			//{
			//	// All browser windows have closed. Quit the application message loop.
			//	CefQuitMessageLoop();
			//}
		}
		void CEFClient::OnLoadError(CefRefPtr<CefBrowser> browser, 
			CefRefPtr<CefFrame> frame,
			ErrorCode errorCode,
			const CefString& errorText,
			const CefString& failedUrl)
		{

		}
		void CEFClient::CloseAllBrowsers(bool force_close)
		{
			if (!CefCurrentlyOn(TID_UI)) {
				// Execute on the UI thread.
				CefPostTask(TID_UI,
					NewCefRunnableMethod(this, &CEFClient::CloseAllBrowsers,
					force_close));
				return;
			}

			if (browser_list_.empty())
				return;

			BrowserList::const_iterator it = browser_list_.begin();
			for (; it != browser_list_.end(); ++it)
				(*it)->GetHost()->CloseBrowser(force_close);
		}
		bool CEFClient::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
		{
			rect.x = 0;
			rect.y = 0;
			rect.width = 400;
			rect.height = 400;

			return true;
		}
		void CEFClient::OnPaint(CefRefPtr<CefBrowser> browser,
				PaintElementType type,
				const RectList& dirtyRects,
				const void* buffer,
				int width, int height)
		{
		}
	}
}
