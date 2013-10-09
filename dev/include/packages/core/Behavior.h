#pragma once

#include "core/GameObjectComponent.h"

namespace ld3d
{
	class Behavior : public GameObjectComponent
	{
	public:
		Behavior(GameObjectManagerPtr pManager)  : GameObjectComponent("Behavior", pManager){}
		virtual ~Behavior(void){}



	};
}
