#include "core_ext_pch.h"
#include "Impl_Behavior.h"


namespace ld3d
{
	Impl_Behavior::Impl_Behavior(GameObjectManagerPtr pManager):Behavior(pManager)
	{
		SetVersion(g_packageVersion);
	}

	Impl_Behavior::~Impl_Behavior(void)
	{
	}
	void Impl_Behavior::Update(float dt)
	{
	}
	bool Impl_Behavior::OnAttach()
	{
		return true;
	}
	void Impl_Behavior::OnDetach()
	{
	}
	
}
