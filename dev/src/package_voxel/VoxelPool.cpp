#include "voxel_pch.h"
#include "VoxelPool.h"

#include "VoxelWorldChunk.h"

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
		m_pool.CreatePool(count);

		return true;
	}
	void VoxelPool::Release()
	{
		m_pool.DestroyPool();
	}

	VoxelWorldChunk* VoxelPool::Alloc()
	{
		VoxelWorldChunk* pVoxel = m_pool.Alloc();

		//Voxel* pVoxel = new Voxel;
		
		return pVoxel;
	}
	void VoxelPool::Free(VoxelWorldChunk* pVoxel)
	{
		m_pool.Free(pVoxel);

		//delete pVoxel;
	}
}
