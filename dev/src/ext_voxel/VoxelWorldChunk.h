#pragma once

namespace ld3d
{
	struct VoxelWorldChunk
	{
	public:
		uint32												key;
		uint8												data[VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE];
		VoxelWorldChunk*									next;
		VoxelWorldChunk*									dirty_list_next;
		VoxelWorldChunk*									render_list_next;
		bool												in_dirty_list;
		bool												in_oct_tree;
		std::vector<VoxelFace>								mesh;
		math::Vector3*										vertex_buffer;
		int													vertex_count;

		math::Vector3										chunk_coord()
		{
			uint32 c_x = (key >> 16) & 0x000000ff;
			uint32 c_y = (key >> 8) & 0x000000ff;
			uint32 c_z = key & 0x000000ff;

			float x = c_x * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_BLOCK_SIZE;
			float y = c_y * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_BLOCK_SIZE;
			float z = c_z * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_BLOCK_SIZE;

			return math::Vector3(x, y, z);
		}


	};
}
