#pragma once

#include "platform/platform.h"
#include "utils/logger.h"

namespace ld3d
{
	class Sys_Graphics;
}
_DLL_API ld3d::Sys_Graphics* CreateSysGraphics(ld3d::Logger& logger);

_DLL_API void DestroySysGraphics(ld3d::Sys_Graphics* pSys);