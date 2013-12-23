#include "core_pch.h"
#include "CEFManager.h"
#include "CEFWebPage.h"
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
		bool CEFManager::Initialize()
		{
			CefMainArgs main_args(GetModuleHandle(NULL));

			m_pApp = new CEFApp;

			//int exit_code = CefExecuteProcess(main_args, m_pApp.get());
		

			CefSettings settings;
			settings.command_line_args_disabled = false;
			const char* szSub = "./cef_sub_process_x64.exe";
			
			CefString(&settings.browser_subprocess_path).FromASCII(szSub);

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

			// SimpleHandler implements browser-level callbacks.
			CefRefPtr<CEFWebPage> handler(new CEFWebPage);

			// Specify CEF browser settings here.
			CefBrowserSettings browser_settings;

			CefRefPtr<CefBrowser> pBrowser = CefBrowserHost::CreateBrowserSync(window_info, handler.get(), url, browser_settings);


			CEFWebpageRendererPtr pRenderer = alloc_object<CEFWebpageRenderer>(handler);

			return pRenderer;
		}
	}
}
