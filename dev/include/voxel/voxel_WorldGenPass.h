#pragma once

#include "voxel/voxel_Coord.h"

namespace ld3d
{
	namespace voxel
	{
		class WorldGenPass
		{
		public:

			WorldGenPass(void){}

			virtual ~WorldGenPass(void){}

			virtual bool											ApplyChunk(WorldGenPtr pGen, const Coord& chunk_coord)										= 0;


		};


	}
}
