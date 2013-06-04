#pragma once

namespace ld3d
{
	struct VoxelWorldChunk
	{
	public:
		
		bool												in_dirty_list;
		uint32												key;
		uint8												data[VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE];
		VoxelWorldChunk*									next;
		VoxelWorldChunk*									dirty_list_next;

		std::vector<VoxelFace>								mesh;
	};
}
