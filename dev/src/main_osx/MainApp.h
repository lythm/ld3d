//
//  MainApp.h
//  main_osx
//
//  Created by 佟 生悦 on 14-6-28.
//  Copyright (c) 2014年 ld3d. All rights reserved.
//

#ifndef __main_osx__MainApp__
#define __main_osx__MainApp__


#include <iostream>
#include "core/core_ptr.h"
//#include "utils/utils_all.h"
class MainApp
{
public:
	MainApp();
	virtual ~MainApp();
	bool					Init(void* wnd);
	void					Release();
	
	void					Update();
private:
	//static ld3d::Logger	s_logger;
	
	ld3d::Sys_GraphicsPtr			m_pGraphics;
};
#endif /* defined(__main_osx__MainApp__) */
