//
//  MainApp.cpp
//  main_osx
//
//  Created by 佟 生悦 on 14-6-28.
//  Copyright (c) 2014年 ld3d. All rights reserved.
//

#include "MainApp.h"

#include "core/graphics_osx.h"


ld3d::Logger	g_logger;
MainApp::MainApp()
{

}

MainApp::~MainApp()
{
	
}
bool MainApp::Init()
{
	using namespace ld3d;
	
	Sys_Graphics* pGraphics = CreateSysGraphics(g_logger);
	
	return true;
}
void MainApp::Release()
{
	
}
