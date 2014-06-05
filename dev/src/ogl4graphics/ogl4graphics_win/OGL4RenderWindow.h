#pragma once

#if defined(_WIN64) || defined(_WIN32)
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
		void														Resize(int cx, int cy, bool fullscreen = false);
		void														Present();

		HGLRC														GetContext();
		void														MakeCurrent();

		void														EnableVSync(bool bEnable);
		void														CenterWindow();
		void														AdjustWindow(int Width, int Height);

		bool														IsFullscreen();
	private:
		HWND														m_hWnd;
		HDC															m_hDC;
		HGLRC														m_hRC;

		int															m_width;
		int															m_height;
		bool														m_fullscreen;
	};
}

#endif