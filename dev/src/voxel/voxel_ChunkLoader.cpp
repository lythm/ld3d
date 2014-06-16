#include "voxel_pch.h"
#include "voxel_ChunkLoader.h"
#include "voxel_ChunkManager.h"
#include "voxel/voxel_Region.h"
#include "voxel/voxel_Chunk.h"
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
			for(int i = 0; i < 10; ++i)
			{
				if(ProcessLoadingQueue() == false)
				{
					break;
				}
			}


			if(m_loadingQueue.size() != 0)
			{
				return;
			}
			for(int i = 0; i < 10; ++i)
			{
				if(ProcessUnloadingQueue() == false)
				{
					break;
				}
			}
		}
		bool ChunkLoader::_do_load_chunk(RegionPtr pRegion, const ChunkKey& key, const std::function<void(RegionPtr, ChunkPtr)>& on_loaded)
		{
			ChunkPtr pChunk = m_pChunkManager->FindChunk(key);
			if(pChunk != nullptr)
			{
				return true;
			}


			pChunk = m_pChunkManager->CreateChunk(key, nullptr);
			
			if(false == pRegion->LoadChunk(pChunk))
			{
				return false;
			}
			
			if(pChunk->IsDirty() == true)
			{
				if(on_loaded != nullptr)
				{
					on_loaded(pRegion, pChunk);
				}

				pChunk->SetDirty(false);
				m_pChunkManager->AddChunk(pChunk);
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

			bool ret = _do_load_chunk(info.pRegion, info.key, info.on_loaded);

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

			pRegion->UnloadChunk(pChunk);

			m_pChunkManager->RemoveChunk(key);

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
		bool ChunkLoader::LoadChunkSync(RegionPtr pRegion, const ChunkKey& key, const std::function<void(RegionPtr, ChunkPtr)>& on_loaded)
		{
			return _do_load_chunk(pRegion, key, on_loaded);
		}
		void ChunkLoader::LoadChunk(RegionPtr pRegion , const ChunkKey& key, const std::function<void(RegionPtr, ChunkPtr)>& on_loaded)
		{
			ChunkInfo info;
			info.pRegion	= pRegion;
			info.key		= key;
			info.on_loaded	= on_loaded;
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
		uint32 ChunkLoader::GetLoadingQueueSize() const
		{
			return (uint32)m_loadingQueue.size();
		}
		uint32 ChunkLoader::GetUnloadingQueueSize() const
		{
			return (uint32)m_unloadingQueue.size();
		}
	}
}
