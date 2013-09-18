#pragma once

#include "core/Sys_Input.h"

namespace ld3d
{
	class WinRawInput : public Sys_Input
	{
	public:
		WinRawInput(void);
		virtual ~WinRawInput(void);

		bool												Initialize(void* app_handle, EmitEvent ee);
		void												Release();
		void												Update();

		
		const KeyState&										GetKeyState();
		const MouseState&									GetMouseState();

		void												HandleMessage(MSG& msg);


	private:
		bool												RegisterDevices();

		void												ProcessMouse(RAWINPUT* pInput);
		void												ProcessKeyboard(RAWINPUT* pInput);
	private:
		KeyState											m_keyState;
		MouseState											m_mouseState;
		
		EmitEvent											_emit_event;
		
		std::shared_ptr<Event_MouseState>					m_pMouseStateEvent;
		std::shared_ptr<Event_KeyboardState>				m_pKeyStateEvent;

		uint32												m_inputBufferBytes;
		uint8*												m_inputBuffer;
	};
}