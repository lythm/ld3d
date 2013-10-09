#pragma once

namespace ld3d
{
	class LuaBehavior : public GameObjectComponent
	{
	public:
		LuaBehavior(GameObjectManagerPtr pManager) : GameObjectComponent("LuaBehavior", pManager){}
		virtual ~LuaBehavior(void){}

	};


}