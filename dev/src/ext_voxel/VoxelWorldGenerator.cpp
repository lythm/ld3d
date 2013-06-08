#include "voxel_pch.h"
#include "VoxelWorldGenerator.h"
#include "VoxelWorldChunk.h"
#include "VoxelPool.h"
#include "VoxelWorldDataSet.h"

#include <boost\random.hpp>

namespace ld3d
{
	VoxelWorldGenerator::VoxelWorldGenerator(void)
	{
	}


	VoxelWorldGenerator::~VoxelWorldGenerator(void)
	{
	}
	VoxelWorldDataSetPtr VoxelWorldGenerator::Generate(int sx, int sy, int sz)
	{
		VoxelWorldDataSetPtr pDataSet = VoxelWorldDataSetPtr(new VoxelWorldDataSet);

		pDataSet->Initialize();

		/*for(int y = 0; y < sy; ++y)
		{
			for(int x = 0; x < sx; ++x)
			{
				for(int z = 0; z < sz; ++z)
				{
					pDataSet->AddVoxel(VT_STONE, x, y, z);
				}
			}
		}*/


		/*for(int x = 0; x < sx; ++x)
		{
			for(int z = 0; z < sz; ++z)
			{
				int yy = sinf(x / 10.0f ) * sy  + (sinf(z / 10.0f)) * sy + 1;
				for(int y = 0; y < yy; ++y)
				{
					pDataSet->AddVoxel(VT_STONE, x, y, z);
				}
			}
		}*/

		boost::random::mt19937 rng;         // produces randomness out of thin air
                                    // see pseudo-random number generators
		
                                    // distribution that maps to 1..6
                                    // see random number distributions
		
		
		for(int x = 0; x < sx; ++x)
		{
			for(int z = 0; z < sz; ++z)
			{
				for(int y = 0; y < sy; ++y)
				{
					boost::random::uniform_int_distribution<> gen(0,y);

					int ret = gen(rng);
					if(ret == 0)
					{
						pDataSet->AddVoxel(VT_STONE, x, y, z);
					}
				}
			}
		}
		

		return pDataSet;
	}
}
