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
	}
	float FrameMetric::GetAvgFPS()
	{
		uint64 dt = os_get_tick() - m_startTick;
		return float(m_totalFrames * 1000) / float(dt);
	}
	
	float FrameMetric::GetFPS()
	{
		uint64 dt = os_get_tick() - m_reportTick;
		float fps = float(m_frames * 1000) / float(dt);

		m_frames = 0;
		m_reportTick = os_get_tick();

		return fps;
	}
}
