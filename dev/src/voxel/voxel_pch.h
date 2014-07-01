#pragma once

#include <unordered_map>

#include <boost/pool/pool.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/thread.hpp>

#include <boost/chrono.hpp>
#include <boost/circular_buffer.hpp>

#include "utils/utils_all.h"


#include "voxel/voxel_types.h"



namespace ld3d
{
	namespace voxel
	{
		Allocator*						allocator();
		Logger&							logger();

		PoolManagerPtr					pool_manager();
	}
}