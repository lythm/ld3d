#pragma once

#include "RenderSystem.h"

namespace ld3d
{
	class RenderSystem_DR
	{
	public:
		RenderSystem_DR(void);
		virtual ~RenderSystem_DR(void);

		bool												Initialize(Sys_GraphicsPtr pGraphics);
		void												Release();

	private:
		Sys_GraphicsPtr							m_pGraphics;
	};


}