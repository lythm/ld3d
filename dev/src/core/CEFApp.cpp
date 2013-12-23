#include "core_pch.h"
#include "CEFApp.h"

#include "CEFClient.h"


namespace ld3d
{
	namespace cef
	{
		CEFApp::CEFApp(void)
		{
		}


		CEFApp::~CEFApp(void)
		{
		}
		CefRefPtr<CefBrowserProcessHandler> CEFApp::GetBrowserProcessHandler()
		{
			return this;
		}
		void CEFApp::OnContextInitialized()
		{

			CefWindowInfo window_info;

#if defined(OS_WIN)
			// On Windows we need to specify certain flags that will be passed to
			// CreateWindowEx().
			window_info.SetAsOffScreen(nullptr);
#endif

			// SimpleHandler implements browser-level callbacks.
			CefRefPtr<CEFClient> handler(new CEFClient());

			// Specify CEF browser settings here.
			CefBrowserSettings browser_settings;

			std::string url;

			url = "http://www.google.com";

			CefRefPtr<CefBrowser> pBrowser = CefBrowserHost::CreateBrowserSync(window_info, handler.get(), url, browser_settings);

			pBrowser = CefBrowserHost::CreateBrowserSync(window_info, handler.get(), url, browser_settings);
		}
	}
}