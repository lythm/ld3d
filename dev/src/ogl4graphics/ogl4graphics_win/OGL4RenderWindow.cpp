#include "ogl4graphics_pch.h"

#if defined(_WIN64) || defined(_WIN32)
#include "OGL4RenderWindow.h"
#include "glext/wglext.h"

namespace ld3d
{
	OGL4RenderWindow::OGL4RenderWindow(void)
	{
		m_hDC			= nullptr;
		m_hRC			= nullptr;
		m_hWnd			= nullptr;
		m_fullscreen	= false;
		m_width			= 0;
		m_height		= 0;
	}


	OGL4RenderWindow::~OGL4RenderWindow(void)
	{
	}
	int OGL4RenderWindow::GetWidth()
	{
		return m_width;
	}
	int OGL4RenderWindow::GetHeight()
	{
		return m_height;
	}
	void OGL4RenderWindow::Release()
	{
		wglMakeCurrent(m_hDC, 0);

		wglDeleteContext(m_hRC);

		DeleteDC(m_hDC);
		m_hDC = nullptr;
		m_hRC = nullptr;
		m_hWnd = nullptr;
	}
	bool OGL4RenderWindow::Create(void* wnd, int w, int h, G_FORMAT color_format, G_FORMAT depth_format)
	{
		if(wnd == nullptr)
		{
			return false;
		}

		m_hWnd = (HWND)wnd;

		AdjustWindow(w, h);
		CenterWindow();

		m_hDC = ::GetDC(m_hWnd);

		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 32;
		pfd.iLayerType = PFD_MAIN_PLANE;

		int nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
		if (nPixelFormat == 0)
			return false;  

		bool bResult = (SetPixelFormat(m_hDC, nPixelFormat, &pfd) != FALSE);
		if (!bResult)
			return false;

		HGLRC tempOpenGLContext = wglCreateContext(m_hDC);
		wglMakeCurrent(m_hDC, tempOpenGLContext);


		int attributes[] = 
		{  
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB |
			WGL_CONTEXT_DEBUG_BIT_ARB,        
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};
		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
		if(wglCreateContextAttribsARB == nullptr)
		{
			m_hRC = tempOpenGLContext;
			return true;
		}

		m_hRC = wglCreateContextAttribsARB(m_hDC, NULL, attributes);

		if(m_hRC == nullptr)
		{
			m_hRC = tempOpenGLContext;
			return true;
		}
		MakeCurrent();

		wglDeleteContext(tempOpenGLContext);

		m_width = w;
		m_height = h;
		return true;
	}


	void OGL4RenderWindow::Present()
	{
		SwapBuffers(m_hDC);

	}
	HGLRC OGL4RenderWindow::GetContext()
	{
		return m_hRC;
	}
	void OGL4RenderWindow::MakeCurrent()
	{
		wglMakeCurrent(NULL, NULL);
		wglMakeCurrent(m_hDC, m_hRC);
	}
	void OGL4RenderWindow::OnResize(int cx, int cy)
	{
		m_width = cx;
		m_height = cy;
	}
	void OGL4RenderWindow::EnableVSync(bool bEnable)
	{
		bEnable ? wglSwapIntervalEXT(1) : wglSwapIntervalEXT(0);
	}
	void OGL4RenderWindow::CenterWindow()
	{
		RECT	rtWindow = {0};
		RECT	rtContainer = {0};

		GetWindowRect(m_hWnd,&rtWindow);
		rtWindow.right -= rtWindow.left;
		rtWindow.bottom -= rtWindow.top;

		rtContainer.right = GetSystemMetrics(SM_CXSCREEN);
		rtContainer.bottom = GetSystemMetrics(SM_CYSCREEN);

		SetWindowPos(m_hWnd,NULL,(rtContainer.right - rtWindow.right) / 2,(rtContainer.bottom - rtWindow.bottom) / 2,0,0,SWP_NOSIZE);
	}
	void OGL4RenderWindow::AdjustWindow(int Width, int Height )
	{
		RECT WinRect;
		RECT ClientRect;

		GetWindowRect( m_hWnd, &WinRect );
		GetClientRect( m_hWnd, &ClientRect );

		int ClientWidth  = ClientRect.right  - ClientRect.left;
		int ClientHeight = ClientRect.bottom - ClientRect.top;

		int IncX = Width  - ClientWidth;
		int IncY = Height - ClientHeight;

		SetWindowPos( m_hWnd, 0, WinRect.left, WinRect.top, WinRect.right - WinRect.left + IncX, WinRect.bottom - WinRect.top + IncY, SWP_NOZORDER );

		m_width			= Width;
		m_height		= Height;
	}
	void OGL4RenderWindow::Resize(int cx, int cy, bool fullscreen)
	{
		LONG_PTR value = GetWindowLongPtr(m_hWnd, GWL_STYLE);
		m_fullscreen = fullscreen;
		if(fullscreen == false)
		{
			value &= ~(WS_POPUP);
			value |= (WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU);

			SetWindowLongPtr(m_hWnd, GWL_STYLE, value);
			
			SetWindowPos( m_hWnd, 0, 0, 0, cx, cy, SWP_NOZORDER );
			AdjustWindow(cx, cy);
			CenterWindow();
			m_width			= cx;
			m_height		= cy;
		}
		else
		{
			int screen_w = GetSystemMetrics(SM_CXSCREEN);
			int screen_h = GetSystemMetrics(SM_CYSCREEN);
			
			value &= ~(WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU);
			value |= (WS_POPUP);

			SetWindowLongPtr(m_hWnd, GWL_STYLE, value);
			SetWindowPos( m_hWnd, 0, 0, 0, screen_w, screen_h, SWP_NOZORDER );

			m_width			= screen_w;
			m_height		= screen_h;
		}
	}
	bool OGL4RenderWindow::IsFullscreen()
	{
		return m_fullscreen;
	}
}


#endif