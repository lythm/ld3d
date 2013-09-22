#include "voxel_pch.h"
#include "VoxelObjectRendererImpl.h"

namespace ld3d
{
	VoxelObjectRendererImpl::VoxelObjectRendererImpl(GameObjectManagerPtr pManager) : VoxelObjectRenderer(pManager)
	{
		SetVersion(g_packageVersion);
	}


	VoxelObjectRendererImpl::~VoxelObjectRendererImpl(void)
	{
	}
	void VoxelObjectRendererImpl::Update(float dt)
	{
		
	}
			
	bool VoxelObjectRendererImpl::OnAttach()
	{
		

		return true;
	}
	void VoxelObjectRendererImpl::OnDetach()
	{
		ClearPropertySet();
	}
}
