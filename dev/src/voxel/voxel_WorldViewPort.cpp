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

		}
	}
}
