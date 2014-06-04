#include "core_pch.h"
#include "core/FrameMetric.h"

namespace ld3d
{
	FrameMetric::FrameMetric(void)
	{
		m_totalFrames			= 0;
		m_frames				= 0;
		m_startTick				= 0;
		m_reportTick			= 0;
		m_fps					= 1;
	}


	FrameMetric::~FrameMetric(void)
	{
	}
	void FrameMetric::BeginFrame()
	{
		if(m_startTick == 0)
		{
			m_startTick = os_get_tick();
		}
		if(m_reportTick == 0)
		{
			m_reportTick = os_get_tick();
		}
	}
	void FrameMetric::EndFrame()
	{
		m_frames++;
		m_totalFrames ++;

		uint64 dt = os_get_tick() - m_reportTick;
		if(dt > 100)
		{
			UpdateFPS();
		}
	}
	float FrameMetric::GetAvgFPS() const
	{
		uint64 dt = os_get_tick() - m_startTick;
		return float(m_totalFrames * 1000) / float(dt);
	}
	
	float FrameMetric::GetFPS()
	{
		return m_fps;
	}
	void FrameMetric::UpdateFPS()
	{
		uint64 dt = os_get_tick() - m_reportTick;
		
		m_fps = float(m_frames * 1000) / float(dt);

		m_frames = 0;
		m_reportTick = os_get_tick();

		
	}
}
