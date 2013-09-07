#pragma once

#include "core/Sys_Input.h"

#if defined(_WIN64) || defined(_WIN32)
namespace ld3d
{
	class WMInput : public Sys_Input
	{
	public:
		WMInput(void);
		virtual ~WMInput(void);


		bool												Initialize(void* app_handle, EmitEvent ee);
		void												Release();
		void												Update();

		
		const KeyState&										GetKeyState();
		const MouseState&									GetMouseState();

		void												HandleMessage(MSG& msg);

	private:
		void												ProcessMouse(MSG& msg);

		void												UpdateMouseState(MSG& msg);
	private:
		KeyState											m_keyState;
		MouseState											m_mouseState;
		
		EmitEvent											_emit_event;


		std::shared_ptr<Event_MouseState>					m_pMouseStateEvent;
		std::shared_ptr<Event_KeyboardState>				m_pKeyStateEvent;

	};


}

#endif