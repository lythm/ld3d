#include "pch.h"

#include "MainApp.h"
#include <tchar.h>

#include <boost/date_time.hpp>

namespace ld3d
{
	static std::ofstream						s_log;

	void open_log()
	{
		boost::filesystem::path p("./log");
		if(boost::filesystem::exists("./log") == false)
		{
			boost::filesystem::create_directory("./log");
		}

		std::string date = boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time());
		
		s_log.open((p / date).string() + ".log", std::ios_base::app);
		s_log << date << "\n";

	}
	void log(const std::string& text)
	{
		if(s_log.is_open() == false)
		{
			open_log();
		}

		s_log << text;
		s_log.flush();

		OutputDebugStringA(text.c_str());
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

		CenterWindow();
		

		ShowWindow(m_hWnd, SW_SHOW);
		UpdateWindow(m_hWnd);

		if(OnInit() == false)
		{
			return false;
		}

		return true;
	}

	void MainApp::CenterWindow()
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
		while( true )
		{
			while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
			{
				HandleMessage(msg);

				TranslateMessage( &msg );
				DispatchMessage( &msg );
			
				if(WM_QUIT == msg.message)
				{
					return;
				}
			}
			
			if(m_bActive)
			{
				OnUpdate();
			}
			else
			{
				Sleep(1);
			}
		}

		return;
	}
	void MainApp::OnUpdate()
	{
		m_pCore->RunFrame();
	}

	bool MainApp::OnInit()
	{

		m_pConfig = std::make_shared<MainConfig>();
		if(m_pConfig->Load("./main.win.x64.conf.xml") == false)
		{
			return false;
		}

		m_pCore = std::make_shared<CoreApi>(Logger(log));

		SysSetting setting = m_pConfig->GetSysSetting();
		
		setting.input.wnd = GetWnd();
		setting.graphics.wnd = GetWnd();
		setting.input.sysMod = "";
		
		setting.app_delegate.CenterWindow = std::bind(&MainApp::CenterWindow, this);
		setting.app_delegate.ExitApp = std::bind(&MainApp::ExitApp, this);
		setting.app_delegate.GetWindowSize = std::bind(&MainApp::GetClientSize, this, std::placeholders::_1, std::placeholders::_2);
		setting.app_delegate.SetWindowSize = std::bind(&MainApp::AdjustWindow, this, std::placeholders::_1, std::placeholders::_2);
		setting.app_delegate.SetWindowTitle = std::bind(&MainApp::SetTitle, this, std::placeholders::_1);


		AdjustWindow(setting.graphics.frameBufferWidth, setting.graphics.frameBufferHeight);


		for(auto package : m_pConfig->GetPackageList())
		{
			setting.packages.push_back(package.string());
		}

		setting.mod = m_pConfig->GetMod().string();

		if(false == m_pCore->Initialize(setting))
		{
			return false;
		}

		return true;
	}

	void MainApp::OnRelease()
	{
		if(m_pCore)
		{
			m_pCore->Release();
			m_pCore.reset();
		}
	}

	void MainApp::SetTitle(const std::string& szTitle)
	{
		SetWindowTextA(m_hWnd, szTitle.c_str());
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
	
	void MainApp::HandleMessage(MSG& msg)
	{
		if(m_pCore)
		{
			m_pCore->HandleMessage(msg);
		}
	}
	void MainApp::GetClientSize(int& w, int& h)
	{
		w = m_width;
		h = m_height;
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
