#pragma once

#include <unordered_map>

#include <boost/pool/pool.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/thread.hpp>

#include <boost/chrono.hpp>

#include "utils/utils_all.h"


#include "voxel/voxel_types.h"



namespace ld3d
{
	namespace voxel
	{
		Allocator*						allocator();
		Logger&							logger();

		struct pool_allocator
		{
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;

			static char * malloc(const size_type bytes)
			{ 
				return reinterpret_cast<char *>(allocator()->Alloc(bytes)); 
			}
			static void free(char * const block)
			{ 
				allocator()->Free(block);
			}
		};


		PoolManagerPtr					pool_manager();
	}
}