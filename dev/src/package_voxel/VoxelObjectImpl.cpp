#include "voxel_pch.h"
#include "VoxelObjectImpl.h"

namespace ld3d
{
	VoxelObjectImpl::VoxelObjectImpl(GameObjectManagerPtr pManager) : VoxelObject(pManager)
	{
	}


	VoxelObjectImpl::~VoxelObjectImpl(void)
	{
	}
	const Version& VoxelObjectImpl::GetVersion() const
	{
		return g_packageVersion;
	}
	bool VoxelObjectImpl::OnAttach()
	{
		
		
		return true;
	}
	void VoxelObjectImpl::OnDetach()
	{
		ClearPropertySet();
	}
}
