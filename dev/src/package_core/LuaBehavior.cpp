#include "core_ext_pch.h"
#include "core/ext/LuaBehavior.h"

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
		PropertyManagerPtr pPM = std::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent("PropertyManager"));

		pPM->Begin("LuaBehavior");
		{
			

		}
		pPM->End();

		return true;
	}
	void LuaBehavior::OnDetach()
	{
	}
}
