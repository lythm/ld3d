#pragma once

#include "voxel/voxel_Coord.h"

namespace ld3d
{
	namespace voxel
	{
		class WorldViewPort
		{
		public:
			WorldViewPort(void);
			virtual ~WorldViewPort(void);

			bool														Open(WorldPtr pWorld, const Coord& center, uint32 size);
			void														Close();

			void														MoveTo(const Coord& c);

		private:

			WorldPtr													m_pWorld;

			uint32														m_size;
			Coord														m_center;
		};


	}
}
