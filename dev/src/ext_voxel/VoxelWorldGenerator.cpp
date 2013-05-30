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
	VoxelWorldDataSetPtr VoxelWorldGenerator::Generate(VoxelPoolPtr pPool, int sx, int sy, int sz)
	{
		VoxelWorldDataSetPtr pDataSet = VoxelWorldDataSetPtr(new VoxelWorldDataSet);
		
		
		return pDataSet;
	}
}
