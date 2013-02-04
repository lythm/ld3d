#include "core_pch.h"
#include "Time64.h"

namespace ld3d
{
	Time64::Time64(void)
	{
		m_paused			= false;
		m_dt				= 0;
		m_pausedTick		= 0;
		m_startTick			= 0;
	}


	Time64::~Time64(void)
	{
	}

	uint64 Time64::Tick()
	{
		if(m_paused)
		{
			return m_pausedTick - m_dt - m_startTick;
		}

		uint64 t = _get_tick();
		return _get_tick() - m_dt - m_startTick;
	}
	void Time64::Pause()
	{
		if(m_paused == true)
		{
			return;
		}
		m_paused = true;
		m_pausedTick = _get_tick();
	}
	void Time64::Resume()
	{
		if(m_paused == false)
		{
			return;
		}
		m_paused = false;
		m_dt += _get_tick() - m_pausedTick;

	}

	void Time64::Start()
	{
		m_paused			= false;
		m_dt				= 0;
		m_pausedTick		= 0;
		m_startTick			= _get_tick();
	}
	uint64 Time64::_get_tick()
	{
		return (uint64)GetTickCount64();
	}
	float Time64::Second()
	{
		return float(Tick() / 1000.0f);
	}
	void Time64::Stop()
	{

	}
	void Time64::Update()
	{
	}
}
