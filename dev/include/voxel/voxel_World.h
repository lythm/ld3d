#pragma once

#include "voxel/voxel_Coord.h"
#include "voxel/voxel_Bound.h"

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

			const Bound&									GetBound() const;		

			ChunkPtr										FindChunk(const ChunkKey& key);

			const std::list<ChunkPtr>&						GetDirtyChunks() const;
			void											ClearDirtyChunks();

			void											Update(float dt);

			ChunkManagerPtr									GetChunkManager();
			RegionManagerPtr								GetRegionManager();

			Coord											ToRegionOrigin(const Coord& c) const;
			Coord											ToRegionCoord(const Coord& c) const;

			Coord											ToChunkOrigin(const Coord& c) const;
			Coord											ToChunkCoord(const Coord& c) const;

			WorldGenPtr										GetWorldGen();
		private:
		
			
		private:
			WorldGenPtr										m_pGen;
			Bound											m_worldBound;

			RegionManagerPtr								m_pRegionManager;
			ChunkManagerPtr									m_pChunkManager;
		};
	}
}
