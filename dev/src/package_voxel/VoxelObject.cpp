#include "voxel_pch.h"
#include "ext_voxel/VoxelObject.h"

namespace ld3d
{
	VoxelObject::VoxelObject(GameObjectManagerPtr pManager) : GameObjectComponent("VoxelObject", pManager)
	{
	}


	VoxelObject::~VoxelObject(void)
	{
	}
	const Version& VoxelObject::GetVersion() const
	{
		return g_packageVersion;
	}
	bool VoxelObject::OnAttach()
	{
		
		
		return true;
	}
	void VoxelObject::OnDetach()
	{
		ClearPropertySet();
	}
}
