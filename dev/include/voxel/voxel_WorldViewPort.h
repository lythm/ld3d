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

			bool														Open(WorldPtr pWorld, const Coord& center, uint32 size, ChunkMeshizerPtr pMeshizer);
			void														Close();

			void														Update();

			Coord														GetBaseCoord();

			void														SetDirtyChunkHandler(const std::function<void (const Coord&, ChunkPtr)>& handler);

			const std::list<ChunkPtr>									GetDirtyChunkList();
			void														ClearDirtyChunkList();

			void														SetRegionLoadedHandler(const std::function<void (RegionPtr)>& handler);
			void														SetRegionUnloadedHandler(const std::function<void (RegionPtr)>& handler);

			void														SetViewportSize(uint32 size);

			void														FrustumCull(const math::ViewFrustum& vf);

			
		private:
			void														UpdateRegionBuffer(bool sync);
			bool														InitRegionBuffer();
			void														ReleaseRegionBuffer();

			RegionPtr													FindInBuffer(const Coord& c);
			RegionPtr													FindInCache(const Coord& c);
			RegionPtr													GetFromCache(const Coord& c);
			void														AddToCache(RegionPtr pRegion);

			void														UpdateRegionCache();

			void														_on_chunk_loaded(RegionPtr pRegion, ChunkPtr pChunk);
			void														_on_dirty_chunk(ChunkPtr pChunk);
		private:
			WorldPtr													m_pWorld;
			RegionManagerPtr											m_pRegionManager;
			uint32														m_size;
			Coord														m_center;
			Coord														m_centerRegionCoord;

			std::vector<RegionPtr>										m_regionBuffer;
			std::list<RegionPtr>										m_regionCache;

			std::function<void (const Coord&, ChunkPtr)>				handler_dirty_chunk;

			std::function<void (RegionPtr)>								handler_region_loaded;
			std::function<void (RegionPtr)>								handler_region_unloaded;

			ChunkMeshizerPtr											m_pMeshizer;
		};
	}
}

