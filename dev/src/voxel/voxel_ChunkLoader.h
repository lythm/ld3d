#pragma once

#include "voxel_ChunkGenService.h"
#include "voxel/voxel_Bound.h"
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

			bool													RequestChunk(const Coord& center, uint32 radius, uint32 height, const std::function<bool(const ChunkKey&)>& pre_load);
			bool													RequestChunk(const Bound& bound, const std::function<bool(const ChunkKey&)>& pre_load);
			bool													RequestChunkSubtract(const Bound& bound, const Bound& refer_bound, const ChunkLoadedHandler& on_loaded);

			bool													RequestChunkDiffSetAsync(const Coord& center, uint32 radius, uint32 height, const Coord& refer_center, uint32 refer_radius, uint32 refer_height, bool gen_mesh, const ChunkLoadedHandler& on_loaded);
			bool													RequestChunkDiffSetAsync(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius, bool gen_mesh, const ChunkLoadedHandler& on_loaded);
			bool													RequestChunkAsync(const ChunkKey& key, bool gen_mesh, const ChunkLoadedHandler& on_loaded);
			bool													RequestChunkAsync(const Coord& center, uint32 radius, bool gen_mesh, const ChunkLoadedHandler& on_loaded);
			bool													RequestChunkAsync(const Coord& center, uint32 radius, uint32 height, bool gen_mesh, const ChunkLoadedHandler& on_loaded);
			bool													RequestUnloadChunk(const ChunkKey& key);
			bool													RequestUnloadChunk(ChunkPtr pChunk);
			bool													RequestMeshAsync(ChunkPtr pChunk, bool force = false);
			
		private:
			void													_on_mesh_gen_complete(const ChunkKey& key, ChunkMesh* mesh);
			void													_on_chunk_gen_complete(const ChunkKey& key, const ChunkData& data, const ChunkAdjacency& adj, bool is_empty);

			void													UpdateChunkAdjacency(const ChunkKey& key);
		private:
			ChunkManagerPtr											m_pChunkManager;
			OctreeManagerPtr										m_pOctreeManager;
			MeshizerPtr												m_pMeshizer;

			int32													m_pendingCount;
			ChunkGenService											m_service;
		};
	}
}