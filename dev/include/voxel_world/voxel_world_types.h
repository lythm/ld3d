#pragma once

#include "platform/platform.h"

#include "math/math_all.h"

#include <memory>

namespace ld3d
{
	namespace voxel
	{

		const uint32 CHUNK_SIZE													= 16;
		const uint32 BLOCK_SIZE													= 1;


		class World;
		class WorldGen;
		class WorldGenPass;

		typedef std::shared_ptr<World>											WorldPtr;
		typedef std::shared_ptr<WorldGen>										WorldGenPtr;
		typedef std::shared_ptr<WorldGenPass>									WorldGenPassPtr;


	}		
}
