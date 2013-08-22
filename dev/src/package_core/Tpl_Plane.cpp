#include "core_ext_pch.h"
#include "Tpl_Plane.h"

namespace ld3d
{
	Tpl_Plane::Tpl_Plane(GameObjectManagerPtr pManager, const std::string& name) : GameObjectTemplate(pManager, name, "Geometry")
	{
	}


	Tpl_Plane::~Tpl_Plane(void)
	{
	}
	GameObjectPtr Tpl_Plane::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject("Plane");
		
		MeshDataPtr pMD = std::dynamic_pointer_cast<MeshData>(m_pManager->CreateComponent("MeshData"));
		pMD->SetMeshAsset("_plane_");

		pObj->AddComponent(pMD);

		MeshRendererPtr pMR = std::dynamic_pointer_cast<MeshRenderer>(m_pManager->CreateComponent("MeshRenderer"));
		pObj->AddComponent(pMR);

		return pObj;
	}
	void Tpl_Plane::Release()
	{
	}
}
