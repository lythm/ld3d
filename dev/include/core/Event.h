#pragma once

#include "input_types.h"


namespace ld3d
{
	enum EVENT_ID
	{
		EV_UNKNOWN,

		EV_ENGINE_INITIALIZED,
		EV_ENGINE_ABOUT_TO_RELEASE,


		EV_SCENE_LOADED,
		EV_SCENE_SAVED,

		EV_WINMSG,
		EV_RESIZE_FRAMEBUFFER,
		EV_FRUSTUM_CULL,
		EV_KEYBOARD_STATE,
		EV_CHAR,
		EV_MOUSE_MOVE,
		EV_MOUSE_WHEEL,
		EV_MOUSE_BUTTON,

		EV_BEGIN_FRAME,
		EV_END_FRAME,

		
		EV_SYS_EVENT_COUNT,

		EV_CUSTOM_EVENT = EV_SYS_EVENT_COUNT + 1000,

		
	};
	class Event
	{
	public:
		Event(uint32 _id = EV_UNKNOWN)
		{
			id = _id;
		}
		virtual ~Event(void){}

		uint32								id;
	};
	class Event_BeginFrame : public Event
	{
	public:
		Event_BeginFrame(float _dt) : Event(EV_BEGIN_FRAME)
		{
			dt = _dt;
		}

		float								dt;
	};
	class Event_EndFrame : public Event
	{
	public:
		Event_EndFrame(float _dt) : Event(EV_END_FRAME)
		{
			dt = _dt;
		}
		float								dt;
	};
	class Event_MouseState : public Event
	{
	public:
		Event_MouseState() : Event((uint32)-1)
		{
			mouse_state				= nullptr;
		}
		MouseState*					mouse_state;
	};
	
	class Event_KeyboardState : public Event
	{
	public:
		Event_KeyboardState() : Event(EV_KEYBOARD_STATE)
		{
			key_code				= 0;
			keyboard_state			= nullptr;
		}
			

		bool						IsKeyUp()
		{
			return keyboard_state->KeyDown(key_code) == false;
		}
		bool						IsKeyDown()
		{
			return IsKeyUp() == false;
		}

		uint32						key_code;
		KeyState*					keyboard_state;

		uint32						vk_code;

	};
	class Event_Char : public Event
	{
	public:
		Event_Char(uint32 key) : Event(EV_CHAR)
		{
			key_code = key;
		}
		uint32						key_code;
	};
	class Event_ResizeFrameBuffer : public Event
	{
	public:
		Event_ResizeFrameBuffer(int cx, int cy) : Event(EV_RESIZE_FRAMEBUFFER)
		{
			w = cx;
			h = cy;
		}

		int							w;
		int							h;
	};


	class Event_FrustumCull : public Event
	{
	public:
		Event_FrustumCull(math::ViewFrustum* vf) : Event(EV_FRUSTUM_CULL)
		{
			m_pViewFrustum	= vf;
		}

		math::ViewFrustum*					m_pViewFrustum;
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
