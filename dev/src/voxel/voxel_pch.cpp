#include "voxel_pch.h"
#include "voxel_PoolManager.h"


namespace ld3d
{
	namespace voxel
	{
		static PoolManagerPtr				s_pPool;
		PoolManagerPtr pool_manager()
		{
			if(s_pPool == nullptr)
			{
				s_pPool = std::allocate_shared<PoolManager, std_allocator_adapter<PoolManager>>(allocator());
			}

			return s_pPool;
		}
	}
}