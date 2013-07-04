#include "stdafx.h"
#include "EngineApp.h"
#include <tchar.h>



namespace ld3d
{

	EngineApp::EngineApp(void)
	{
	}


	EngineApp::~EngineApp(void)
	{
	}
	void EngineApp::OnUpdate()
	{
		m_pGraphics->ClearRenderTarget(0, math::Color4(0.3, 0.5, 0.7, 1));
		m_pGraphics->ClearDepthStencil(CLEAR_ALL, 1.0f, 0);

		
		m_pGraphics->Present();

		ShowFPS();
	}
	bool EngineApp::OnInit()
	{
		using namespace ld3d;

		if(false == m_mod.load_sys(L"./ogl4graphics_x64.dll"))
		{
			return false;
		}

		m_pGraphics = m_mod.pSys;
		
		GraphicsSetting setting;
		setting.sysMod = L"./ogl4graphics_x64.dll";
		setting.backBufferCount = 2;
		setting.depthStencilFormat = G_FORMAT_D24_UNORM_S8_UINT;
		setting.frameBufferFormat = G_FORMAT_R8G8B8A8_UNORM;
		setting.frameBufferHeight = GetClientHeight();
		setting.frameBufferWidth = GetClientWidth();
		setting.multiSampleCount = 1;
		setting.multiSampleQuality = 0;
		setting.windowed = true;
		setting.wnd = GetWnd();

		
		if(false == m_pGraphics->Initialize(setting))
		{
			return false;
		}



		return true;
	}
	void EngineApp::OnRelease()
	{
		m_pGraphics.reset();
	}

	void EngineApp::ShowFPS()
	{
		static int tick = GetTickCount();

		static int frames = 0;
		int dt = GetTickCount() - tick;

		int iv = 100;
		if(dt >= iv)
		{

			wchar_t buffer[100];

			float fps = float(frames * 1000) / float(dt);
			swprintf(buffer, 100, L"fps : %.3f - %fms", fps, 1000.0f / fps);

			SetTitle(buffer);

			tick = GetTickCount();
			frames = 0;
		}

		frames ++;
	}

	void EngineApp::HandleMessage(MSG& msg)
	{
	}
}






int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	using namespace ld3d;
	EngineApp app;

	if(false == app.Initialize(hInstance, L"Main Window", 800, 600))
	{
		return -1;
	}
	app.Run();

	app.Release();

	return 0;
}
