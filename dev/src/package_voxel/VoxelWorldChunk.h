#pragma once

namespace ld3d
{
	struct VoxelVertex
	{
		math::Vector3										pos;
		math::Vector3										normal;
		uint32												clr;
	};
	struct VoxelWorldChunk
	{
	public:
		uint32												key;
		uint8												data[VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE];
		VoxelWorldChunk*									map_next;
		VoxelWorldChunk*									dirty_list_next;
		VoxelWorldChunk*									render_list_next;
		VoxelVertex*										vertex_buffer;
		int													vertex_count;
		bool												in_dirty_list;
		bool												in_oct_tree;
		uint32												voxel_count;

		math::Vector3										chunk_coord()
		{
			uint32 c_x = (key >> 16) & 0x000000ff;
			uint32 c_y = (key >> 8) & 0x000000ff;
			uint32 c_z = key & 0x000000ff;

			float x = float(c_x * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_BLOCK_SIZE);
			float y = float(c_y * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_BLOCK_SIZE);
			float z = float(c_z * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_BLOCK_SIZE);

			return math::Vector3(x, y, z);
		}
	};
}
