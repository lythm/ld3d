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
		m_pool.CreatePool(count);

		return true;
	}
	void VoxelPool::Release()
	{
		m_pool.DestroyPool();

	}

	Voxel* VoxelPool::Alloc()
	{
		Voxel* pVoxel = m_pool.Alloc();

		//Voxel* pVoxel = new Voxel;
		
		return pVoxel;
	}
	void VoxelPool::Free(Voxel* pVoxel)
	{
		m_pool.Free(pVoxel);

		//delete pVoxel;
	}
}
