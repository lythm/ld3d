#include "core_pch.h"
#include "core/EventDispatcher.h"
#include "core/Event.h"
#include "core_utils.h"
namespace ld3d
{
	EventDispatcher::EventDispatcher(void)
	{
	}


	EventDispatcher::~EventDispatcher(void)
	{
		Clear();
	}
	
	void EventDispatcher::DispatchEvent(EventPtr pEvent)
	{
		/*if(pEvent->id == EV_WINMSG)
		{
			Event_WindowMessage* pMsg = (Event_WindowMessage*)pEvent.get();
			if(pMsg->msg.message == WM_CHAR)
			{
				logger() << (char)pMsg->msg.wParam;
			}
		}*/

		std::shared_ptr<Signal> pHandlers = m_HandlerMap[pEvent->id];
		if(pHandlers)
		{
			(*pHandlers)(pEvent);
		}
	}
	EventHandlerID EventDispatcher::AddEventHandler(uint32 id, const EventHandler& handler)
	{
		std::shared_ptr<Signal> pHandlers = m_HandlerMap[id];

		if(pHandlers == nullptr)
		{
			pHandlers = alloc_object<Signal>();
			m_HandlerMap[id] = pHandlers;
		}

		return pHandlers->connect(handler);
	}
	void EventDispatcher::Clear()
	{
		for(auto v : m_HandlerMap)
		{
			if(v.second)
			{
				v.second->disconnect_all_slots();
			}
		}

		m_HandlerMap.clear();
	}
	void EventDispatcher::RemoveEventHandler(EventHandlerID handler)
	{
		handler.disconnect();
	}
}
