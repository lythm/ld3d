#pragma once

#include "ext_voxel\Voxel.h"

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
		Voxel*																m_pPool;
	};
}
