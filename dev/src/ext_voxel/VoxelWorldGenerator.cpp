#include "voxel_pch.h"
#include "VoxelWorldGenerator.h"
#include "ext_voxel\VoxelBlock.h"
#include "VoxelPool.h"
#include "VoxelWorldDataSet.h"

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

		for(int x = 0; x < sx; ++x)
		{
			for(int z = 0; z < sz; ++z)
			{
				pDataSet->AddVoxel(VT_STONE, x, 0, z);
			}
		}
		
		return pDataSet;
	}
}
