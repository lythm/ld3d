#include "core_pch.h"
#include "WinCursor.h"
#include "core_utils.h"

namespace ld3d
{
	WinCursor::WinCursor(void)
	{
		m_confine = false;
	}


	WinCursor::~WinCursor(void)
	{
	}
	void WinCursor::ShowCursor(bool show)
	{
		::ShowCursor(show);
	}
	void WinCursor::SetCursorPos(int x, int y)
	{
		::SetCursorPos(x, y);
	}
	void WinCursor::GetCursorPos(int& x, int& y)
	{
		POINT pt;
		::GetCursorPos(&pt);
		x = pt.x;
		y = pt.y;

	}
	void WinCursor::ConfineCursor(bool confine)
	{
		m_confine = confine;
	}
	void WinCursor::HandleMessage(MSG& msg)
	{
		
		switch(msg.message)
		{
		case WM_SHOWWINDOW:
			if(m_confine == false)
			{
				break;
			}
			if(msg.wParam)
			{
				do_confine(msg.hwnd);
			}
			else
			{
				::ClipCursor(NULL);
			}
			
			break;

		case WM_ACTIVATE:
			if(m_confine == false)
			{
				break;
			}

			if(LOWORD(msg.wParam) == WA_ACTIVE || LOWORD(msg.wParam) == WA_CLICKACTIVE)
			{
				do_confine(msg.hwnd);
			}
			if(LOWORD(msg.wParam) == WA_INACTIVE)
			{
				::ClipCursor(NULL);
			}
			break;
		case WM_SIZE:
			if(m_confine)
			{
				do_confine(msg.hwnd);
			}
		case WM_WINDOWPOSCHANGED:
			if(m_confine)
			{
				do_confine(msg.hwnd);
			}
			break;
		default:
			break;
		}
	}
	void WinCursor::do_confine(HWND hWnd)
	{
		RECT rc;

		GetClientRect(hWnd, &rc);

		POINT pt;
		pt.x = 0;
		pt.y = 0;
		ClientToScreen(hWnd, &pt);


		rc.left += pt.x;
		rc.right += pt.x;

		rc.top += pt.y;
		rc.bottom += pt.y;

		ClipCursor(&rc);
	}
}

