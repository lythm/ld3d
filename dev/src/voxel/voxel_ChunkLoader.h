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

			uint32													GetLoadingQueueSize() const;

			bool													RequestChunk(const ChunkKey& key);
			bool													RequestChunk(const Coord& center, uint32 radius);
			bool													RequestChunkMesh(ChunkPtr pChunk);


			bool													RequestChunkDiffSetAsync(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius);
			bool													RequestChunkAsync(const ChunkKey& key);
			bool													RequestChunkAsync(const Coord& center, uint32 radius);
			bool													RequestChunkMeshAsync(const ChunkKey& key);
		private:

			void													_handle_load_chunk_ret(ChunkLoaderWorker::Task& t);
			void													_handle_gen_mesh(ChunkLoaderWorker::Task& t);

			void													_gen_chunk(const ChunkKey& key, uint8* chunk_data, ChunkAdjacency& adj);
			bool													GenerateChunkMesh(ChunkPtr pChunk);
			void													UpdateChunkAdjacency(ChunkPtr pChunk);
		private:
			ChunkManagerPtr											m_pChunkManager;
			OctreeManagerPtr										m_pOctreeManager;
			MeshizerPtr												m_pMeshizer;

			ChunkLoaderWorker										m_worker;

			int32													m_pendingCount;
		};
	}
}