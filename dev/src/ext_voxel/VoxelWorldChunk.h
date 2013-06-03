#pragma once

namespace ld3d
{
	struct VoxelWorldChunk
	{
	public:
		
		uint32												key;
		uint8												data[VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE];
		VoxelWorldChunk*									next;
	};
}
