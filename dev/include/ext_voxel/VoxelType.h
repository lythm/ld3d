#pragma once

namespace ld3d
{
	enum VOXEL_TYPE
	{
		VT_SOIL					= 0,
		VT_STONE				= 1,
		VT_IRON					= 2,
		VT_SILVER				= 3,
		VT_GOLD					= 4,
		VT_WATER				= 5,
		VT_GRASS				= 6,
		VT_BEACH				= 7,
		VT_TREE_LEAF			= 8,
		VT_TREE_TRUNK			= 9,


		VT_EMPTY				= 255,
	};

	struct VoxelFace
	{
		math::Vector3			verts[4];
		math::Vector3			normal;
		uint8					type;
	};

	enum 
	{
		VOXEL_WORLD_CHUNK_SIZE					= 16,
		VOXEL_WORLD_REGION_SIZE					= 256,
		VOXEL_WORLD_CHUNK_MAP_RATIO				= 8,
		VOXEL_WORLD_CHUNK_MAP_SIZE				= (VOXEL_WORLD_REGION_SIZE * VOXEL_WORLD_REGION_SIZE * VOXEL_WORLD_REGION_SIZE) / VOXEL_WORLD_CHUNK_MAP_RATIO,

		VOXEL_WORLD_BLOCK_SIZE					= 1,
	};


}