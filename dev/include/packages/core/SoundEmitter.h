#pragma once

#include "core/GameObjectComponent.h"
namespace ld3d
{

	class SoundEmitter : public GameObjectComponent
	{
	public:
		SoundEmitter(GameObjectManagerPtr pManager) : GameObjectComponent("SoundEmitter", pManager){}
		virtual ~SoundEmitter(void){}

		
		virtual const bool&									GetStreamed()										= 0;
		virtual void										SetStreamed(const bool& streamed)					= 0;
	};

}