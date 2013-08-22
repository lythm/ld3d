#pragma once

#include "GameManager.h"
namespace ld3d
{
	class MainApp
	{
	public:
		MainApp(void);
		virtual ~MainApp(void);

		bool													Initialize(HINSTANCE hInst, const std::string& title, int w, int h);

		void													Release();

		void													Run();
	protected:

		void													ShowFPS();

		void													SetTitle(const char* szTitle);
		void													ExitApp();
		
		virtual void											OnUpdate();
		virtual bool											OnInit();
		virtual void											OnRelease();


		virtual void											HandleMessage(MSG& msg);

		void													AdjustWindow(int Width, int Height );

		static LRESULT CALLBACK									WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		HWND													GetWnd();

		int														GetClientWidth();
		int														GetClientHeight();

		int														GetWindowWidth();
		int														GetWindowHeight();

		static bool												IsActive();
	protected:

		HINSTANCE												m_hInst;
		HWND													m_hWnd;

		std::string												m_wndClass;
		std::string												m_wndTitle;

		int														m_width;
		int														m_height;

		int														m_clientWidth;
		int														m_clientHeight;

		static bool												m_bActive;

		GameManagerPtr											m_pGameManager;
		CoreApiPtr												m_pCore;
	};


}