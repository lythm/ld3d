#pragma once

#include "voxel/voxel_Coord.h"

#include "voxel/voxel_ChunkKey.h"

namespace ld3d
{
	namespace voxel
	{
		class _DLL_CLASS World : public std::enable_shared_from_this<World>
		{
		public:
			World(void);
			virtual ~World(void);

			bool											Initialize(WorldGenPtr pGen);

			void											Release();

			bool											AddBlock(const Coord& c, uint8 type);
			bool											ReplaceBlock(const Coord& c, uint8 type);
			bool											RemoveBlock(const Coord& c);
			bool											IsEmpty(const Coord& c);
			uint8											GetBlock(const Coord& c);
			void											UpdateBlock(const Coord& c);


			bool											Inside(const Coord& c) const;

			const math::AABBox&								GetBound() const;		

			const math::Matrix44&							GetWorldTransform() const;

			void											SetOriginChunk(const Coord& c);
			Coord											ToChunkCoord(const Coord& c);
			Coord											ToRegionCoord(const Coord& c);
			ChunkPtr										FindChunk(const ChunkKey& key);

			const std::list<ChunkPtr>&						GetDirtyChunks() const;
			void											ClearDirtyChunks();

			void											Update(float dt);
		private:
			
			void											LoadPendingRegion();

			void											AddPendingRegion(RegionPtr pRegion);
		private:
			WorldGenPtr										m_pGen;

			ChunkManagerPtr									m_pChunkManager;
			math::AABBox									m_worldBound;

			math::Matrix44									m_worldTransfom;
			Coord											m_origin;


			uint32											m_regionPoolSize;
			uint32											m_regionCacheSize;

			std::vector<RegionPtr>							m_regionPool;
			std::vector<RegionPtr>							m_regionCache;



			std::list<RegionPtr>							m_pendingRengionList;
			
		};

	}
}


