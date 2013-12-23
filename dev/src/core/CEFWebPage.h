#pragma once

#include "cef3/include/cef_browser.h"

namespace ld3d
{
	namespace cef
	{
		class CEFWebPage
		{
		public:
			CEFWebPage(void);
			virtual ~CEFWebPage(void);

			void												SetRenderTarget(TexturePtr pTexture);

		private:
			CefRefPtr<CefBrowser>								m_pBrowser;
		};
	}
}
