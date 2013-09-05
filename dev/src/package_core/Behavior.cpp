#include "core_ext_pch.h"
#include "packages/core/Behavior.h"
#include "CorePackage.h"

namespace ld3d
{
	Behavior::Behavior(GameObjectManagerPtr pManager):GameObjectComponent("Behavior", pManager)
	{
		SetVersion(g_packageVersion);
	}

	Behavior::~Behavior(void)
	{
	}
	void Behavior::Update(float dt)
	{
	}
	bool Behavior::OnAttach()
	{
		return true;
	}
	void Behavior::OnDetach()
	{
	}
	
}
