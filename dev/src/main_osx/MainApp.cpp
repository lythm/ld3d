//
//  MainApp.cpp
//  main_osx
//
//  Created by 佟 生悦 on 14-6-28.
//  Copyright (c) 2014年 ld3d. All rights reserved.
//

//#import <Cocoa/Cocoa.h>

#include "MainApp.h"

#include "core/graphics_osx.h"
#include "core/Sys_Graphics.h"
ld3d::Logger	s_logger;
MainApp::MainApp()
{

}

MainApp::~MainApp()
{
	
}
bool MainApp::Init(void* wnd)
{
	using namespace ld3d;
	
	m_pGraphics = CreateSysGraphicsPtr(s_logger);
	
	GraphicsSetting setting;
	setting.frameBufferWidth = 1024;
	setting.frameBufferHeight = 600;
	
	setting.wnd = wnd;
	m_pGraphics->Initialize(setting);
	
	
	return true;
}
void MainApp::Release()
{
	m_pGraphics->Release();
}
void MainApp::Update()
{
	//m_pGraphics->SetViewPort(0, 0, 100, 100);
	m_pGraphics->ClearRenderTarget(0, math::Color4(0, 0.5, 0, 1));
	
	

	m_pGraphics->Present();
	
}