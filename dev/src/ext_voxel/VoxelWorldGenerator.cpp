#include "voxel_pch.h"
#include "VoxelWorldGenerator.h"
#include "ext_voxel\VoxelBlock.h"

namespace ld3d
{
	VoxelWorldGenerator::VoxelWorldGenerator(void)
	{
	}


	VoxelWorldGenerator::~VoxelWorldGenerator(void)
	{
	}
	std::vector<VoxelBlockPtr> VoxelWorldGenerator::Generate(Allocator* pAllocator, int w, int h)
	{
		std::vector<VoxelBlockPtr> blocks;
		blocks.resize(w * h);

		for(int i = 0; i < w * h; ++i)
		{
			VoxelBlockPtr pBlock = pAllocator->AllocObject<VoxelBlock>();
			blocks.push_back(pBlock);

		}
		return blocks;
	}
}
