#pragma once

#include <boost/signals2.hpp>

namespace ld3d
{
	class EventDispatcher
	{
	public:

		typedef std::function<void (EventPtr)>											EventHandler;

		typedef boost::signals2::signal<void (EventPtr)>								Signal;

		typedef boost::signals2::connection												EventHandlerHandle;

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