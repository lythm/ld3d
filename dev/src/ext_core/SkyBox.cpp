#include "core_ext_pch.h"
#include "..\..\include\core\ext\SkyBox.h"


namespace ld3d
{
	SkyBox::SkyBox(GameObjectManagerPtr pManager) : GameObjectComponent(L"SkyBox", pManager)
	{
		SetVersion(g_packageVersion);
	}


	SkyBox::~SkyBox(void)
	{
	}
	void SkyBox::Update(float dt)
	{
	}
	
	bool SkyBox::OnAttach()
	{
	
		PropertyManagerPtr pPM = boost::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"SkyBox");
		{
		}
		pPM->End();

		return true;
	}
	void SkyBox::OnDetach()
	{
	}
}
