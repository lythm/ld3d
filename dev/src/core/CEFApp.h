#pragma once

#ifdef WIN32
#include "cef3/include/cef_app.h"
#endif

#ifdef __APPLE__
#include "cef3-mac/include/cef_app.h"
#endif
namespace ld3d
{
	namespace cef
	{
		class CEFApp : public CefApp, public CefBrowserProcessHandler
		{
		public:
			CEFApp(void);
			virtual ~CEFApp(void);

			CefRefPtr<CefBrowserProcessHandler>						GetBrowserProcessHandler() OVERRIDE;


			CefRefPtr<CefRenderProcessHandler>						GetRenderProcessHandler() OVERRIDE;
			

			void													OnContextInitialized() OVERRIDE;

		private:
			// Include the default reference counting implementation.
			IMPLEMENT_REFCOUNTING(CEFApp);

		};
	}
}
