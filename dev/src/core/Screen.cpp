#include "core_pch.h"
#include "core/Screen.h"

#include "core/CoreApi.h"
#include "core/RenderManager.h"
#include "core/Sys_Graphics.h"

namespace ld3d
{

	Screen::Screen(CoreApiPtr pCore)
	{
		m_pCore = pCore;
	}


	Screen::~Screen(void)
	{
	}
	void Screen::SetResolution(uint32 w, uint32 h, bool fullscreen)
	{
		m_pCore->GetRenderManager()->ResizeFramebuffer(w, h, fullscreen);
	}
	bool Screen::IsWindowed()
	{
		return !m_pCore->GetRenderManager()->IsFullscreen();
	}
	uint32 Screen::GetRenderWindowWidth()
	{
		return m_pCore->GetSysGraphics()->GetRenderWindowWidth();
	}
	uint32 Screen::GetRenderWindowHeight()
	{
		return m_pCore->GetSysGraphics()->GetRenderWindowHeight();
	}
	uint32 Screen::GetFramebufferWidth()
	{
		return m_pCore->GetSysGraphics()->GetFrameBufferWidth();
	}
	uint32 Screen::GetFramebufferHeight()
	{
		return m_pCore->GetSysGraphics()->GetFrameBufferHeight();
	}
	void Screen::SetResolution(uint32 w, uint32 h)
	{
		SetResolution(w, h, !IsWindowed());
	}
	void Screen::SetWindowed(bool windowed)
	{
		int cx = GetFramebufferWidth();
		int cy = GetFramebufferHeight();
		SetResolution(cx, cy, !windowed);
	}
}
