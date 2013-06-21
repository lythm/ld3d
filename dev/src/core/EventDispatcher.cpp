#include "core_pch.h"
#include "..\..\include\core\EventDispatcher.h"
#include "core\Event.h"

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
		std::shared_ptr<Signal> pHandlers = m_HandlerMap[pEvent->id];
		if(pHandlers)
		{
			(*pHandlers)(pEvent);
		}
	}
	EventDispatcher::EventHandlerHandle EventDispatcher::AddEventHandler(uint32 id, const EventHandler& handler)
	{
		std::shared_ptr<Signal> pHandlers = m_HandlerMap[id];

		if(pHandlers == nullptr)
		{

			pHandlers = std::shared_ptr<Signal>(new Signal);
			m_HandlerMap[id] = pHandlers;
		}

		return pHandlers->connect(handler);
	}
	void EventDispatcher::Clear()
	{
		for(auto v : m_HandlerMap)
		{
			v.second->disconnect_all_slots();
		}
		m_HandlerMap.clear();
	}
	void EventDispatcher::RemoveEventHandler(EventHandlerHandle handler)
	{
		handler.disconnect();
	}
}
