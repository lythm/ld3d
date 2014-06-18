#include "voxel_pch.h"
#include "voxel_PoolManager.h"


namespace ld3d
{
	namespace voxel
	{
		static PoolManagerPtr				s_pPool;
		PoolManagerPtr GetPoolManager()
		{
			if(s_pPool == nullptr)
			{
				s_pPool = std::allocate_shared<PoolManager, std_allocator_adapter<PoolManager>>(GetAllocator());
			}

			return s_pPool;
		}
	}
}