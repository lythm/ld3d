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

		void												ShowCursor(bool bShow);

	private:
		bool												RegisterDevices();

		void												ProcessChar(MSG& msg);
		void												ProcessRawInput(MSG& msg);
		void												ProcessMouse(RAWINPUT* pInput);
		void												ProcessKeyboard(RAWINPUT* pInput);
	private:
		KeyState											m_keyState;
		MouseState											m_mouseState;
		
		EmitEvent											_emit_event;
		
		std::shared_ptr<Event_MouseState>					m_pMouseStateEvent;
		std::shared_ptr<Event_KeyboardState>				m_pKeyStateEvent;
		std::shared_ptr<Event_Char>							m_pCharEvent;
		uint32												m_inputBufferBytes;
		uint8*												m_inputBuffer;
	};
}