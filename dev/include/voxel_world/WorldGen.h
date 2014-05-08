#pragma once

#include "voxel_world/Coord.h"

namespace ld3d
{
	namespace voxel
	{
		class WorldGen
		{
		public:
			WorldGen(void);
			virtual ~WorldGen(void);

			bool												GenAll();
			bool												GenChunk(const Coord& c);
			bool												GenRegion(const Coord& c, uint32 dx, uint32 dy, uint32 dz); 
		};


	}
}
