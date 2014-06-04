#include "core_pch.h"
#include "CEFManager.h"
#include "CEFWebpage.h"
#include "core_utils.h"


namespace ld3d
{
	namespace cef
	{
		CEFManager::CEFManager(void)
		{
		}

		CEFManager::~CEFManager(void)
		{
		}
		bool CEFManager::Initialize(CoreApiPtr pCore)
		{
			m_pCore = pCore;
			CefMainArgs main_args(GetModuleHandle(NULL));

			m_pApp = new CEFApp;

			CefSettings settings;
			settings.command_line_args_disabled = false;
			const char* szSub = "./cef_sub_process_x64.exe";
			
			CefString(&settings.browser_subprocess_path).FromASCII(szSub);
			CefString(&settings.log_file).FromString("./log/cef.log");

			if(false == CefInitialize(main_args, settings, m_pApp.get()))
			{
				return false;
			}

			return true;
		}
		void CEFManager::Release()
		{

			CefShutdown();
		}
		void CEFManager::Update()
		{
			CefDoMessageLoopWork();
		}
		WebpageRendererPtr CEFManager::CreateWebpageRenderer(const std::string& url)
		{
			CefWindowInfo window_info;

			window_info.SetAsOffScreen(nullptr);
			window_info.SetTransparentPainting(true);
			// SimpleHandler implements browser-level callbacks.
			CefRefPtr<CEFWebpage> handler(new CEFWebpage);

			// Specify CEF browser settings here.
			CefBrowserSettings browser_settings;

			CefRefPtr<CefBrowser> pBrowser = CefBrowserHost::CreateBrowserSync(window_info, handler.get(), url, browser_settings, nullptr);

			while(pBrowser->IsLoading())
			{
				CefDoMessageLoopWork();
			}

			CEFWebpageRendererPtr pRenderer = alloc_object<CEFWebpageRenderer>(m_pCore, handler);

			return pRenderer;
		}
	}
}
