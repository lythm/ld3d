#include "core_ext_pch.h"
#include "Tpl_Cone.h"
#include "core/ext/MeshData.h"
#include "core/ext/MeshRenderer.h"
namespace ld3d
{
	Tpl_Cone::Tpl_Cone(GameObjectManagerPtr pManager, const std::string& name) : GameObjectTemplate(pManager, name, "Geometry")
	{
	}


	Tpl_Cone::~Tpl_Cone(void)
	{
	}
	GameObjectPtr Tpl_Cone::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject("Cone");
		
		MeshDataPtr pMD = std::dynamic_pointer_cast<MeshData>(m_pManager->CreateComponent("MeshData"));
		pMD->SetMeshAsset("_cone_");

		pObj->AddComponent(pMD);

		MeshRendererPtr pMR = std::dynamic_pointer_cast<MeshRenderer>(m_pManager->CreateComponent("MeshRenderer"));
		pObj->AddComponent(pMR);

		return pObj;
	}
	void Tpl_Cone::Release()
	{
	}

}