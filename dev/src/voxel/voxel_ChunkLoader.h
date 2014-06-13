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

			bool									Initialize(ChunkManagerPtr pManager);
			void									Release();

			void									LoadChunk(RegionPtr pRegion, const ChunkKey& key);
			bool									LoadChunkSync(RegionPtr pRegion, const ChunkKey& key);
			void									UnloadChunk(RegionPtr pRegion, const ChunkKey& key);
			bool									UnloadChunkSync(RegionPtr pRegion, const ChunkKey& key);
			void									ReleaseRegion(RegionPtr pRegion);
			void									Update();
		private:
			bool									ProcessLoadingQueue();
			bool									ProcessUnloadingQueue();

			bool									_do_load_chunk(RegionPtr pRegion, const ChunkKey& key);
			bool									_do_unload_chunk(RegionPtr pRegion, const ChunkKey& key);
		private:

			ChunkManagerPtr							m_pChunkManager;

			struct ChunkInfo
			{
				ChunkKey							key;
				RegionPtr							pRegion;
			};


			typedef std::queue<ChunkInfo, std::list<ChunkInfo, std_allocator_adapter<ChunkInfo>>>	ChunkQueue;

			ChunkQueue	m_loadingQueue;
			
			
			ChunkQueue	m_unloadingQueue;

			
		};


	}
}
