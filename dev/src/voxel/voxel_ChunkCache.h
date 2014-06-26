#pragma once


namespace ld3d
{
	namespace voxel
	{
		class ChunkCache
		{
		public:
			ChunkCache(ChunkLoaderPtr pLoader);
			virtual ~ChunkCache(void);

			void													AddChunk(ChunkPtr pChunk);
			void													Release();
			bool													Initialize(ChunkLoaderPtr pLoader, uint32 size);
			void													Update();

			void													Flush();

			void													RefreshMesh();
		private:

			typedef std::list<ChunkPtr, 
				std_allocator_adapter<ChunkPtr>>					ChunkList;

			ChunkList												m_chunks;

			typedef std::unordered_map<uint64, 
				ChunkList::iterator, 
				std::hash<uint64>, 
				std::equal_to<uint64>,
				std_allocator_adapter<std::pair<uint64, 
					ChunkList::iterator>>>							ChunkMap;

			ChunkMap												m_chunkMap;

			uint32													m_cacheSize;
			ChunkLoaderPtr											m_pLoader;
		};
	}
}
