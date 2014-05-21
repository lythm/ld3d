#pragma once


#include <vector>

#include "platform/platform.h"

#include "math/math_all.h"

#include "utils/utils_all.h"

#include <memory>


namespace ld3d
{
	namespace voxel
	{
		const uint8  VT_EMPTY													= 0;

		const uint32 REGION_HEIGHT												= 256;
		const uint32 REGION_SIZE												= 32;
		const uint32 CHUNK_SIZE													= 16;
		const uint32 BLOCK_SIZE													= 1;

		class World;
		class WorldGen;
		class WorldGenPass;
		class Chunk;
		class ChunkManager;
		class Region;


		typedef std::shared_ptr<Region>											RegionPtr;
		typedef std::shared_ptr<World>											WorldPtr;
		typedef std::shared_ptr<WorldGen>										WorldGenPtr;
		typedef std::shared_ptr<WorldGenPass>									WorldGenPassPtr;
		typedef std::shared_ptr<Chunk>											ChunkPtr;
		typedef std::shared_ptr<ChunkManager>									ChunkManagerPtr;


	}		
}
