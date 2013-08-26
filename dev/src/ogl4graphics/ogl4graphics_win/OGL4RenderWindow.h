#pragma once

#if deined(_WIN64) || defined(_WIN32)
#include "core/RenderWindow.h"

namespace ld3d
{
	class OGL4RenderWindow : public RenderWindow
	{
	public:
		OGL4RenderWindow(void);
		virtual ~OGL4RenderWindow(void);

		bool														Create(void* wnd, int w, int h, G_FORMAT color_format, G_FORMAT depth_format);
		int															GetWidth();
		int															GetHeight();
		void														Release();

		void														OnResize(int cx, int cy);
		void														Present();

		HGLRC														GetContext();
		void														MakeCurrent();

		void														EnableVSync(bool bEnable);
	private:
		HWND														m_hWnd;
		HDC															m_hDC;
		HGLRC														m_hRC;

		int															m_width;
		int															m_height;
	};
}

#endif