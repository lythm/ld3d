#include "core_ext_pch.h"
#include "Tpl_Camera.h"
//#include "core/ext/CameraData.h"

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

	

		return pObj;
	}
	void Tpl_Camera::Release()
	{
	}
}