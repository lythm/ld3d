#include "voxel_pch.h"
#include "voxel/voxel_WorldGenPass_Heightmap.h"
#include "voxel/voxel_World.h"
#include "voxel/voxel_WorldGen.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_ChunkManager.h"

namespace ld3d
{
	namespace voxel
	{
		WorldGenPass_Heightmap::WorldGenPass_Heightmap(void)
		{
		}


		WorldGenPass_Heightmap::~WorldGenPass_Heightmap(void)
		{
		}
		bool WorldGenPass_Heightmap::ApplyChunk(WorldGenPtr pGen, const Coord& chunk_origin)
		{
			
			return true;
		}
	}
}
