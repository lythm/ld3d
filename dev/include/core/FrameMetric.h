#pragma once

namespace ld3d
{
	class _DLL_CLASS FrameMetric
	{
	public:
		FrameMetric(void);
		virtual ~FrameMetric(void);

		void											BeginFrame();
		void											EndFrame();

		float											GetAvgFPS() const;
		float											GetFPS();

	private:

		void											UpdateFPS();

		uint64											m_totalFrames;
		uint64											m_startTick;


		uint64											m_frames;
		uint64											m_reportTick;

		float											m_fps;
	};
}
