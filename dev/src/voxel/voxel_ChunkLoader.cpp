#include "voxel_pch.h"
#include "voxel_ChunkLoader.h"
#include "voxel_ChunkManager.h"
#include "voxel/voxel_Region.h"
#include "voxel/voxel_Chunk.h"
#include "voxel/voxel_Meshizer.h"
#include "voxel_PoolManager.h"
#include "voxel_VoxelUtils.h"
#include "voxel_RegionManager.h"

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
		bool ChunkLoader::Initialize(ChunkManagerPtr pChunkManager, RegionManagerPtr pRegionManager, MeshizerPtr pMeshizer)
		{
			m_pChunkManager		= pChunkManager;
			m_pRegionManager	= pRegionManager;
			m_pMeshizer			= pMeshizer;

			
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
			for(int i = 0; i < 1; ++i)
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
			for(int i = 0; i < 1; ++i)
			{
				if(ProcessUnloadingQueue() == false)
				{
					break;
				}
			}
		}
		bool ChunkLoader::GenerateChunkMesh(ChunkPtr pChunk)
		{
			if(m_pMeshizer == nullptr)
			{
				return false;
			}
			
			if(pChunk == nullptr)
			{
				return false;
			}

			ChunkMeshPtr pMesh = pChunk->GetMesh();

			if(pMesh == nullptr)
			{
				pMesh = GetPoolManager()->AllocChunkMesh();
			}

			Coord chunk_origin = pChunk->GetKey().ToChunkOrigin();
			Coord region_origin = VoxelUtils::ToRegionOrigin(chunk_origin);


			Coord chunk_mesh_base = chunk_origin - region_origin;

			m_pMeshizer->GenerateMesh(pChunk, chunk_mesh_base, pMesh);

			pChunk->SetMesh(pMesh);

			return true;
		}
		bool ChunkLoader::_do_load_chunk(const ChunkKey& key)
		{
			ChunkPtr pChunk = m_pChunkManager->FindChunk(key);
			if(pChunk != nullptr)
			{
				return true;
			}

			pChunk = m_pChunkManager->CreateChunk(key, nullptr);
			
			if(false == GenerateChunk(pChunk))
			{
				return false;
			}
			
			if(pChunk->IsDirty() == true)
			{
				pChunk->SetDirty(false);
				m_pChunkManager->AddChunk(pChunk);
			}

			GenerateChunkMesh(pChunk);

			m_pRegionManager->AddChunk(pChunk);

			return true;
		}
		bool ChunkLoader::ProcessLoadingQueue()
		{
			ChunkInfo info;
			
			while(m_loadingQueue.size() != 0)
			{
				info = m_loadingQueue.front();
				if(info.canceled == true)
				{
					m_loadingQueue.pop_front();
					continue;
				}
				break;
			}

			if(m_loadingQueue.size() == 0)
			{
				return false;
			}

			bool ret = _do_load_chunk(info.key);

			m_loadingQueue.pop_front();
			
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
				m_unloadingQueue.pop_front();
				return true;
			}

			bool ret = _do_unload_chunk(info.pRegion, info.key);
			
			m_unloadingQueue.pop_front();

			return ret;
		}
		bool ChunkLoader::LoadChunkSync(RegionPtr pRegion, const ChunkKey& key, const std::function<void(RegionPtr, ChunkPtr)>& on_loaded)
		{
			return _do_load_chunk(key);
		}
		void ChunkLoader::LoadChunk(RegionPtr pRegion , const ChunkKey& key, const std::function<void(RegionPtr, ChunkPtr)>& on_loaded)
		{
			ChunkInfo info;
			info.pRegion	= pRegion;
			info.key		= key;
			info.on_loaded	= on_loaded;
			info.canceled	= false;
			m_loadingQueue.push_back(info);
		}
		bool ChunkLoader::UnloadChunkSync(RegionPtr pRegion, const ChunkKey& key)
		{
			return _do_unload_chunk(pRegion, key);
		}
		void ChunkLoader::UnloadChunk(RegionPtr pRegion , const ChunkKey& key)
		{
			if(CancelLoading(key) == true)
			{
				return;
			}
			ChunkInfo info;
			info.pRegion	= pRegion;
			info.key		= key;
			info.canceled	= false;
			m_unloadingQueue.push_back(info);
		}
		void ChunkLoader::ReleaseRegion(RegionPtr pRegion)
		{
			ChunkInfo info;
			info.pRegion	= pRegion;
			info.key		= ChunkKey();

			m_unloadingQueue.push_back(info);
		}
		uint32 ChunkLoader::GetLoadingQueueSize() const
		{
			return (uint32)m_loadingQueue.size();
		}
		uint32 ChunkLoader::GetUnloadingQueueSize() const
		{
			return (uint32)m_unloadingQueue.size();
		}
		bool ChunkLoader::CancelLoading(const ChunkKey& key)
		{
			ChunkQueue::iterator it = m_loadingQueue.begin();
			for(;it != m_loadingQueue.end(); ++it)
			{
				if(it->key == key)
				{
					it->canceled = true;
					return true;
				}
			}

			return false;
		}
		void ChunkLoader::SetMeshizer(MeshizerPtr pMeshizer)
		{
			m_pMeshizer = pMeshizer;
		}
		bool ChunkLoader::GenerateChunk(ChunkPtr pChunk)
		{
			// load chunk
			const ChunkKey& key = pChunk->GetKey();

			Coord chunk_origin = key.ToChunkOrigin();
			Coord region_origin = VoxelUtils::ToRegionOrigin(chunk_origin);
			
			Coord dc = chunk_origin - region_origin;

			for(int x = 0; x < CHUNK_SIZE; ++x)
			{
				for(int z = 0; z < CHUNK_SIZE; ++z)
				{
					float h = 512;

					if(h < (chunk_origin.y))
					{
						continue;
					}

					float dy = h - chunk_origin.y;

					dy = dy > CHUNK_SIZE ? CHUNK_SIZE : dy;

					if(dy == 0)
					{
						dy = 1;
					}
					for(int y = 0; y < dy; ++y)
					{
						pChunk->SetBlock(x, y, z, 1);
					}
				}
			}

			return pChunk->IsDirty();
		}
		bool ChunkLoader::RequestChunk(const ChunkKey& key)
		{
			return _do_load_chunk(key);
		}
	}
}
