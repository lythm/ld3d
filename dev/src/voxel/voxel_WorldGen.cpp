#include "voxel_pch.h"
#include "voxel/voxel_WorldGen.h"
#include "voxel/voxel_WorldGenPass.h"


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
			for(size_t i = 0; i < m_passList.size(); ++i)
			{
				m_passList[i]->Apply(shared_from_this());
			}
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

		bool WorldGen::Initialize()
		{
			return true;
		}
		void WorldGen::Release()
		{
		}
		WorldPtr WorldGen::GetWorld()
		{
			return m_pWorld;
		}
		void WorldGen::SetWorld(WorldPtr pWorld)
		{
			m_pWorld = pWorld;
		}
		void WorldGen::AddPass(WorldGenPassPtr pPass)
		{
			m_passList.push_back(pPass);
		}
	}
}
