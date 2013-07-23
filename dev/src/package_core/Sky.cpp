#include "core_ext_pch.h"
#include "..\..\include\core\ext\Sky.h"

namespace ld3d
{
	Sky::Sky(GameObjectManagerPtr pManager) : GameObjectComponent(L"Sky", pManager)
	{
		SetVersion(g_packageVersion);
	}


	Sky::~Sky(void)
	{
	}
	
	bool Sky::OnAttach()
	{
		PropertyManagerPtr pPM = std::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"Sky");
		{
			

		}
		pPM->End();

		return true;
	}
	void Sky::OnDetach()
	{

	}
}
