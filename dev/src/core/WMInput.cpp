#include "core_pch.h"
#include "WMInput.h"
#include <windowsx.h>

#include "core_utils.h"
namespace ld3d
{
	WMInput::WMInput(void)
	{
	}


	WMInput::~WMInput(void)
	{
	}
	bool WMInput::Initialize(void* app_handle, EmitEvent ee)
	{
		_emit_event = ee;
		memset(&m_mouseState, 0, sizeof(m_mouseState));
		memset(&m_keyState, 0, sizeof(m_keyState));

		m_pMouseStateEvent = alloc_object<Event_MouseState>();
		m_pKeyStateEvent = alloc_object<Event_KeyboardState>();

		return true;
	}
	void WMInput::Release()
	{
	}
	void WMInput::Update()
	{
	}

	const KeyState& WMInput::GetKeyState()
	{
		return m_keyState;
	}
	const MouseState& WMInput::GetMouseState()
	{
		return m_mouseState;
	}
	void WMInput::UpdateMouseState(MSG& msg)
	{
		int xPos = GET_X_LPARAM(msg.lParam); 
		int yPos = GET_Y_LPARAM(msg.lParam); 

		m_mouseState.x = xPos;
		m_mouseState.y = yPos;


		if(msg.wParam & MK_LBUTTON)
		{
			m_mouseState.buttons[0] = 0x80;
		}
		else
		{
			m_mouseState.buttons[0] = 0;
		}

		if(msg.wParam & MK_RBUTTON)
		{
			m_mouseState.buttons[1] = 0x80;
		}
		else
		{
			m_mouseState.buttons[1] = 0;
		}

		if(msg.wParam & MK_MBUTTON)
		{
			m_mouseState.buttons[2] = 0x80;
		}
		else
		{
			m_mouseState.buttons[2] = 0;
		}

		if(msg.wParam & MK_CONTROL)
		{
			m_mouseState.control = 0x80;
		}
		else
		{
			m_mouseState.control = 0;
		}

		if(msg.wParam & MK_SHIFT)
		{
			m_mouseState.shift = 0x80;
		}
		else
		{
			m_mouseState.shift = 0;
		}

	}
	void WMInput::ProcessMouse(MSG& msg)
	{
		switch(msg.message)
		{
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			{
				UpdateMouseState(msg);

				m_pMouseStateEvent->id = EV_MOUSE_BUTTON;
			}
			break;

		case WM_MOUSEWHEEL:
			{
				m_mouseState.wheel = -GET_WHEEL_DELTA_WPARAM(msg.wParam);
				UpdateMouseState(msg);

				m_pMouseStateEvent->id = EV_MOUSE_WHEEL;
			}

			break;
		case WM_MOUSEMOVE:
			{
				UpdateMouseState(msg);
				m_pMouseStateEvent->id = EV_MOUSE_MOVE;
			}
			break;

		default:
			return;
		}
		m_pMouseStateEvent->mouse_state = &m_mouseState;

		if(_emit_event)
		{
			_emit_event(m_pMouseStateEvent);
		}
	}
	void WMInput::HandleMessage(MSG& msg)
	{
		ProcessMouse(msg);
	}
}
