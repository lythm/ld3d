#pragma once


#include "core\Sys_Time.h"

namespace ld3d
{
	class Time64 : public Sys_Time
	{
	public:
		Time64(void);
		virtual ~Time64(void);

		float								Second();
		uint64								Tick();
		void								Pause();
		void								Resume();

		void								Start();
		void								Stop();

		void								Update();
	private:

		uint64								_get_tick();

	private:

		bool								m_paused;
		uint64								m_dt;
		uint64								m_pausedTick;
		uint64								m_startTick;

	};


}