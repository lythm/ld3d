#include "core_ext_pch.h"
#include "Tpl_Cube.h"

namespace ld3d
{
	Tpl_Cube::Tpl_Cube(GameObjectManagerPtr pManager, const std::string& name) : GameObjectTemplate(pManager, name, "Geometry")
	{
	}
	 

	Tpl_Cube::~Tpl_Cube(void)
	{
	}
	GameObjectPtr Tpl_Cube::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject("Cube");
		
		MeshDataPtr pMD = std::dynamic_pointer_cast<MeshData>(m_pManager->CreateComponent("MeshData"));
		if(false == pMD->SetMeshAsset("_cube_"))
		{
			return GameObjectPtr();
		}

		pObj->AddComponent(pMD);

		MeshRendererPtr pMR = std::dynamic_pointer_cast<MeshRenderer>(m_pManager->CreateComponent("MeshRenderer"));
		pObj->AddComponent(pMR);

		return pObj;
	}
	void Tpl_Cube::Release()
	{
	}
}
