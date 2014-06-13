#pragma once

#include "voxel/voxel_Coord.h"

namespace ld3d
{
	namespace voxel
	{
		class RegionManager
		{
		public:
			RegionManager(void);
			virtual ~RegionManager(void);

			bool											Initialize(WorldPtr pWorld);
			void											Release();

			RegionPtr										LoadRegion(const Coord& c);
			RegionPtr										LoadRegionSync(const Coord& c);
			void											UnloadRegion(RegionPtr pRegion);
			void											UnloadRegionSync(RegionPtr pRegion);

			void											Update();

			RegionPtr										FindRegion(const Coord& c);

		private:
			
		private:
			WorldPtr										m_pWorld;
			
			std::list<RegionPtr>							m_regions;
			
			ChunkLoaderPtr									m_pChunkLoader;
		};
	}
}
