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

			bool											Apply(WorldGenPtr pGen);

		private:

		};


	}
}