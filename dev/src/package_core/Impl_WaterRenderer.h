#pragma once

#include "packages/core/WaterRenderer.h"

namespace ld3d
{
	class Impl_WaterRenderer : public WaterRenderer
	{
	public:
		Impl_WaterRenderer(GameObjectManagerPtr pManager);
		virtual ~Impl_WaterRenderer(void);
	};


}