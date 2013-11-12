#pragma once

#include "core/ObjectPool.h"


namespace ld3d
{
	class VoxelWorldChunk;
	class VoxelPool
	{
	public:
		VoxelPool(void);
		virtual ~VoxelPool(void);

		bool																Initialize(int count);
		void																Release();

		VoxelWorldChunk*													Alloc();
		void																Free(VoxelWorldChunk* pVoxel);

	private:
		ObjectPool<VoxelWorldChunk>											m_pool;
	};
}
