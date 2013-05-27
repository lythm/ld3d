#include "voxel_pch.h"
#include "VoxelWorldGenerator.h"
#include "ext_voxel\VoxelBlock.h"
#include "VoxelPool.h"

namespace ld3d
{
	VoxelWorldGenerator::VoxelWorldGenerator(void)
	{
	}


	VoxelWorldGenerator::~VoxelWorldGenerator(void)
	{
	}
	std::vector<Voxel*> VoxelWorldGenerator::Generate(VoxelPoolPtr pPool, int sx, int sy, int sz)
	{

		std::vector<Voxel*>	voxels;
		voxels.resize(sx * sy * sz);

		for(int i = 0; i < sx * sy * sz; ++i)
		{
			Voxel* pData = (Voxel*)pPool->Alloc();

			pData->pos = i;

			voxels.push_back(pData);
			

		}
		return voxels;
	}
}
