#include "core_pch.h"
#include "CEFRenderHandler.h"

namespace ld3d
{
	namespace cef
	{
		CEFRenderHandler::CEFRenderHandler(void)
		{
		}


		CEFRenderHandler::~CEFRenderHandler(void)
		{
		}
		bool CEFRenderHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
		{
			rect.x = 0;
			rect.y = 0;
			rect.width = 400;
			rect.height = 400;

			return true;
		}
		void CEFRenderHandler::OnPaint(CefRefPtr<CefBrowser> browser,
				PaintElementType type,
				const RectList& dirtyRects,
				const void* buffer,
				int width, int height)
		{
		}

	}
}
