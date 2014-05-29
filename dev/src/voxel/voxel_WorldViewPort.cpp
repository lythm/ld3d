#include "voxel_pch.h"
#include "voxel/voxel_WorldViewPort.h"
#include "voxel/voxel_World.h"
#include "voxel_RegionManager.h"

namespace ld3d
{
	namespace voxel
	{
		WorldViewport::WorldViewport()
		{
			m_size = 0;
		}


		WorldViewport::~WorldViewport(void)
		{
		}
		bool WorldViewport::Inside(const Coord& coord) const
		{
			Coord min_coord = m_center - m_size / 2;
			Coord max_coord = m_center + m_size / 2;
			
			// 2d. axis y is ignored
			return coord.x >= min_coord.x && coord.x <= max_coord.x 
				&& coord.z >= min_coord.z && coord.z <= max_coord.z;
		}
		
		void WorldViewport::MoveTo(const Coord& c)
		{
			m_center = c;
		}
		
		bool WorldViewport::Open(WorldPtr pWorld, const Coord& center, uint32 size)
		{
			m_pWorld = pWorld;
			m_center = center;
			m_size = size;
			m_pRegionManager = pWorld->GetRegionManager();

			if(InitRegionBuffer() == false)
			{
				return false;
			}

			return true;
		}
		void WorldViewport::Close()
		{

			ReleaseRegionBuffer();

			m_pWorld.reset();
			m_center = Coord();
			m_size = 0;
			m_pRegionManager.reset();
		}
		bool WorldViewport::InitRegionBuffer()
		{
			uint32 region_count = m_size / (REGION_SIZE * CHUNK_SIZE * BLOCK_SIZE) + 1;

			m_regionBuffer.resize(region_count * region_count);

			m_baseRegionCoord = (m_center - m_size / 2);

			m_baseRegionCoord /= REGION_SIZE * CHUNK_SIZE * BLOCK_SIZE;


			for(size_t x = 0; x < region_count; ++x)
			{
				for(size_t z = 0; z < region_count; ++z)
				{

					Coord c;

					c.x = x;
					c.z = z;

					c += m_baseRegionCoord;
					m_regionBuffer[x + z * region_count] = m_pRegionManager->LoadRegion(c);
				}
			}
			return true;
		}
		void WorldViewport::ReleaseRegionBuffer()
		{
			for(auto r : m_regionBuffer)
			{
				if(r == nullptr)
				{
					continue;
				}
				m_pRegionManager->UnloadRegion(r);
			}
			m_regionBuffer.clear();
		}
		void WorldViewport::Update()
		{
			Coord base_coord = (m_center - m_size / 2);
			base_coord /= REGION_SIZE * CHUNK_SIZE * BLOCK_SIZE;

			if(base_coord != m_baseRegionCoord)
			{
				UpdateRegionBuffer();
			}
		}
		void WorldViewport::UpdateRegionBuffer()
		{

		}
	}
}
