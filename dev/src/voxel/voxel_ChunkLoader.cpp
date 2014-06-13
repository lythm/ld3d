#include "voxel_pch.h"
#include "voxel_ChunkLoader.h"
#include "voxel_ChunkManager.h"
#include "voxel/voxel_Region.h"

namespace ld3d
{
	namespace voxel
	{
		ChunkLoader::ChunkLoader(void) : m_loadingQueue(GetAllocator()), m_unloadingQueue(GetAllocator())
		{
		}


		ChunkLoader::~ChunkLoader(void)
		{
		}
		bool ChunkLoader::Initialize(ChunkManagerPtr pManager)
		{
			m_pChunkManager = pManager;
			return true;
		}
		void ChunkLoader::Release()
		{
			//m_loadingQueue.c.clear();
			while(ProcessUnloadingQueue());

			m_pChunkManager.reset();
		}
		void ChunkLoader::Update()
		{
			for(int i = 0; i < 1000; ++i)
			{
				if(ProcessLoadingQueue() == false)
				{
					break;
				}
			}

			for(int i = 0; i < 1000; ++i)
			{
				if(ProcessUnloadingQueue() == false)
				{
					break;
				}
			}
		}
		bool ChunkLoader::_do_load_chunk(RegionPtr pRegion, const ChunkKey& key)
		{
			ChunkPtr pChunk = m_pChunkManager->FindChunk(key);
			if(pChunk != nullptr)
			{
				return true;
			}

			// load chunk
			float* height_map = pRegion->GetHeightmap();

			Coord region_origin = pRegion->GetRegionOrigin();
			Coord chunk_origin = key.ToChunkOrigin();

			Coord dc = chunk_origin - region_origin;

			for(int x = 0; x < CHUNK_SIZE; ++x)
			{
				for(int z = 0; z < CHUNK_SIZE; ++z)
				{
					int rx = x + dc.x;
					int rz = z + dc.z;
					float h = height_map[rz * REGION_SIZE + rx] * 100;

					if(h < chunk_origin.y)
					{
						continue;
					}
				}
			}

			return true;
		}
		bool ChunkLoader::ProcessLoadingQueue()
		{
			if(0 == m_loadingQueue.size())
			{
				return false;
			}

			const ChunkInfo& info = m_loadingQueue.front();

			bool ret = _do_load_chunk(info.pRegion, info.key);

			m_loadingQueue.pop();
			
			return ret;
		}
		bool ChunkLoader::_do_unload_chunk(RegionPtr pRegion, const ChunkKey& key)
		{
			ChunkPtr pChunk = m_pChunkManager->FindChunk(key);
			if(pChunk == nullptr)
			{
				return true;
			}


			// save chunk

			m_pChunkManager->RemoveChunk(key);

			// unload chunk

			return true;
		}
		bool ChunkLoader::ProcessUnloadingQueue()
		{
			if(0 == m_unloadingQueue.size())
			{
				return false;
			}

			ChunkInfo info = m_unloadingQueue.front();

			

			if(info.key == ChunkKey())
			{
				info.pRegion->Release();
				info.pRegion.reset();
				m_unloadingQueue.pop();
				return true;
			}

			bool ret = _do_unload_chunk(info.pRegion, info.key);
			
			m_unloadingQueue.pop();

			return ret;
		}
		bool ChunkLoader::LoadChunkSync(RegionPtr pRegion, const ChunkKey& key)
		{
			return _do_load_chunk(pRegion, key);
		}
		void ChunkLoader::LoadChunk(RegionPtr pRegion , const ChunkKey& key)
		{
			ChunkInfo info;
			info.pRegion	= pRegion;
			info.key		= key;
			
			m_loadingQueue.push(info);
		}
		bool ChunkLoader::UnloadChunkSync(RegionPtr pRegion, const ChunkKey& key)
		{
			return _do_unload_chunk(pRegion, key);
		}
		void ChunkLoader::UnloadChunk(RegionPtr pRegion , const ChunkKey& key)
		{
			ChunkInfo info;
			info.pRegion	= pRegion;
			info.key		= key;

			m_unloadingQueue.push(info);
		}
		void ChunkLoader::ReleaseRegion(RegionPtr pRegion)
		{
			ChunkInfo info;
			info.pRegion	= pRegion;
			info.key		= ChunkKey();

			m_unloadingQueue.push(info);
		}
	}
}
