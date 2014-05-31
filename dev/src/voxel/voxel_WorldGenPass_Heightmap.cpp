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
			PerlinNoise p(3, 1, 1, rand());

			const Bound& bound = pGen->GetWorld()->GetBound();
			
			uint32 ex, ey, ez;
			bound.GetExtent(ex, ey, ez);
			

			WorldPtr pWorld = pGen->GetWorld();

			uint8 chunk_data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
			
			memset(chunk_data, 0, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
			bool empty_chunk = true;
			for(int x = 0; x < CHUNK_SIZE; ++x)
			{
				for(int z = 0; z < CHUNK_SIZE; ++z)
				{
					Coord c = Coord(x, 0, z) + chunk_origin;

					double h = p.Get(double(c.x) / double(ex), double(c.z) / double(ez));
					c.y = (h * REGION_HEIGHT) / 2;

					c -= chunk_origin;

					if(c.y < 0 || c.y >= CHUNK_SIZE)
					{
						continue;
					}

					empty_chunk = false;

					uint32 index = Chunk::ToIndex(c);

					chunk_data[index] = 1;
				}

			}

			if(empty_chunk == true)
			{
				return true;
			}

			ChunkPtr pChunk = pGen->GetWorld()->GetChunkManager()->CreateChunk(ChunkKey(chunk_origin), chunk_data);

			return true;
		}
	}
}
