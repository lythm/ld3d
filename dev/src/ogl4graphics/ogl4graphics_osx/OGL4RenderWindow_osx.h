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

#include <Cocoa/Cocoa.h>
namespace ld3d
{
    class OGL4RenderWindow : public RenderWindow
    {
    public:
        OGL4RenderWindow();
        virtual ~OGL4RenderWindow();
        
        
        bool                    Create(NSWindow* window);
        void                    Destroy();
        
        
    private:
        
        
    private:
        
    };
    
    
}


#endif /* defined(__ogl4graphics_osx__OGL4RenderWindow_osx__) */
