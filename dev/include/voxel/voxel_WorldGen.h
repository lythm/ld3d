#pragma once

#include "voxel/voxel_Coord.h"

namespace ld3d
{
	namespace voxel
	{
		class WorldGen : public std::enable_shared_from_this<WorldGen>
		{
		public:
			WorldGen(void);
			virtual ~WorldGen(void);

			bool												GenAll();
			bool												GenChunk(const Coord& c);
			bool												GenRegion(const Coord& c, uint32 dx, uint32 dy, uint32 dz); 

			bool												Initialize();
			void												Release();

			WorldPtr											GetWorld();
			void												SetWorld(WorldPtr pWorld);

			void												AddPass(WorldGenPassPtr pPass);
		private:
			std::vector<WorldGenPassPtr>						m_passList;
			WorldPtr											m_pWorld;
		};
	}
}
