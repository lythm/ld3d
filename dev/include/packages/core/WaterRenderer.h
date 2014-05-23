#pragma once

#include "core/GameObjectComponent.h"
namespace ld3d
{
	class WaterRenderer : public GameObjectComponent
	{
	public:

	

	protected:
		WaterRenderer(GameObjectManagerPtr pManager):GameObjectComponent("WaterRenderer", pManager){}
		virtual ~WaterRenderer(void){}
	};


}
