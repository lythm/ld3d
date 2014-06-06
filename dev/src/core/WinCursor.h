#pragma once


#include "core/Cursor.h"

namespace ld3d
{
	class WinCursor : public Cursor
	{
	public:
		WinCursor(void);
		virtual ~WinCursor(void);


		void												SetCursorPos(int x, int y);
		void												GetCursorPos(int& x, int& y);
		void												ConfineCursor(bool confine);

		void												HandleMessage(MSG& msg);
		void												ShowCursor(bool show);
	private:
		void												do_confine(HWND hWnd);
	private:
		bool												m_confine;

	};


}