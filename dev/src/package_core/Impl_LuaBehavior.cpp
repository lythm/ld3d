#include "core_ext_pch.h"
#include "Impl_LuaBehavior.h"


namespace ld3d
{
	Impl_LuaBehavior::Impl_LuaBehavior(GameObjectManagerPtr pManager) : LuaBehavior(pManager)
	{
		SetVersion(g_packageVersion);
	}


	Impl_LuaBehavior::~Impl_LuaBehavior(void)
	{
	}
	
	void Impl_LuaBehavior::Update(float dt)
	{
	}
	bool Impl_LuaBehavior::OnAttach()
	{
		
		return true;
	}
	void Impl_LuaBehavior::OnDetach()
	{
	}
}
