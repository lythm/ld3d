#pragma once

#include <platform/platform.h>


namespace ld3d
{
	class Sys_Time
	{
	public:

		virtual float Second()
		{
			return float(Tick() / 1000.0f);
		}
		virtual uint64 Tick()
		{
			if(m_paused)
			{
				return m_pausedTick - m_dt - m_startTick;
			}

			uint64 t = _get_tick();
			return _get_tick() - m_dt - m_startTick;
		}

		virtual void Pause()
		{
			if(m_paused == true)
			{
				return;
			}
			m_paused = true;
			m_pausedTick = _get_tick();
		}
		virtual void Resume()
		{
			if(m_paused == false)
			{
				return;
			}
			m_paused = false;
			m_dt += _get_tick() - m_pausedTick;

		}

		virtual void Start()
		{
			m_paused			= false;
			m_dt				= 0;
			m_pausedTick		= 0;
			m_startTick			= _get_tick();
		}
		virtual void Stop()
		{
		}

		virtual void Update()
		{
		}

	protected:
		virtual uint64								_get_tick()										= 0;
	protected:

		Sys_Time(void)
		{
			m_paused			= false;
			m_dt				= 0;
			m_pausedTick		= 0;
			m_startTick			= 0;
		}

		virtual ~Sys_Time(void){}

	protected:
		bool								m_paused;
		uint64								m_dt;
		uint64								m_pausedTick;
		uint64								m_startTick;
	};
}
