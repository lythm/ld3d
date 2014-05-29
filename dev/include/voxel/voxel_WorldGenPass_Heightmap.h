#pragma once

#include "voxel/voxel_WorldGenPass.h"
namespace ld3d
{
	namespace voxel
	{
		class WorldGenPass_Heightmap : public WorldGenPass
		{
		public:
			WorldGenPass_Heightmap(void);
			virtual ~WorldGenPass_Heightmap(void);

			bool											ApplyChunk(WorldGenPtr pGen, const Coord& chunk_coord);

		private:

		};


	}
}