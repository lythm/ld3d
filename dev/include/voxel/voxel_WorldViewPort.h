#pragma once

#include "voxel/voxel_Coord.h"

namespace ld3d
{
	namespace voxel
	{
		class WorldViewport : public std::enable_shared_from_this<WorldViewport>
		{
		public:
			WorldViewport(WorldPtr pWorld);
			virtual ~WorldViewport(void);


			void														MoveTo(const Coord& c);

			bool														Inside(const Coord& coord) const;

			void														SetSize(uint32 size);

			void														Close();
		private:

			WorldPtr													m_pWorld;

			uint32														m_size;
			Coord														m_center;

			std::vector<RegionPtr>										m_regionBuffer;
		};
	}
}

