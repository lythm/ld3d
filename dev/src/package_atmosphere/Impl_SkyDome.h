#pragma once

#include "packages/atmosphere/SkyDome.h"

namespace ld3d
{
	namespace atmosphere
	{
		class Impl_SkyDome : public SkyDome
		{
		public:
			Impl_SkyDome(GameObjectManagerPtr pManager);
			virtual ~Impl_SkyDome(void);
		};
	}
}