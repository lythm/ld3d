#include "core_pch.h"
#include "RenderSystem_DR.h"

namespace ld3d
{
	RenderSystem_DR::RenderSystem_DR(void)
	{
	}


	RenderSystem_DR::~RenderSystem_DR(void)
	{
	}
	bool RenderSystem_DR::Initialize(Sys_GraphicsPtr pGraphics)
	{
		m_pGraphics = pGraphics;
		return true;
	}
	void RenderSystem_DR::Release()
	{
		m_pGraphics.reset();
	}
}