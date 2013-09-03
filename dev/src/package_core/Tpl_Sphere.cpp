#include "core_ext_pch.h"
#include "Tpl_Sphere.h"
#include "core/ext/MeshData.h"
#include "core/ext/MeshRenderer.h"
namespace ld3d
{
	Tpl_Sphere::Tpl_Sphere(GameObjectManagerPtr pManager, const std::string& name) : GameObjectTemplate(pManager, name, "Geometry")
	{
	}


	Tpl_Sphere::~Tpl_Sphere(void)
	{
	}
	void Tpl_Sphere::Release()
	{
	}
	GameObjectPtr Tpl_Sphere::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject("Sphere");
		
		MeshDataPtr pMD = std::dynamic_pointer_cast<MeshData>(m_pManager->CreateComponent("MeshData"));
		pMD->SetMeshAsset("_sphere_");

		pObj->AddComponent(pMD);

		MeshRendererPtr pMR = std::dynamic_pointer_cast<MeshRenderer>(m_pManager->CreateComponent("MeshRenderer"));
		pObj->AddComponent(pMR);

		return pObj;
	}
}