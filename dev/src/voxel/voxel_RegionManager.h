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
			void											UnloadRegion(RegionPtr pRegion);

			void											Update();

			RegionPtr										FindRegion(const Coord& c);

		private:
			bool											ProcessLoadingQueue();
			bool											ProcessUnloadingQueue();
		private:
			WorldPtr										m_pWorld;


			std::list<RegionPtr>							m_regions;
			std::list<RegionPtr>							m_loadingQueue;
			std::list<RegionPtr>							m_unloadingQueue;

		};


	}
}