#pragma once

#include "voxel/voxel_Coord.h"
#include "voxel/voxel_ChunkKey.h"


namespace ld3d
{
	namespace voxel
	{
		class ChunkManager : public std::enable_shared_from_this<ChunkManager>
		{
		public:
			ChunkManager(void);
			virtual ~ChunkManager(void);

			bool											AddBlock(const Coord& c, uint8 type);
			bool											ReplaceBlock(const Coord& c, uint8 type);
			bool											RemoveBlock(const Coord& c);
			bool											IsEmpty(const Coord& c);
			uint8											GetBlock(const Coord& c);
			void											UpdateBlock(const Coord& c);


			ChunkPtr										FindChunk(const ChunkKey& key);

			const std::list<ChunkPtr>&						GetDirtyChunks() const;
			void											ClearDirtyChunks();

			void											Clear();

			ChunkPtr										CreateChunk(const ChunkKey& key, uint8 data[]);

		private:
			ChunkPtr										AllocChunk(uint8 data[]);
		private:
			std::unordered_map<uint64, ChunkPtr>			m_chunkmap;
			std::list<ChunkPtr>								m_dirtyList;
		};
	}
}
