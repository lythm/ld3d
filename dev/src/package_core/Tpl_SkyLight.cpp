#include "core_ext_pch.h"
#include "Tpl_SkyLight.h"


namespace ld3d
{
	Tpl_SkyLight::Tpl_SkyLight(GameObjectManagerPtr pManager, const std::string& name) : GameObjectTemplate(pManager, name, "Light")
	{
	}


	Tpl_SkyLight::~Tpl_SkyLight(void)
	{
	}
	GameObjectPtr Tpl_SkyLight::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject("Sky Light");

		GameObjectComponentPtr pLight = m_pManager->CreateComponent("SkyLight");
		
		if(false == pObj->AddComponent(pLight))
		{
			pObj->Clear();
			pObj.reset();
			return GameObjectPtr();
		}

		return pObj;
	}
	void Tpl_SkyLight::Release()
	{
	}
}
