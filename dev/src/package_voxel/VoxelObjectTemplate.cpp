#include "voxel_pch.h"
#include "VoxelObjectTemplate.h"



namespace ld3d
{
	VoxelObjectTemplate::VoxelObjectTemplate(GameObjectManagerPtr pManager, const std::string& name) : GameObjectTemplate(pManager, name, "Voxel")
	{
		
	}
	
	VoxelObjectTemplate::~VoxelObjectTemplate(void)
	{
	}
	
	GameObjectPtr VoxelObjectTemplate::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject("VoxelObject");

		GameObjectComponentPtr pCom = m_pManager->CreateComponent("VoxelObject");

		pObj->AddComponent(pCom);

		pCom = m_pManager->CreateComponent("VoxelObjectRenderer");
		pObj->AddComponent(pCom);

		return pObj;
	}
	void VoxelObjectTemplate::Release()
	{
	}
}

