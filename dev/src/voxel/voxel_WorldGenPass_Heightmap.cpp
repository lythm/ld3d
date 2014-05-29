#include "voxel_pch.h"
#include "voxel/voxel_WorldGenPass_Heightmap.h"
#include "voxel/voxel_World.h"
#include "voxel/voxel_WorldGen.h"

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
		bool WorldGenPass_Heightmap::ApplyChunk(WorldGenPtr pGen, const Coord& chunk_coord)
		{
			PerlinNoise p(2, 1, 1, rand());

			const Bound& bound = pGen->GetWorld()->GetBound();
			WorldPtr pWorld = pGen->GetWorld();

			for(int x = 0; x < CHUNK_SIZE; ++x)
			{
				for(int z = 0; z < CHUNK_SIZE; ++z)
				{
					Coord c = Coord(x, 0, z) + chunk_coord;

					float h = p.Get(c.x, c.z);
					c.y = h * 2000 - 1000;

					pWorld->AddBlock(c, 1);
				}
			}
			return true;
		}
	}
}
