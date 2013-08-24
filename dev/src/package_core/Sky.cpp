#include "core_ext_pch.h"
#include "core/ext/Sky.h"

namespace ld3d
{
	Sky::Sky(GameObjectManagerPtr pManager) : GameObjectComponent("Sky", pManager)
	{
		SetVersion(g_packageVersion);
	}


	Sky::~Sky(void)
	{
	}
	
	bool Sky::OnAttach()
	{
		PropertyManagerPtr pPM = std::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent("PropertyManager"));

		pPM->Begin("Sky");
		{
			

		}
		pPM->End();

		return true;
	}
	void Sky::OnDetach()
	{

	}
}