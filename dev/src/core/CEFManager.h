#pragma once

#include "CEFApp.h"

namespace ld3d
{
	namespace cef
	{
		class CEFManager
		{
		public:
			CEFManager(void);
			virtual ~CEFManager(void);

			bool								Initialize();
			void								Release();

			void								Update();

			WebpageRendererPtr					CreateWebpageRenderer(const std::string& url);

		private:

			CefRefPtr<CEFApp>					m_pApp;
		};
	}
}
