#include "voxel_pch.h"
#include "..\..\include\ext_voxel\VoxelBlock.h"

namespace ld3d
{
	VoxelBlock::VoxelBlock(void)
	{
	}


	VoxelBlock::~VoxelBlock(void)
	{
	}
	const math::Vector3& VoxelBlock::Center()
	{
		return m_center;
	}
}