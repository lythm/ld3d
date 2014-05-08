#pragma once

namespace ld3d
{
	namespace voxel
	{
		class WorldGenPass
		{
		public:

			WorldGenPass(void){}

			virtual ~WorldGenPass(void){}

			virtual bool											Apply(WorldPtr pWorld)										= 0;


		};


	}
}
