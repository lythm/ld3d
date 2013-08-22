#include "core_ext_pch.h"
#include "Tpl_SpotLight.h"



namespace ld3d
{
	Tpl_SpotLight::Tpl_SpotLight(GameObjectManagerPtr pManager, const std::string& name) : GameObjectTemplate(pManager, name, "Light")
	{
	}


	Tpl_SpotLight::~Tpl_SpotLight(void)
	{
	}
	GameObjectPtr Tpl_SpotLight::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject("Spot Light");

		GameObjectComponentPtr pLight = m_pManager->CreateComponent("SpotLight");
		pObj->AddComponent(pLight);

		return pObj;
	}
	void Tpl_SpotLight::Release()
	{
	}
}
