#pragma once

#include <boost/signals2.hpp>

namespace ld3d
{
	class EventDispatcher
	{
		
		typedef boost::signals2::signal<void (EventPtr)>								Signal;
		typedef std::unordered_map<uint32, std::shared_ptr<Signal> >					HandlerMap;

	public:

		

		EventDispatcher(void);
		virtual ~EventDispatcher(void);


		void									DispatchEvent(EventPtr pEvent);
		EventHandlerID							AddEventHandler(uint32 id, const EventHandler& handler);

		void									RemoveEventHandler(EventHandlerID handler);
		void									Clear();
	private:


	private:
		HandlerMap								m_HandlerMap;

	};


}