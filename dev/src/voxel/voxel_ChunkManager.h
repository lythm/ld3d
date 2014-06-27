#pragma once

#include "voxel/voxel_Coord.h"
#include "voxel/voxel_ChunkKey.h"
#include "voxel/voxel_ChunkData.h"


namespace ld3d
{
	namespace voxel
	{
		
		class ChunkManager : public std::enable_shared_from_this<ChunkManager>
		{
		public:
			typedef std::list<ChunkPtr, std_allocator_adapter<ChunkPtr>>	DirtyChunkList;
			ChunkManager(void);
			virtual ~ChunkManager(void);

			bool											AddBlock(const Coord& c, uint8 type);
			bool											ReplaceBlock(const Coord& c, uint8 type);
			bool											RemoveBlock(const Coord& c);
			bool											IsEmpty(const Coord& c);
			uint8											GetBlock(const Coord& c);
			void											UpdateBlock(const Coord& c);

			ChunkPtr										FindChunk(const ChunkKey& key, bool& loaded);

			const DirtyChunkList&							GetDirtyChunks() const;
			void											ClearDirtyChunks();

			void											Clear();

			ChunkPtr										CreateChunk(const ChunkKey& key, const ChunkData& data);

			bool											AddChunk(const ChunkKey& chunk_key, ChunkPtr pChunk = nullptr);
			bool											AddChunk(ChunkPtr pChunk);
			void											RemoveChunk(const ChunkKey& key);
			void											RemoveChunk(ChunkPtr pChunk);

			void											Update(float dt);

			void											AddDirtyChunkHandler(const std::function<void (ChunkPtr)>& handler);

			uint32											GetChunkCount() const;

			void											PickChunk(const Coord& center, uint32 radius, const std::function<void(const ChunkKey&)>& op);
			void											PickChunkDiffSet(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius, const std::function<void(const ChunkKey&)>& op);
			void											PickChunkDiffSet1(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius, const std::function<void(const ChunkKey&)>& op);

			// -x +x -y +y -z +z
			void											PickAdjacentChunks(const ChunkKey& key, const std::function<void(const ChunkKey& , ChunkPtr, bool)>& op);
			void											PickSurroundingChunks(const ChunkKey& key, const std::function<void(const ChunkKey& , ChunkPtr, bool)>& op);
		private:
			bool											InSphere(const Coord& c, const Coord& center, uint32 radius);
			void											PickChunkSlice(int32 sy, const Coord& center, uint32 radius, const std::function<void(const ChunkKey&)>& op);
			void											PickChunkDiffSetSlice(int32 sy, const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius, const std::function<void(const ChunkKey&)>& op);
		
		private:

			typedef 
				std::unordered_map<uint64, 
				ChunkPtr, 
				std::hash<uint64>, 
				std::equal_to<uint64>,
				std_allocator_adapter<
				std::pair<uint64, ChunkPtr>
				>>											ChunkMap;										

			ChunkMap										m_chunkmap;
			DirtyChunkList									m_dirtyList;

			std::vector<std::function<void(ChunkPtr)>>		m_dirtyChunkHandlers;
		};
	}
}
