#pragma once
#include <memory>

#include "core/g_format.h"

namespace ld3d
{
	namespace atmosphere
	{

		enum
		{
			LT_SKYLIGHT													= LT_USER + 1,
		};
		class SkyLight;
		class SkyDome;

		typedef std::shared_ptr<SkyLight>								SkyLightPtr;
		typedef std::shared_ptr<SkyDome>								SkyDomePtr;
	}
}