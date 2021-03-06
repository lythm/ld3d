#pragma once

#include "core/GameObjectComponent.h"


namespace ld3d
{

	class MeshAnimator : public GameObjectComponent
	{
	public:
		MeshAnimator(GameObjectManagerPtr pManager) : GameObjectComponent("MeshAnimator", pManager){}
		virtual ~MeshAnimator(void){}
	};

}

