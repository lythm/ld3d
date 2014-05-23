#pragma once

#include "core/GameObjectComponent.h"
namespace ld3d
{
	class WaterBody : public GameObjectComponent
	{
	public:


	protected:
		WaterBody(GameObjectManagerPtr pManager):GameObjectComponent("WaterBody", pManager){}
		
		virtual ~WaterBody(void){}
	};


}
