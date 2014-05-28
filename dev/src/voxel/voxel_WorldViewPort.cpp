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
			return true;
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
