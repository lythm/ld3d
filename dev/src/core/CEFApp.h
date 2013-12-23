#pragma once

#include "cef3/include/cef_app.h"

namespace ld3d
{
	namespace cef
	{
		class CEFApp : public CefApp, public CefBrowserProcessHandler
		{
		public:
			CEFApp(void);
			virtual ~CEFApp(void);

			CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE;

			void OnContextInitialized() OVERRIDE;

		private:
			// Include the default reference counting implementation.
			IMPLEMENT_REFCOUNTING(SimpleApp);

		};
	}
}
