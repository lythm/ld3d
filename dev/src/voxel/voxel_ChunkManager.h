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

			bool											AddChunk(ChunkPtr pChunk);
			void											RemoveChunk(const ChunkKey& key);

			void											Update(float dt);

			void											AddDirtyChunkHandler(const std::function<void (ChunkPtr)>& handler);

			uint32											GetChunkCount() const;
		private:
			ChunkPtr										AllocChunk(uint8 data[]);
		private:

			typedef 
				std::unordered_map<uint64, 
				ChunkPtr, 
				std::hash<uint64>, 
				std::equal_to<uint64>,
				std_allocator_adapter<
				std::pair<const uint64, ChunkPtr>
				>>											ChunkMap;										

			ChunkMap										m_chunkmap;
			std::list<ChunkPtr>								m_dirtyList;

			std::vector<std::function<void(ChunkPtr)>>		m_dirtyChunkHandlers;
		};
	}
}
