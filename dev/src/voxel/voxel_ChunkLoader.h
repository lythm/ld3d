#pragma once

#include "voxel/voxel_ChunkKey.h"
#include <queue>
namespace ld3d
{
	namespace voxel
	{
		class ChunkLoader
		{
		public:

			

			ChunkLoader(void);
			virtual ~ChunkLoader(void);

			bool													Initialize(ChunkManagerPtr pChunkManager, RegionManagerPtr pRegionManager, MeshizerPtr pMeshizer);
			void													Release();

			void													LoadChunk(RegionPtr pRegion, const ChunkKey& key, const std::function<void(RegionPtr, ChunkPtr)>& on_loaded);
			bool													LoadChunkSync(RegionPtr pRegion, const ChunkKey& key, const std::function<void(RegionPtr, ChunkPtr)>& on_loaded);
			void													UnloadChunk(RegionPtr pRegion, const ChunkKey& key);
			bool													UnloadChunkSync(RegionPtr pRegion, const ChunkKey& key);
			void													ReleaseRegion(RegionPtr pRegion);
			void													Update();

			uint32													GetLoadingQueueSize() const;
			uint32													GetUnloadingQueueSize() const;

			void													SetMeshizer(MeshizerPtr pMeshizer);

			bool													RequestChunkDiffSet(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius);
			bool													RequestChunk(const Coord& center, uint32 radius);
			bool													RequestChunkMesh(ChunkPtr pChunk);
			
			bool													RequestChunk(const ChunkKey& key);


			bool													RequestChunkMeshAsync(const ChunkKey& key);
			bool													RequestChunkAsync(const ChunkKey& key);
			bool													RequestChunkAsync(const Coord& center, uint32 radius);
			bool													RequestChunkDiffSetAsync(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius);

		private:
			bool													ProcessLoadingQueue();
			bool													ProcessUnloadingQueue();

			bool													CancelLoading(const ChunkKey& key);

			bool													_do_load_chunk(const ChunkKey& key);
			bool													GenerateChunkMesh(ChunkPtr pChunk);
			bool													GenerateChunk(ChunkPtr pChunk);
			bool													_do_unload_chunk(RegionPtr pRegion, const ChunkKey& key);
		private:

			ChunkManagerPtr											m_pChunkManager;
			RegionManagerPtr										m_pRegionManager;
			MeshizerPtr												m_pMeshizer;

			struct LoaderCommand
			{
				enum
				{
					load_chunk,
					unload_chunk,
					gen_chunkmesh,
				};
				uint32												id;
				ChunkKey											key;
				bool												canceled;
			};


			typedef std::deque<LoaderCommand, std_allocator_adapter<LoaderCommand>>	ChunkQueue;

			ChunkQueue	m_loadingQueue;
			
			
			ChunkQueue	m_unloadingQueue;

			
		};


	}
}
