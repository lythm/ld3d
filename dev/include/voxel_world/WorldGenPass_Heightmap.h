#pragma once

#include "voxel_world/WorldGenPass.h"
namespace ld3d
{
	namespace voxel
	{
		class WorldGenPass_Heightmap : public WorldGenPass
		{
		public:
			WorldGenPass_Heightmap(void);
			virtual ~WorldGenPass_Heightmap(void);

			bool											Apply(WorldPtr pWorld);

		private:

		};


	}
}