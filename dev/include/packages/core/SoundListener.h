#pragma once

#include "core/GameObjectComponent.h"
namespace ld3d
{

	class SoundListener : public GameObjectComponent
	{
	public:
		SoundListener(GameObjectManagerPtr pManager):GameObjectComponent("SoundListener", pManager){}
		virtual ~SoundListener(void){}

	};

}
