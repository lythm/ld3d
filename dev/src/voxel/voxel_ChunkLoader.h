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
			enum
			{
				cmd_load_chunk,
				cmd_unload_chunk,
				cmd_release_region,
			};

			ChunkLoader(void);
			virtual ~ChunkLoader(void);

			bool									Initialize(ChunkManagerPtr pChunkManager, RegionManagerPtr pRegionManager, MeshizerPtr pMeshizer);
			void									Release();

			void									LoadChunk(RegionPtr pRegion, const ChunkKey& key, const std::function<void(RegionPtr, ChunkPtr)>& on_loaded);
			bool									LoadChunkSync(RegionPtr pRegion, const ChunkKey& key, const std::function<void(RegionPtr, ChunkPtr)>& on_loaded);
			void									UnloadChunk(RegionPtr pRegion, const ChunkKey& key);
			bool									UnloadChunkSync(RegionPtr pRegion, const ChunkKey& key);
			void									ReleaseRegion(RegionPtr pRegion);
			void									Update();

			uint32									GetLoadingQueueSize() const;
			uint32									GetUnloadingQueueSize() const;

			void									SetMeshizer(MeshizerPtr pMeshizer);

			bool									RequestChunkDiffSet(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius);
			bool									RequestChunk(const Coord& center, uint32 radius);
			bool									RequestChunk(const ChunkKey& key);
			bool									RequestChunkMesh(ChunkPtr pChunk);
		private:
			bool									ProcessLoadingQueue();
			bool									ProcessUnloadingQueue();

			bool									CancelLoading(const ChunkKey& key);

			bool									_do_load_chunk(const ChunkKey& key);
			bool									GenerateChunkMesh(ChunkPtr pChunk);
			bool									GenerateChunk(ChunkPtr pChunk);
			bool									_do_unload_chunk(RegionPtr pRegion, const ChunkKey& key);
		private:

			ChunkManagerPtr							m_pChunkManager;
			RegionManagerPtr						m_pRegionManager;
			MeshizerPtr								m_pMeshizer;

			struct ChunkInfo
			{
				ChunkKey							key;
				RegionPtr							pRegion;
				bool								canceled;

				std::function<void(RegionPtr, 
						ChunkPtr)>					on_loaded;
			};


			typedef std::deque<ChunkInfo, std_allocator_adapter<ChunkInfo>>	ChunkQueue;

			ChunkQueue	m_loadingQueue;
			
			
			ChunkQueue	m_unloadingQueue;

			
		};


	}
}
