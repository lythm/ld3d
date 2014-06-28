//
//  OGL4RenderWindow_osx.h
//  ogl4graphics_osx
//
//  Created by 佟 生悦 on 13-8-26.
//  Copyright (c) 2013年 ld3d. All rights reserved.
//

#ifndef __ogl4graphics_osx__OGL4RenderWindow_osx__
#define __ogl4graphics_osx__OGL4RenderWindow_osx__

#include "core/RenderWindow.h"

//#include <Cocoa/Cocoa.h>
namespace ld3d
{
    class OGL4RenderWindow : public RenderWindow
    {
    public:
        OGL4RenderWindow();
        virtual ~OGL4RenderWindow();
        
        
      //  bool                    Create(NSWindow* window);
		
		
		bool														Create(void* wnd, int w, int h, G_FORMAT color_format, G_FORMAT depth_format);
		int															GetWidth();
		int															GetHeight();
		void														Release();
		
		void														OnResize(int cx, int cy);
		void														Resize(int cx, int cy, bool fullscreen = false);
		void														Present();
		
		//HGLRC														GetContext();
		void														MakeCurrent();
		
		void														EnableVSync(bool bEnable);
		void														CenterWindow();
		void														AdjustWindow(int Width, int Height);
		
		bool														IsFullscreen();
        
        
    private:
        
        
    private:
		void*														m_hWnd;
		
		int															m_width;
		int															m_height;
		bool														m_fullscreen;
        
    };
    
    
}


#endif /* defined(__ogl4graphics_osx__OGL4RenderWindow_osx__) */
