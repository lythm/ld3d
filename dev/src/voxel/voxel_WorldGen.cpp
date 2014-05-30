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
		
		bool WorldGen::GenChunk(const Coord& chunk_origin)
		{
			for(size_t i = 0; i < m_passList.size(); ++i)
			{
				m_passList[i]->ApplyChunk(shared_from_this(), chunk_origin);
			}

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
