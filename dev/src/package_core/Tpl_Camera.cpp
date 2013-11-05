#include "core_ext_pch.h"
#include "Tpl_Camera.h"


#include "Impl_CameraData.h"

#include "Impl_CameraController_Orbit.h"
#include "Impl_CameraController_FirstPerson.h"

namespace ld3d
{
	Tpl_Camera::Tpl_Camera(GameObjectManagerPtr pManager, const std::string& name) : GameObjectTemplate(pManager, name, "Camera")
	{
	}


	Tpl_Camera::~Tpl_Camera(void)
	{
	}
	GameObjectPtr Tpl_Camera::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject("Camera");
		
		CameraDataPtr pMD = std::dynamic_pointer_cast<Impl_CameraData>(m_pManager->CreateComponent("Camera"));
	
		pObj->AddComponent(pMD);

		GameObjectComponentPtr pController = std::dynamic_pointer_cast<Impl_CameraController_FirstPerson>(m_pManager->CreateComponent("CameraFirstPersonController"));
		//GameObjectComponentPtr pController = m_pManager->CreateComponent("CameraOrbitController");
		
		pObj->AddComponent(pController);

		GameObjectComponentPtr pSkyBox = m_pManager->CreateComponent("SkyBox");
		pObj->AddComponent(pSkyBox);

		return pObj;
	}
	void Tpl_Camera::Release()
	{
	}
}