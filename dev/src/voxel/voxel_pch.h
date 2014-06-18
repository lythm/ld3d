#pragma once

#include <unordered_map>

#include <boost/pool/pool.hpp>

#include "voxel/voxel_types.h"


#include "core/Allocator.h"




namespace ld3d
{
	namespace voxel
	{
		Allocator*						GetAllocator();

		struct pool_allocator
		{
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;

			static char * malloc(const size_type bytes)
			{ 
				return reinterpret_cast<char *>(GetAllocator()->Alloc(bytes)); 
			}
			static void free(char * const block)
			{ 
				GetAllocator()->Free(block);
			}
		};


		PoolManagerPtr					GetPoolManager();
	}
}