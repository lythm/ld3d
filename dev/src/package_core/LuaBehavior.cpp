#include "core_ext_pch.h"
#include "packages/core/LuaBehavior.h"

namespace ld3d
{
	LuaBehavior::LuaBehavior(GameObjectManagerPtr pManager) : GameObjectComponent("LuaBehavior", pManager)
	{
		SetVersion(g_packageVersion);
	}


	LuaBehavior::~LuaBehavior(void)
	{
	}
	
	void LuaBehavior::Update(float dt)
	{
	}
	bool LuaBehavior::OnAttach()
	{
		
		return true;
	}
	void LuaBehavior::OnDetach()
	{
	}
}
