#pragma once

#include "core/GameObjectComponent.h"

namespace ld3d
{
	class CameraData : public GameObjectComponent
	{
	public:
		CameraData(GameObjectManagerPtr pManager) : GameObjectComponent("CameraData", pManager){}
		virtual ~CameraData(void){}


	};
}
