#include "voxel_world_pch.h"

#include "voxel_world/World.h"

namespace ld3d
{
	namespace voxel
	{
		World::World(void)
		{
		}


		World::~World(void)
		{
		}
		bool World::Initialize(WorldGenPtr pGen)
		{
			m_pGen = pGen;

			return true;
		}
		void World::Release()
		{
		}

	}
}
