#include "core_pch.h"
#include "CEFManager.h"
#include "CEFWebPage.h"
#include "CEFApp.h"
#include "CEFClientHandler.h"
#include "CEFClient.h"
#include "CEFRenderHandler.h"

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
			CefMainArgs main_args;

			CefRefPtr<CEFApp> app(new CEFApp);

			int exit_code = CefExecuteProcess(main_args, app.get());
			
			CefSettings settings;

			const char* szSub = "./cef_sub_process.exe";
			
			CefString(&settings.browser_subprocess_path).FromASCII(szSub);

			if(false == CefInitialize(main_args, settings, app.get()))
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
		CEFWebPagePtr CEFManager::CreatePage(const std::string& url)
		{
			return CEFWebPagePtr();
		}
	}
}
