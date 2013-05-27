#include "voxel_pch.h"
#include "VoxelPool.h"

namespace ld3d
{
	VoxelPool::VoxelPool(void)
	{
	}


	VoxelPool::~VoxelPool(void)
	{
	}
	bool VoxelPool::Initialize(int count)
	{
		return true;
	}
	void VoxelPool::Release()
	{
	}

	Voxel* VoxelPool::Alloc()
	{
		return new Voxel;
	}
	void VoxelPool::Free(Voxel* pVoxel)
	{
		delete pVoxel;
	}
}
