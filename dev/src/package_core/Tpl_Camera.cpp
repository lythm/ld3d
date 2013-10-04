#include "core_ext_pch.h"
#include "Tpl_Camera.h"
#include "packages/core/CameraData.h"

#include "packages/core/CameraController_Orbit.h"

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
		
		CameraDataPtr pMD = std::dynamic_pointer_cast<CameraData>(m_pManager->CreateComponent("Camera"));
	
		pObj->AddComponent(pMD);

		CameraController_OrbitPtr pController = std::dynamic_pointer_cast<CameraController_Orbit>(m_pManager->CreateComponent("CameraOrbitController"));

		pObj->AddComponent(pController);

		return pObj;
	}
	void Tpl_Camera::Release()
	{
	}
}