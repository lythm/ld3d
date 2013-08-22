#include "voxel_pch.h"
#include "ext_voxel/VoxelObjectRenderer.h"


namespace ld3d
{
	VoxelObjectRenderer::VoxelObjectRenderer(GameObjectManagerPtr pManager) : GameObjectComponent("VoxelObjectRenderer", pManager)
	{
		SetVersion(g_packageVersion);
	}


	VoxelObjectRenderer::~VoxelObjectRenderer(void)
	{
	}
	void VoxelObjectRenderer::Update(float dt)
	{
		
	}
			
	bool VoxelObjectRenderer::OnAttach()
	{
		PropertyManagerPtr pPM = std::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent("PropertyManager"));

		pPM->Begin("VoxelObjectRenderer");
		{
			
		}
		pPM->End();

		return true;
	}
	void VoxelObjectRenderer::OnDetach()
	{
		
	}
}
