#include "voxel_pch.h"
#include "voxel/voxel_WorldViewPort.h"
#include "voxel/voxel_World.h"
#include "voxel_RegionManager.h"
#include "voxel/voxel_Region.h"
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
			UpdateRegionBuffer();
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

			for(auto r : m_regionCache)
			{
				m_pRegionManager->UnloadRegion(r);
			}
			m_regionCache.clear();
		}
		void WorldViewport::Update()
		{
			Coord center_coord = m_center / (REGION_SIZE);
			
			if(center_coord != m_centerRegionCoord)
			{
				UpdateRegionBuffer();
			}

			UpdateRegionCache();
		}
		void WorldViewport::UpdateRegionCache()
		{
			Coord center_coord = m_center / (REGION_SIZE);

			Coord min_coord = (m_center - m_size / 2) / (REGION_SIZE);
			Coord max_coord = (m_center + m_size / 2) / (REGION_SIZE);

			uint32 dx = max_coord.x - min_coord.x;
			uint32 dz = max_coord.z - min_coord.z;

			std::vector<std::list<RegionPtr>::iterator> erase_list;

			std::list<RegionPtr>::iterator it = m_regionCache.begin();

			uint32 cache_margin = 1;

			for(it; it != m_regionCache.end(); ++it)
			{

				Coord r_coord = (*it)->GetRegionCoord();
				
				if(r_coord.x < (min_coord.x - cache_margin) || r_coord.x > (min_coord.x + cache_margin))
				{
					erase_list.push_back(it);
					continue;
				}

				if(r_coord.z < (min_coord.z - cache_margin) || r_coord.z > (min_coord.z + cache_margin))
				{
					erase_list.push_back(it);
					continue;
				}
			}

			for(auto r : erase_list)
			{
				m_pRegionManager->UnloadRegion(*r);
				m_regionCache.erase(r);
			}

			erase_list.clear();
		}
		RegionPtr WorldViewport::FindInCache(const Coord& c)
		{
			std::list<RegionPtr>::iterator it = m_regionCache.begin();
			for(; it != m_regionCache.end(); ++it)
			{
				if((*it)->GetRegionCoord() == c)
				{
					break;
				}
			}

			if(it == m_regionCache.end())
			{
				return nullptr;
			}

			RegionPtr pRegion = *it;

			m_regionCache.erase(it);

			return pRegion;

		}
		void WorldViewport::AddToCache(RegionPtr pRegion)
		{
			m_regionCache.push_back(pRegion);
		}
		void WorldViewport::UpdateRegionBuffer()
		{
			m_centerRegionCoord = m_center / REGION_SIZE;
			
			Coord min_coord = (m_center - m_size / 2) / REGION_SIZE;
			Coord max_coord = (m_center + m_size / 2) / REGION_SIZE;

			uint32 dx = max_coord.x - min_coord.x;
			uint32 dz = max_coord.z - min_coord.z;

			uint32 region_count = (dx + 1) * (dz + 1);

			for(auto r : m_regionBuffer)
			{
				AddToCache(r);
			}

			if(m_regionBuffer.size() != region_count)
			{
				m_regionBuffer.resize(region_count);
			}

			for(size_t x = 0; x <= dx; ++x)
			{
				for(size_t z = 0; z <= dz; ++z)
				{
					Coord c(x, 0, z);
					c += min_coord;

					RegionPtr pRegion = FindInCache(c);
					if(pRegion == nullptr)
					{
						pRegion = m_pRegionManager->LoadRegion(c);
					}
					m_regionBuffer[x + z * (dx + 1)] = pRegion;
				}
			}
		}
		Coord WorldViewport::GetBaseCoord()
		{
			return m_pWorld->ToRegionOrigin(m_center);
		}
	}
}

