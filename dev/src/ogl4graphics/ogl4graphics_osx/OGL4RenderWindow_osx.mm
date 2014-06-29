//
//  OGL4RenderWindow_osx.cpp
//  ogl4graphics_osx
//
//  Created by 佟 生悦 on 13-8-26.
//  Copyright (c) 2013年 ld3d. All rights reserved.
//

#include "OGL4RenderWindow_osx.h"

#import <Cocoa/Cocoa.h>
namespace ld3d
{
    OGL4RenderWindow::OGL4RenderWindow()
    {
		m_window	= nullptr;
        
    }
    OGL4RenderWindow::~OGL4RenderWindow()
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
		
		//wglMakeCurrent(m_hDC, 0);
		
		//wglDeleteContext(m_hRC);
		
		//DeleteDC(m_hDC);
		//m_hDC = nullptr;
		//m_hRC = nullptr;
		m_window = nullptr;
	}
	bool OGL4RenderWindow::Create(void* wnd, int w, int h, G_FORMAT color_format, G_FORMAT depth_format)
	{
		if(wnd == nullptr)
		{
			return false;
		}
		
		m_window = wnd;
		
		AdjustWindow(w, h);
		CenterWindow();
		
		
		
		// Insert code here to initialize your application
		NSOpenGLPixelFormatAttribute attributes[] = {
			NSOpenGLPFAColorSize, 32,
			NSOpenGLPFADepthSize, 24,
			NSOpenGLPFAStencilSize, 8,
			NSOpenGLPFADoubleBuffer,
			NSOpenGLPFAAccelerated,
			NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
			0
		};
		
		NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
		if (pixelFormat == nil)
		{
			return false;
		}
		
		NSWindow* nsw = (NSWindow*)m_window;
		
		NSOpenGLView *view = [[NSOpenGLView alloc] initWithFrame:nsw.frame pixelFormat:pixelFormat];
		
		[nsw setContentView:view];
		
		MakeCurrent();
		m_width = w;
		m_height = h;
		return true;
	}
	
	
	void OGL4RenderWindow::Present()
	{
		NSWindow* nsw = (NSWindow*)m_window;
		
		NSOpenGLView *view = [nsw contentView];
		
		NSOpenGLContext* context = [view openGLContext];
		
		[context flushBuffer];
		
	}
	
	void OGL4RenderWindow::MakeCurrent()
	{
		
		NSWindow* nsw = (NSWindow*)m_window;
		
		NSOpenGLView *view = [nsw contentView];
		
		NSOpenGLContext* context = [view openGLContext];
		
		[context makeCurrentContext];

	}
	void OGL4RenderWindow::OnResize(int cx, int cy)
	{
		m_width = cx;
		m_height = cy;
	}
	void OGL4RenderWindow::EnableVSync(bool bEnable)
	{
		NSWindow* nsw = (NSWindow*)m_window;
		
		NSOpenGLView *view = [nsw contentView];
		
		NSOpenGLContext* context = [view openGLContext];
		
		GLint v = bEnable ?  1 : 0;
		[context setValues:&v forParameter:NSOpenGLCPSwapInterval];
		
	}
	void OGL4RenderWindow::CenterWindow()
	{
		NSWindow* nsw = (NSWindow*)m_window;
		
		[nsw center];
		
	}
	void OGL4RenderWindow::AdjustWindow(int Width, int Height )
	{
		NSSize size;
		size.width = Width;
		size.height = Height;
		
		NSWindow* nsw = (NSWindow*)m_window;
		[nsw setContentSize:size];
		
		m_width			= Width;
		m_height		= Height;
	}
	void OGL4RenderWindow::Resize(int cx, int cy, bool fullscreen)
	{
		
		m_fullscreen = fullscreen;
		if(m_fullscreen == false)
		{
			AdjustWindow(cx, cy);
			CenterWindow();
			m_width = cx;
			m_height = cy;
			
		}
		else
		{
			
		}
		
	/*	LONG_PTR value = GetWindowLongPtr(m_hWnd, GWL_STYLE);
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
	 */
	}
	bool OGL4RenderWindow::IsFullscreen()
	{
		return m_fullscreen;
	}
}