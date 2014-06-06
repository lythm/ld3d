#include "core_pch.h"
#include "WinWindow.h"

namespace ld3d
{
	WinWindow::WinWindow(HWND hWnd)
	{
		m_hWnd = hWnd;
	}


	WinWindow::~WinWindow(void)
	{
	}
	WindowPtr WinWindow::Create(HINSTANCE hInstance,
		const std::string& title, 
		int x, 
		int y, 
		int w, 
		int h, 
		bool fullscreen)
	{
		//m_wndTitle = title;
		std::string wndClass = title + "_WndClass";


	//	m_clientWidth = w;
	//	m_clientHeight = h;

	//	m_width = w;
	//	m_height = h;

		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= NULL;
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
		wcex.lpszMenuName	= NULL;

		std::wstring utf16_class;

		ld3d::Unicode::UTF8_2_UTF16(wndClass, utf16_class);

		wcex.lpszClassName	= utf16_class.c_str();
		wcex.hIconSm		= NULL;


		if(FALSE == RegisterClassEx(&wcex))
		{
			return false;
		}

		std::wstring utf16_title;

		ld3d::Unicode::UTF8_2_UTF16(title, utf16_title);

		HWND hWnd = CreateWindow(utf16_class.c_str(), 
			utf16_title.c_str(), 
			(WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU), 
			CW_USEDEFAULT, 
			0, 
			w, 
			h, 
			NULL, 
			NULL, 
			hInstance, 
			NULL);

		if (!hWnd)
		{
			return WindowPtr();
		}

		std::shared_ptr<WinWindow> pWnd = std::make_shared<WinWindow>(hWnd);

		pWnd->SetFullscreen(fullscreen);
		pWnd->SetTitle(title);

		return pWnd;
	}
	void WinWindow::SetTitle(const std::string& title)
	{
		m_title = title;

		std::wstring utf16_title;

		ld3d::Unicode::UTF8_2_UTF16(title, utf16_title);

		SetWindowText(m_hWnd, utf16_title.c_str());
	}
	void WinWindow::Destroy()
	{
	}
	void WinWindow::Show(bool show)
	{
	}
	void WinWindow::IsVisible()
	{
	}
	void WinWindow::Resize(int cx, int cy)
	{
	}
	void WinWindow::SetFullscreen(bool fullscreen)
	{
	}

	LRESULT CALLBACK WinWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		MSG msg;
		msg.hwnd = hWnd;
		msg.lParam = lParam;
		msg.message = message;
		msg.wParam = wParam;
	//	g_app.HandleMessage(msg);
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ACTIVATE:

	//		m_bActive = LOWORD(wParam) != 0;

			break;
		
		case WM_KEYDOWN:
			break;
		case WM_KEYUP:
			break;

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:

			//SetCapture(hWnd);
			//SetFocus(hWnd);

			break;
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			
			//if (GetCapture() == hWnd)
			{
			//	ReleaseCapture();
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}
}
