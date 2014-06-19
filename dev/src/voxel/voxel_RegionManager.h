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

			RegionPtr										LoadRegion(const Coord& c, const std::function<void(RegionPtr, ChunkPtr)>& on_chunk_loaded = std::function<void(RegionPtr, ChunkPtr)>());
			RegionPtr										LoadRegionSync(const Coord& c, const std::function<void(RegionPtr, ChunkPtr)>& on_chunk_loaded = std::function<void(RegionPtr, ChunkPtr)>());
			void											UnloadRegion(RegionPtr pRegion);
			void											UnloadRegionSync(RegionPtr pRegion);

			void											Update();

			RegionPtr										FindRegionByRegionCoord(const Coord& c);

			void											AddChunk(ChunkPtr pChunk);
			void											FrustumCull(const math::ViewFrustum& vf, const std::function<void(const Coord&, ChunkMeshPtr)>& op);
		private:
			
		private:
			WorldPtr										m_pWorld;
			
			std::list<RegionPtr>							m_regions;

		};
	}
}
