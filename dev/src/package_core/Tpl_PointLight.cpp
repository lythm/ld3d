#include "core_ext_pch.h"
#include "Tpl_PointLight.h"



namespace ld3d
{
	Tpl_PointLight::Tpl_PointLight(GameObjectManagerPtr pManager, const std::string& name) : GameObjectTemplate(pManager, name, "Light")
	{
	}


	Tpl_PointLight::~Tpl_PointLight(void)
	{
	}
	GameObjectPtr Tpl_PointLight::CreateGameObject()
	{
		GameObjectComponentPtr pLight = m_pManager->CreateComponent("PointLight");
		if(pLight == nullptr)
		{
			return nullptr;
		}
		GameObjectPtr pObj = m_pManager->CreateGameObject("Point Light");

		pObj->AddComponent(pLight);

		return pObj;
	}
	void Tpl_PointLight::Release()
	{
	}
}
