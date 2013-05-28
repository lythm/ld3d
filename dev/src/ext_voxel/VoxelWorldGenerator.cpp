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
		voxels.reserve(sx * sy * sz);


		for(int x = 0; x < sx; ++x)
		{
			for(int z = 0; z < sz; ++z)
			{

				Voxel* pData = (Voxel*)pPool->Alloc();

				if(pData == nullptr)
				{
					break;
				}
				pData->pos.x = x;
				pData->pos.y = 0;
				pData->pos.z = z;

				voxels.push_back(pData);
			}
		}
		return voxels;
	}
}
