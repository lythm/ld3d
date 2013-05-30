#pragma once


namespace ld3d
{
	struct VoxelChunk
	{
		uint32												key;
		uint8												data[64];
		VoxelChunk*											next;
	};
}
