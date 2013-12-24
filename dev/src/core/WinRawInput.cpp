#include "core_pch.h"
#include "WinRawInput.h"

#include "core/Event.h"
#include "core_utils.h"
namespace ld3d
{
	WinRawInput::WinRawInput(void)
	{
		m_inputBufferBytes					= 0;
		m_inputBuffer						= nullptr;

	}


	WinRawInput::~WinRawInput(void)
	{
	}
	bool WinRawInput::Initialize(void* app_handle, EmitEvent ee)
	{
		_emit_event = ee;
		memset(&m_mouseState, 0, sizeof(m_mouseState));
		memset(&m_keyState, 0, sizeof(m_keyState));

		m_pMouseStateEvent	= alloc_object<Event_MouseState>();
		m_pKeyStateEvent	= alloc_object<Event_KeyboardState>();
		m_pCharEvent		= alloc_object<Event_Char>(0);
		m_inputBufferBytes					= 0;
		m_inputBuffer						= nullptr;

		RegisterDevices();

		POINT p;
		p.x = 0;
		p.y = 0;

		RECT rc;
		GetClientRect((HWND)app_handle, &rc);

		p.x = (rc.right - rc.left) / 2;
		p.y = (rc.bottom - rc.top) / 2;

		ClientToScreen((HWND)app_handle, &p);

		SetCursorPos(p.x, p.y);
		return true;
	}
	void WinRawInput::Release()
	{
		if(m_inputBuffer)
		{
			mem_free(m_inputBuffer);
			m_inputBuffer = nullptr;
		}
		m_inputBufferBytes = 0;
	}
	void WinRawInput::Update()
	{
	}
	const KeyState&	WinRawInput::GetKeyState()
	{
		return m_keyState;
	}
	const MouseState& WinRawInput::GetMouseState()
	{
		return m_mouseState;
	}
	bool WinRawInput::RegisterDevices()
	{
		RAWINPUTDEVICE Rid[2];

		Rid[0].usUsagePage = 0x01; 
		Rid[0].usUsage = 0x02; 
		Rid[0].dwFlags = 0;   
		Rid[0].hwndTarget = 0;

		Rid[1].usUsagePage = 0x01; 
		Rid[1].usUsage = 0x06; 
		Rid[1].dwFlags = 0;   
		Rid[1].hwndTarget = 0;

		if (RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])) == FALSE)
		{
			logger() << "failed to register input device. \n";
			return false;
		}

		return true;
	}
	void WinRawInput::ProcessRawInput(MSG& msg)
	{
		UINT dwSize;

		GetRawInputData((HRAWINPUT)msg.lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));

		if(dwSize > m_inputBufferBytes)
		{
			m_inputBufferBytes = dwSize;

			mem_free(m_inputBuffer);
			m_inputBuffer = (uint8*)mem_alloc(dwSize);
		}

		if (GetRawInputData((HRAWINPUT)msg.lParam, RID_INPUT, m_inputBuffer, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize )
		{
			logger() << "GetRawInputData does not return correct size !\n"; 
			return;
		}

		RAWINPUT* raw = (RAWINPUT*)m_inputBuffer;

		if (raw->header.dwType == RIM_TYPEKEYBOARD) 
		{
			ProcessKeyboard(raw);
		}
		else if (raw->header.dwType == RIM_TYPEMOUSE) 
		{
			ProcessMouse(raw);
		} 
	}
	void WinRawInput::HandleMessage(MSG& msg)
	{
		switch(msg.message)
		{
		case WM_INPUT:
			ProcessRawInput(msg);
			break;
		case WM_CHAR:
			ProcessChar(msg);
			break;
		default:
			break;
		}
		
	}
	void WinRawInput::ProcessChar(MSG& msg)
	{
		m_pCharEvent->key_code = msg.wParam;
		_emit_event(m_pCharEvent);
	}
	void WinRawInput::ProcessMouse(RAWINPUT* pInput)
	{
		m_mouseState.dx = pInput->data.mouse.lLastX;
		m_mouseState.dy = pInput->data.mouse.lLastY;

		m_mouseState.x += pInput->data.mouse.lLastX;
		m_mouseState.y += pInput->data.mouse.lLastY;

		m_pMouseStateEvent->mouse_state = &m_mouseState;

		bool button = false;

		if(pInput->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN)
		{
			m_mouseState.buttons[0] = 0x80;
			button = true;
		}

		if(pInput->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP)
		{
			m_mouseState.buttons[0] = 0;
			button = true;
		}

		if(pInput->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN)
		{
			m_mouseState.buttons[1] = 0x80;
			button = true;
		}

		if(pInput->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP)
		{
			m_mouseState.buttons[1] = 0;
			button = true;
		}

		if(pInput->data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN)
		{
			m_mouseState.buttons[2] = 0x80;
			button = true;
		}

		if(pInput->data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP)
		{
			m_mouseState.buttons[2] = 0;
			button = true;
		}

		bool wheel = false;
		if(pInput->data.mouse.usButtonFlags & RI_MOUSE_WHEEL)
		{
			m_mouseState.wheel = -(short)pInput->data.mouse.usButtonData;
			wheel = true;
		}
		
		if(button)
		{
			m_pMouseStateEvent->id = EV_MOUSE_BUTTON;
			_emit_event(m_pMouseStateEvent);
		}

		if(wheel)
		{
			m_pMouseStateEvent->id = EV_MOUSE_WHEEL;
			_emit_event(m_pMouseStateEvent);
		}

		m_pMouseStateEvent->id = EV_MOUSE_MOVE;
		_emit_event(m_pMouseStateEvent);
		
	}
	void WinRawInput::ProcessKeyboard(RAWINPUT* pInput)
	{
		m_keyState.keys[pInput->data.keyboard.MakeCode] = (pInput->data.keyboard.Flags == 0) ? 0x80 : 0;
		
		m_pKeyStateEvent->key_code = pInput->data.keyboard.MakeCode;
		m_pKeyStateEvent->keyboard_state = &m_keyState;
		m_pKeyStateEvent->vk_code = pInput->data.keyboard.VKey;

		_emit_event(m_pKeyStateEvent);

	}
	void WinRawInput::ShowCursor(bool bShow)
	{
		::ShowCursor(bShow ? TRUE : FALSE);
	}
}
