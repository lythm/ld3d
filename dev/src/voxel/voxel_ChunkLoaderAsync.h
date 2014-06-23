#pragma once

#include "voxel_ChunkLoaderWorker.h"

namespace ld3d
{
	namespace voxel
	{
		class ChunkLoaderAsync
		{
		public:
			ChunkLoaderAsync(void);
			virtual ~ChunkLoaderAsync(void);

			bool													Initialize(ChunkManagerPtr pChunkManager, RegionManagerPtr pRegionManager, MeshizerPtr pMeshizer);
			void													Release();
			void													Update();

			uint32													GetLoadingQueueSize() const;

			bool													RequestChunkDiffSetAsync(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius);
			bool													RequestChunkAsync(const ChunkKey& key);
			bool													RequestChunkMeshAsync(const ChunkKey& key);
		private:

			void													_handle_load_chunk_ret(ChunkLoaderWorker::Task& t);
			void													_handle_gen_mesh(ChunkLoaderWorker::Task& t);
			bool													GenerateChunkMesh(ChunkPtr pChunk);
		private:
			ChunkManagerPtr											m_pChunkManager;
			RegionManagerPtr										m_pRegionManager;
			MeshizerPtr												m_pMeshizer;

			ChunkLoaderWorker										m_worker;

			int32													m_pendingCount;
		};
	}
}