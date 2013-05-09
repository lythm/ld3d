#include "core_ext_pch.h"
#include "Tpl_Cone.h"

namespace ld3d
{
	Tpl_Cone::Tpl_Cone(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Geometry")
	{
	}


	Tpl_Cone::~Tpl_Cone(void)
	{
	}
	GameObjectPtr Tpl_Cone::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"Cone");
		
		MeshDataPtr pMD = boost::dynamic_pointer_cast<MeshData>(m_pManager->CreateComponent(L"MeshData"));
		pMD->SetMeshAsset(L"_cone_");

		pObj->AddComponent(pMD);

		MeshRendererPtr pMR = boost::dynamic_pointer_cast<MeshRenderer>(m_pManager->CreateComponent(L"MeshRenderer"));
		pObj->AddComponent(pMR);

		return pObj;
	}
	void Tpl_Cone::Release()
	{
	}

}