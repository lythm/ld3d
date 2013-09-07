#pragma once

#include "input_types.h"


namespace ld3d
{
	enum EVENT_ID
	{
		EV_WINMSG,
		EV_RESIZE_FRAMEBUFFER,
		EV_FRUSTUM_CULL,
		EV_KEYBOARD_STATE,
		EV_MOUSE_MOVE,
		EV_MOUSE_WHEEL,
		EV_MOUSE_BUTTON,
		
	};
	class Event
	{
	public:
		Event(uint32 _id)
		{
			id = _id;
		}
		virtual ~Event(void){}

		uint32								id;
	};

	class Event_MouseState : public Event
	{
	public:
		Event_MouseState() : Event((uint32)-1)
		{
		}
		MouseState*					mouse_state;
	};
	
	class Event_KeyboardState : public Event
	{
	public:
		Event_KeyboardState() : Event(EV_KEYBOARD_STATE)
		{
		}
			
		KeyState*					key_State;

	};
	class Event_ResizeFrameBuffer : public Event
	{
	public:
		Event_ResizeFrameBuffer(int cx, int cy) : Event(EV_RESIZE_FRAMEBUFFER)
		{
			m_width = cx;
			m_height = cy;
		}

		int							m_width;
		int							m_height;
	};

	class Event_FrustumCull : public Event
	{
	public:
		Event_FrustumCull(BaseCameraPtr pCamera) : Event(EV_FRUSTUM_CULL)
		{
			m_pCamera	= pCamera;
		}

		BaseCameraPtr				m_pCamera;
	};

#if defined(WIN32) || defined(WIN64)
	class Event_WindowMessage: public Event
	{
	public:
		Event_WindowMessage(const MSG& m) : Event(EV_WINMSG)
		{
			msg = m;
		}
		virtual ~Event_WindowMessage(){}

		MSG									msg;
	};
#endif
}
