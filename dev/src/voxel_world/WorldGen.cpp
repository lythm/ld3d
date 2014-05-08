#include "voxel_world_pch.h"
#include "voxel_world/WorldGen.h"


namespace ld3d
{
	namespace voxel
	{

		WorldGen::WorldGen(void)
		{
		}

		WorldGen::~WorldGen(void)
		{
		}
		bool WorldGen::GenAll()
		{
			return true;
		}
		bool WorldGen::GenChunk(const Coord& c)
		{
			return true;
		}
		bool WorldGen::GenRegion(const Coord& c, uint32 dx, uint32 dy, uint32 dz)
		{
			return true;
		}
	}
}
