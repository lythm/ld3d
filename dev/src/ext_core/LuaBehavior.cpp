#include "core_ext_pch.h"
#include "..\..\include\core\ext\LuaBehavior.h"

namespace ld3d
{
	LuaBehavior::LuaBehavior(GameObjectManagerPtr pManager) : GameObjectComponent(L"LuaBehavior", pManager)
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
		PropertyManagerPtr pPM = std::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"LuaBehavior");
		{
			

		}
		pPM->End();

		return true;
	}
	void LuaBehavior::OnDetach()
	{
	}
}
