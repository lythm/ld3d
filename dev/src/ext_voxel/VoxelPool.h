#pragma once

#include "ext_voxel\Voxel.h"
#include "core\ObjectPool.h"


namespace ld3d
{
	struct VoxelChunk;
	class VoxelPool
	{
	public:
		VoxelPool(void);
		virtual ~VoxelPool(void);

		bool																Initialize(int count);
		void																Release();

		VoxelChunk*															Alloc();
		void																Free(VoxelChunk* pVoxel);

	private:
		ObjectPool<VoxelChunk>												m_pool;
	};
}
