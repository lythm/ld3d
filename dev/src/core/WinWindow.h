#pragma once

#include "core/OSWindow.h"

namespace ld3d
{
	class WinWindow : public Window
	{
	public:
		WinWindow(HWND hWnd);
		virtual ~WinWindow(void);


		static WindowPtr							Create(HINSTANCE hInstance,
														const std::string& title, 
														int x, 
														int y, 
														int w, 
														int h, 
														bool fullscreen = false);
		void										Destroy();
		void										Show(bool show);
		void										IsVisible();
		void										Resize(int cx, int cy);
		void										SetFullscreen(bool fullscreen);

		void										SetTitle(const std::string& title);

		static LRESULT CALLBACK						WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	private:
		HWND										m_hWnd;
		bool										m_fullscreen;
		std::string									m_title;
	};
}
