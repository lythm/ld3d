#include "voxel_pch.h"
#include "VoxelWorldTemplate.h"
#include "VoxelWorldImpl.h"
#include "VoxelWorldRendererImpl.h"


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

		VoxelWorldPtr pWorld = m_pManager->alloc_object<VoxelWorldImpl>(m_pManager);

		pObj->AddComponent(pWorld);

		VoxelWorldRendererPtr pRenderer = m_pManager->alloc_object<VoxelWorldRendererImpl>(m_pManager);
		pObj->AddComponent(pRenderer);

		return pObj;
	}
	void VoxelWorldTemplate::Release()
	{
	}
}

