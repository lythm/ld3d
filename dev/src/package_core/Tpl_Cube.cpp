#include "core_ext_pch.h"
#include "Tpl_Cube.h"

namespace ld3d
{
	Tpl_Cube::Tpl_Cube(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Geometry")
	{
	}
	 

	Tpl_Cube::~Tpl_Cube(void)
	{
	}
	GameObjectPtr Tpl_Cube::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"Cube");
		
		MeshDataPtr pMD = std::dynamic_pointer_cast<MeshData>(m_pManager->CreateComponent(L"MeshData"));
		if(false == pMD->SetMeshAsset(L"_cube_"))
		{
			return GameObjectPtr();
		}

		pObj->AddComponent(pMD);

		MeshRendererPtr pMR = std::dynamic_pointer_cast<MeshRenderer>(m_pManager->CreateComponent(L"MeshRenderer"));
		pObj->AddComponent(pMR);

		return pObj;
	}
	void Tpl_Cube::Release()
	{
	}
}
