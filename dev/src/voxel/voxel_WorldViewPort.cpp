#include "voxel_pch.h"
#include "voxel/voxel_WorldViewPort.h"

namespace ld3d
{
	namespace voxel
	{
		WorldViewport::WorldViewport(WorldPtr pWorld)
		{
			m_size = 0;
			m_pWorld = pWorld;
		}


		WorldViewport::~WorldViewport(void)
		{
		}
		bool WorldViewport::Inside(const Coord& coord) const
		{
			Coord min_coord = m_center - m_size;
			Coord max_coord = m_center + m_size;
			
			// 2d. axis y is ignored
			return coord.x >= min_coord.x && coord.x <= max_coord.x 
				&& coord.z >= min_coord.z && coord.z <= max_coord.z;
		}
		
		void WorldViewport::MoveTo(const Coord& c)
		{
			m_center = c;
		}
		void WorldViewport::SetSize(uint32 size)
		{
			m_size = size;
		}
		void WorldViewport::Close()
		{

		}
	}
}
