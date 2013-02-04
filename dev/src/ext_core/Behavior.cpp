#include "core_ext_pch.h"
#include "..\..\include\core\ext\Behavior.h"
#include "CorePackage.h"

namespace ld3d
{
	Behavior::Behavior(GameObjectManagerPtr pManager):GameObjectComponent(L"Behavior", pManager)
	{
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
	const Version& Behavior::GetVersion() const
	{
		return g_packageVersion;
	}
}
