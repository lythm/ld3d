#pragma once

#include <platform/platform.h>
#include "core/input_types.h"
#include "core/Event.h"

namespace ld3d
{
	class Sys_Input
	{
	public:

		typedef std::function<void (EventPtr)>						EmitEvent;

		virtual bool												Initialize(void* app_handle, EmitEvent ee)							= 0;
		virtual void												Release()															= 0;
		virtual void												Update()															= 0;

		virtual void												ClipCursor(const math::Rect<long>& rc)								= 0;
		virtual void												SetCursorPos(int x, int y)											= 0;
		virtual void												GetCursorPos(int& x, int& y)										= 0;
		virtual void												ShowCursor(bool bShow)												= 0;
		
		virtual const KeyState&										GetKeyState()														= 0;
		virtual const MouseState&									GetMouseState()														= 0;

#if defined(WIN32) || defined(WIN64)
		virtual void												HandleMessage(MSG& msg)												= 0;
#endif
	
		Sys_Input(void){}
		virtual ~Sys_Input(void){}
	};


}