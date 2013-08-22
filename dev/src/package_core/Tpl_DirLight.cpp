#include "core_ext_pch.h"
#include "Tpl_DirLight.h"


namespace ld3d
{
	Tpl_DirLight::Tpl_DirLight(GameObjectManagerPtr pManager, const std::string& name) : GameObjectTemplate(pManager, name, "Light")
	{
	}


	Tpl_DirLight::~Tpl_DirLight(void)
	{
	}
	GameObjectPtr Tpl_DirLight::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject("Directional Light");

		GameObjectComponentPtr pLight = m_pManager->CreateComponent("DirectionalLight");
		pObj->AddComponent(pLight);

		return pObj;
	}
	void Tpl_DirLight::Release()
	{
	}
}
