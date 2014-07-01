#pragma once

#include "voxel_ChunkLoaderWorker.h"
#include "voxel_ChunkGenService.h"

namespace ld3d
{
	namespace voxel
	{
		class ChunkLoader
		{
		public:

			typedef std::function<void(const ChunkKey&)>			ChunkLoadedHandler;

			ChunkLoader(void);
			virtual ~ChunkLoader(void);

			bool													Initialize(ChunkManagerPtr pChunkManager, OctreeManagerPtr pOctreeManager, MeshizerPtr pMeshizer, WorldGenPtr pWorldGen);
			void													Release();
			void													Update();

			uint32													GetPendingCount() const;

			bool													RequestChunkDiffSetAsync(const Coord& center, uint32 radius, uint32 height, const Coord& refer_center, uint32 refer_radius, uint32 refer_height, bool gen_mesh, const ChunkLoadedHandler& on_loaded);
			bool													RequestChunkDiffSetAsync(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius, bool gen_mesh, const ChunkLoadedHandler& on_loaded);
			bool													RequestChunkAsync(const ChunkKey& key, bool gen_mesh, const ChunkLoadedHandler& on_loaded);
			bool													RequestChunkAsync(const Coord& center, uint32 radius, bool gen_mesh, const ChunkLoadedHandler& on_loaded);
			bool													RequestChunkAsync(const Coord& center, uint32 radius, uint32 height, bool gen_mesh, const ChunkLoadedHandler& on_loaded);
			bool													RequestUnloadChunk(const ChunkKey& key);
			bool													RequestUnloadChunk(ChunkPtr pChunk);
			bool													RequestMeshAsync(ChunkPtr pChunk, bool force = false);
			
		private:

			void													PushTaskUntilSuccess(ChunkLoaderWorker::Command& t);
			void													_handle_load_chunk_ret(ChunkLoaderWorker::Command& t);
			void													_handle_gen_mesh(ChunkLoaderWorker::Command& t);

			void													_gen_chunk(const ChunkKey& key, uint8* chunk_data, ChunkAdjacency& adj);

			void													UpdateChunkAdjacency(const ChunkKey& key);
		private:
			ChunkManagerPtr											m_pChunkManager;
			OctreeManagerPtr										m_pOctreeManager;
			MeshizerPtr												m_pMeshizer;

			ChunkLoaderWorker										m_worker;

			int32													m_pendingCount;

			ChunkGenService											m_service;
		};
	}
}