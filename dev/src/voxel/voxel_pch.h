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

	}
}