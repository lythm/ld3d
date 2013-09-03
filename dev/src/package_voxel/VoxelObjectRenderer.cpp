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
		

		return true;
	}
	void VoxelObjectRenderer::OnDetach()
	{
		ClearPropertySet();
	}
}
