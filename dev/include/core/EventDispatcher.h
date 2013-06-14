#pragma once

#include <boost\signal.hpp>

namespace ld3d
{
	class EventDispatcher
	{
	public:

		typedef std::function<void (EventPtr)>											EventHandler;

		typedef boost::signal<void (EventPtr)>											Signal;

		typedef boost::signals::connection												EventHandlerHandle;

		typedef std::unordered_map<uint32, std::shared_ptr<Signal> >					HandlerMap;

		EventDispatcher(void);
		virtual ~EventDispatcher(void);


		void									DispatchEvent(EventPtr pEvent);
		EventHandlerHandle						AddEventHandler(uint32 id, const EventHandler& handler);
		void									RemoveEventHandler(EventHandlerHandle handler);
		void									Clear();
	private:


	private:
		HandlerMap								m_HandlerMap;

	};


}