#include "voxel_pch.h"
#include "voxel_ChunkCache.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_ChunkLoader.h"

namespace ld3d
{
	namespace voxel
	{
		ChunkCache::ChunkCache(ChunkLoaderPtr pLoader) : m_chunks(allocator()), m_chunkMap(allocator())
		{
			m_pLoader = pLoader;
		}


		ChunkCache::~ChunkCache(void)
		{
			Release();
		}
		void ChunkCache::AddChunk(const ChunkKey& key)
		{
			auto find = m_chunkMap.find(key.AsUint64());
			if(find != m_chunkMap.end())
			{
				m_pLoader->RequestUnloadChunk(key);
				m_chunks.erase(find->second);
				m_chunks.push_back(key);
				m_chunkMap[key.AsUint64()] = --m_chunks.rbegin().base();
				return;
			}

			if(m_chunks.size() < m_cacheSize)
			{
				m_chunks.push_back(key);
				m_chunkMap[key.AsUint64()] = --m_chunks.rbegin().base();
				return;
			}

			// cache is full

			const ChunkKey& remove = m_chunks.front();
			
			m_chunkMap.erase(remove.AsUint64());
			m_pLoader->RequestUnloadChunk(remove);
			
			m_chunks.pop_front();


			m_chunks.push_back(key);
			m_chunkMap[key.AsUint64()] = --m_chunks.rbegin().base();
		}
		void ChunkCache::Release()
		{
			Flush();
			m_pLoader.reset();
		}
		void ChunkCache::Update()
		{

		}
		void ChunkCache::Flush()
		{
			m_chunkMap.clear();
			for(auto ch : m_chunks)
			{
				if(m_pLoader)
				{
					m_pLoader->RequestUnloadChunk(ch);
				}
			}

			m_chunks.clear();
		}
		bool ChunkCache::Initialize(ChunkLoaderPtr pLoader, uint32 size)
		{
			m_pLoader		= pLoader;
			m_cacheSize		= size;

			return true;
		}
		bool ChunkCache::InCache(const ChunkKey& key)
		{
			auto find = m_chunkMap.find(key.AsUint64());
			return find != m_chunkMap.end();
		}
	}
}
