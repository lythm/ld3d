#pragma once

#include "voxel_ChunkLoaderWorker.h"

namespace ld3d
{
	namespace voxel
	{
		class ChunkLoader
		{
		public:
			ChunkLoader(void);
			virtual ~ChunkLoader(void);

			bool													Initialize(ChunkManagerPtr pChunkManager, OctreeManagerPtr pOctreeManager, MeshizerPtr pMeshizer);
			void													Release();
			void													Update();

			uint32													GetPendingCount() const;

			bool													RequestChunkDiffSetAsync(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius, const std::function<void(ChunkPtr)>& on_loaded);
			bool													RequestChunkAsync(const ChunkKey& key, const std::function<void(ChunkPtr)>& on_loaded);
			bool													RequestChunkAsync(const Coord& center, uint32 radius, const std::function<void(ChunkPtr)>& on_loaded);
			bool													RequestUnloadChunk(const ChunkKey& key);
			bool													RequestUnloadChunk(ChunkPtr pChunk);
			
		private:
			
			void													_handle_load_chunk_ret(ChunkLoaderWorker::Task& t);
			void													_handle_gen_mesh(ChunkLoaderWorker::Task& t);

			void													_gen_chunk(const ChunkKey& key, uint8* chunk_data, ChunkAdjacency& adj);

			void													UpdateChunkAdjacency(const ChunkKey& key);
		private:
			ChunkManagerPtr											m_pChunkManager;
			OctreeManagerPtr										m_pOctreeManager;
			MeshizerPtr												m_pMeshizer;

			ChunkLoaderWorker										m_worker;

			int32													m_pendingCount;
		};
	}
}