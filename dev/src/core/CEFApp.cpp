#include "core_pch.h"
#include "CEFApp.h"

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
		CefRefPtr<CefRenderProcessHandler> CEFApp::GetRenderProcessHandler()
		{
			return NULL;
		}
		void CEFApp::OnContextInitialized()
		{

			
		}
	}
}