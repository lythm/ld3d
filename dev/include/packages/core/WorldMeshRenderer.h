#pragma once

#include "core/GameObjectComponent.h"

namespace ld3d
{

	class WorldMeshRenderer : public GameObjectComponent
	{
	public:
		WorldMeshRenderer(GameObjectManagerPtr pManager):GameObjectComponent("WorldMeshRenderer", pManager){}
		virtual ~WorldMeshRenderer(void){}

	};

}