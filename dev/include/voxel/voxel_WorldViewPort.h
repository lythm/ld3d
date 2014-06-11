#pragma once

#include "voxel/voxel_Coord.h"

namespace ld3d
{
	namespace voxel
	{
		class _DLL_CLASS WorldViewport : public std::enable_shared_from_this<WorldViewport>
		{
		public:
			WorldViewport();
			virtual ~WorldViewport(void);


			void														MoveTo(const Coord& c);

			bool														Inside(const Coord& coord) const;

			bool														Open(WorldPtr pWorld, const Coord& center, uint32 size);
			void														Close();

			void														Update();

			Coord														GetBaseCoord();

			void														SetDirtyChunkHandler(const std::function<void (ChunkPtr)>& handler);

			const std::list<ChunkPtr>									GetDirtyChunkList();
			void														ClearDirtyChunkList();
		private:
			void														UpdateRegionBuffer();
			bool														InitRegionBuffer();
			void														ReleaseRegionBuffer();

			RegionPtr													FindInCache(const Coord& c);
			void														AddToCache(RegionPtr pRegion);

			void														UpdateRegionCache();
		private:
			WorldPtr													m_pWorld;
			RegionManagerPtr											m_pRegionManager;
			uint32														m_size;
			Coord														m_center;
			Coord														m_centerRegionCoord;

			std::vector<RegionPtr>										m_regionBuffer;
			std::list<RegionPtr>										m_regionCache;
		};
	}
}

