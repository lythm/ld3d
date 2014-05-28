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
		bool WorldGenPass_Heightmap::Apply(WorldGenPtr pGen)
		{
			const Bound& bound = pGen->GetWorld()->GetBound();
			WorldPtr pWorld = pGen->GetWorld();

			for(int x = 0; x < 100; ++x)
			{
				for(int z = 0; z < 100; ++z)
				{
					pWorld->AddBlock(Coord(x, 0, z), 1);
				}
			}

			return true;
		}
	}
}
