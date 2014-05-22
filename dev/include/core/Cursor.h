#pragma once


namespace ld3d
{
	class Cursor
	{
	public:

		virtual void												SetCursorPos(int x, int y)									= 0;
		virtual void												GetCursorPos(int& x, int& y)								= 0;
		
		virtual void												ConfineCursor(bool confine)									= 0;



	protected:
		Cursor(void){}
		virtual ~Cursor(void){}
	};


}