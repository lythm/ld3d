#include "ogl4graphics_pch.h"

#if defined(_WIN64) || defined(_WIN32)
#include "OGL4RenderWindow.h"
#include "glext/wglext.h"

namespace ld3d
{
	OGL4RenderWindow::OGL4RenderWindow(void)
	{
		m_hDC = nullptr;
		m_hRC = nullptr;
		m_hWnd = nullptr;
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
}


#endif