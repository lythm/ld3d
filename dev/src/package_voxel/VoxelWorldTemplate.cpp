#include "voxel_pch.h"
#include "VoxelWorldTemplate.h"
#include "packages/voxel/VoxelWorld.h"
#include "packages/voxel/VoxelWorldRenderer.h"
#include "packages/voxel/VoxelWorldGenerator.h"

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

		VoxelWorldPtr pWorld = m_pManager->alloc_object<VoxelWorld>(m_pManager);

		pObj->AddComponent(pWorld);

		VoxelWorldGeneratorPtr pGen = m_pManager->alloc_object<VoxelWorldGenerator>(m_pManager);
		pObj->AddComponent(pGen);

		VoxelWorldRendererPtr pRenderer = m_pManager->alloc_object<VoxelWorldRenderer>(m_pManager);
		pObj->AddComponent(pRenderer);

		return pObj;
	}
	void VoxelWorldTemplate::Release()
	{
	}
}

