#pragma once

#include "ext_voxel\Voxel.h"
#include "core\ObjectPool.h"


namespace ld3d
{
	struct Voxel;
	class VoxelPool
	{
	public:
		VoxelPool(void);
		virtual ~VoxelPool(void);

		bool																Initialize(int count);
		void																Release();

		Voxel*																Alloc();
		void																Free(Voxel* pVoxel);

	private:
		ObjectPool<Voxel>													m_pool;
	};
}
