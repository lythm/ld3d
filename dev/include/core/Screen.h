#pragma once

namespace ld3d
{
	class Screen
	{
	public:
		Screen(CoreApiPtr pCore);
		virtual ~Screen(void);

		void													SetWindowed(bool windowed);
		void													SetResolution(uint32 w, uint32 h);
		void													SetResolution(uint32 w, uint32 h, bool fullscreen);
		bool													IsWindowed();

		uint32													GetRenderWindowWidth();
		uint32													GetRenderWindowHeight();
		uint32													GetFramebufferWidth();
		uint32													GetFrameBufferHeight();
	private:
		CoreApiPtr												m_pCore;
	};

}