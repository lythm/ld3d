#include "voxel_pch.h"
#include "VoxelWorldTemplate.h"
#include "VoxelWorldImpl2.h"
#include "VoxelWorldRendererImpl2.h"


namespace ld3d
{
	VoxelWorldTemplate::VoxelWorldTemplate(GameObjectManagerPtr pManager, const std::string& name) : GameObjectTemplate(pManager, name, "Voxel")
	{
		
	}
	
	VoxelWorldTemplate::~VoxelWorldTemplate(void)
	{
	}
	
	GameObjectPtr VoxelWorldTemplate::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject("VoxelWorld");

		VoxelWorldPtr pWorld = m_pManager->alloc_object<VoxelWorldImpl2>(m_pManager);

		pObj->AddComponent(pWorld);

	//	VoxelWorldGeneratorPtr pGen = m_pManager->alloc_object<VoxelWorldGeneratorImpl>(m_pManager);
	//	pObj->AddComponent(pGen);

		VoxelWorldRendererPtr pRenderer = m_pManager->alloc_object<VoxelWorldRendererImpl2>(m_pManager);
		pObj->AddComponent(pRenderer);

	//	GameObjectComponentPtr pCom = m_pManager->CreateComponent("VoxelWorldCollisionData");
//		pObj->AddComponent(pCom);

		return pObj;
	}
	void VoxelWorldTemplate::Release()
	{
	}
}

