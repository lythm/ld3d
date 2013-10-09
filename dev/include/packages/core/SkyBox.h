#pragma once

#include "core/GameObjectComponent.h"

namespace ld3d
{
	class SkyBox : public GameObjectComponent
	{
	public:
		SkyBox(GameObjectManagerPtr pManager) : GameObjectComponent("SkyBox", pManager){}
		virtual ~SkyBox(void){}

	};
}