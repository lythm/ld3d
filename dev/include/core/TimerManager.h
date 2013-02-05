#pragma once


namespace ld3d
{
	class TimerManager
	{
	public:
		typedef void*					timer_handle;

	public:

		struct TimerNode
		{
			uint64													interval;
			uint64													start_tick;

			boost::function<void (timer_handle,  uint64)>			handler;
			
			TimerNode*												prev;
			TimerNode*												next;
		};

		TimerManager(void);
		virtual ~TimerManager(void);

		bool														Init(Sys_TimePtr pTime);
		void														Release();
		void														Update();

		timer_handle												RegisterTimer(uint64 interval, const boost::function<void (timer_handle, uint64)>& handler);

		void														RemoveTimer(timer_handle timer);

	private:
		void														InsertNode(TimerNode* pNewNode);
		void														UnLink(TimerNode* pNode);
		void														CleanRemove();
	private:
		TimerNode*													m_head;
		std::vector<TimerNode*>										m_remove;

		Sys_TimePtr													m_pTime;
	};
}