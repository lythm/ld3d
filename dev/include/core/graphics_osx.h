#pragma once

#include "platform/platform.h"
#include "utils/logger.h"
#include <memory>

namespace ld3d
{
	class Sys_Graphics;
}
_DLL_API ld3d::Sys_Graphics* CreateSysGraphics(ld3d::Logger& logger);

_DLL_API void DestroySysGraphics(ld3d::Sys_Graphics* pSys);

namespace ld3d
{
	inline
	std::shared_ptr<Sys_Graphics>	CreateSysGraphicsPtr(Logger& logger)
	{
		return std::shared_ptr<Sys_Graphics>(CreateSysGraphics(logger), [&](Sys_Graphics* pGraphics)
											 {
												if(pGraphics == nullptr)
												{
													return;
												}
												 DestroySysGraphics(pGraphics);

											 });
	
	}
}