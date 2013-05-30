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
		VT_TREE_LEAF			= 7,
		VT_TREE_TRUNK			= 8,


		VT_EMPTY				= -1,
	};

	struct VoxelFace
	{
		math::Vector3			verts[4];
		uint32					index[3];
		uint32					clr;
	};
}
