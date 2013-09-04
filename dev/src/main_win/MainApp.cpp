#include "pch.h"

#include "MainApp.h"
#include <tchar.h>


namespace ld3d
{

	void log(const std::string& text)
	{
		OutputDebugStringA(text.c_str());
		OutputDebugStringA("\r\n");

	}

	bool												MainApp::m_bActive = true;
	MainApp::MainApp(void)
	{
		m_hInst	= NULL;
		m_hWnd = NULL;
		m_width = 640;
		m_height = 480;

		m_clientWidth		= 0;
		m_clientHeight		= 0;
	}

	MainApp::~MainApp(void)
	{
	}

	HWND MainApp::GetWnd()
	{
		return m_hWnd;
	}
	bool MainApp::Initialize(HINSTANCE hInst, const std::string& title, int w, int h)
	{
		m_hInst = hInst;
		m_wndTitle = title;
		m_wndClass = title + "_WndClass";


		m_clientWidth = w;
		m_clientHeight = h;

		m_width = w;
		m_height = h;

		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= m_hInst;
		wcex.hIcon			= NULL;
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
		wcex.lpszMenuName	= NULL;
		
		std::wstring utf16_class;

		ld3d::Unicode::UTF8_2_UTF16(m_wndClass, utf16_class);
		
		wcex.lpszClassName	= utf16_class.c_str();
		wcex.hIconSm		= NULL;
		

		if(FALSE == RegisterClassEx(&wcex))
		{
			return false;
		}

		std::wstring utf16_title;

		ld3d::Unicode::UTF8_2_UTF16(m_wndTitle, utf16_title);
		
		m_hWnd = CreateWindow(utf16_class.c_str(), 
			utf16_title.c_str(), 
			(WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU), 
			CW_USEDEFAULT, 
			0, 
			m_width, 
			m_height, 
			NULL, 
			NULL, 
			m_hInst, 
			NULL);

		if (!m_hWnd)
		{
			return false;
		}

		AdjustWindow(w, h);

		ShowWindow(m_hWnd, SW_SHOW);
		UpdateWindow(m_hWnd);

		if(OnInit() == false)
		{
			return false;
		}

		return true;
	}
	void MainApp::AdjustWindow(int Width, int Height )
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


		m_width = IncX + Width;
		m_height = IncY + Height;
	}
	
	void MainApp::Release()
	{

		OnRelease();
	}
	LRESULT CALLBACK MainApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ACTIVATE:

			m_bActive = LOWORD(wParam) != 0;

			break;
		case WM_CHAR:
			{
				
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}

	void MainApp::Run()
	{
		MSG msg = {0};
		while( WM_QUIT != msg.message )
		{
			if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
			{
				HandleMessage(msg);

				TranslateMessage( &msg );
				DispatchMessage( &msg );
			
			}
			else
			{
				if(m_bActive)
				{
					OnUpdate();
				}
				else
				{
					Sleep(1);
				}
			}
		}

		return;
	}
	void MainApp::OnUpdate()
	{
		m_pCore->Update();

		ShowFPS();

		m_pGameManager->GetGame()->Update();
	}

	bool MainApp::OnInit()
	{

		m_pConfig = std::make_shared<MainConfig>();
		if(m_pConfig->Load("./main.conf.xml") == false)
		{
			return false;
		}

		m_pGameManager = std::make_shared<GameManager>();

		if(false == m_pGameManager->Initialize("./game_x64.dll"))
		{
			return false;
		}


		m_pCore = std::make_shared<CoreApi>();

		SysSetting setting;
		

		setting.graphics.sysMod = "./d11graphics_x64.dll";
		setting.graphics.backBufferCount = 2;
		setting.graphics.depthStencilFormat = G_FORMAT_D24_UNORM_S8_UINT;
		setting.graphics.frameBufferFormat = G_FORMAT_R8G8B8A8_UNORM;
		setting.graphics.frameBufferHeight = GetClientHeight();
		setting.graphics.frameBufferWidth = GetClientWidth();
		setting.graphics.multiSampleCount = 1;
		setting.graphics.multiSampleQuality = 0;
		setting.graphics.windowed = true;
		setting.input.wnd = GetWnd();
		setting.graphics.wnd = GetWnd();

		setting.input.sysMod = "";

		setting.sound.maxChannels = 100;
		setting.sound.sysMod = "./fmod_sound_x64.dll";

		setting.physics.sysMod = "";

		setting.network.sysMod = "./network_x64.dll";

		m_pGameManager->GetGame()->AdjustSysSetting(setting);
		
		AdjustWindow(setting.graphics.frameBufferWidth, setting.graphics.frameBufferHeight);

		CoreApi::SetLogger(log);

		if(false == m_pCore->Initialize(setting))
		{
			return false;
		}

		if(false == m_pGameManager->GetGame()->Initialize(m_pCore))
		{
			return false;
		}

		return true;
	}

	void MainApp::OnRelease()
	{
		if(m_pGameManager)
		{
			m_pGameManager->GetGame()->Release();
		}

		if(m_pCore)
		{
			m_pCore->Release();
			m_pCore.reset();
		}

		if(m_pGameManager)
		{
			m_pGameManager->Release();
			m_pGameManager.reset();
		}
	}



	void MainApp::SetTitle(const char* szTitle)
	{
		SetWindowTextA(m_hWnd, szTitle);
	}
	void MainApp::ExitApp()
	{
		PostQuitMessage(0);
	}
	int MainApp::GetClientWidth()
	{
		return m_clientWidth;
	}
	int	MainApp::GetClientHeight()
	{
		return m_clientHeight;
	}
	int	MainApp::GetWindowWidth()
	{
		return m_width;
	}
	int MainApp::GetWindowHeight()
	{
		return m_height;
	}
	bool MainApp::IsActive()
	{
		return m_bActive;
	}

	void MainApp::ShowFPS()
	{
		static uint64 tick = m_pCore->GetSysTime()->Tick();

		static int frames = 0;
		uint64 dt = m_pCore->GetSysTime()->Tick() - tick;

		int iv = 100;
		if(dt >= iv)
		{

			char buffer[100];

			float fps = float(frames * 1000) / float(dt);
			sprintf(buffer, "fps : %.3f - %fms", fps, 1000.0f / fps);

			SetTitle(buffer);

			tick = m_pCore->GetSysTime()->Tick();
			frames = 0;
		}

		frames ++;
	}

	void MainApp::HandleMessage(MSG& msg)
	{
		if(m_pCore)
		{
			m_pCore->HandleMessage(msg);
		}
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
	MainApp app;

	if(false == app.Initialize(hInstance, "Main Window", 800, 600))
	{
		return -1;
	}
	app.Run();

	app.Release();

	return 0;
}
