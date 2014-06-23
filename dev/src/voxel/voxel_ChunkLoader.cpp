#include "voxel_pch.h"
#include "voxel_ChunkLoader.h"
#include "voxel_ChunkManager.h"
#include "voxel/voxel_Region.h"
#include "voxel/voxel_Chunk.h"
#include "voxel/voxel_Meshizer.h"
#include "voxel_PoolManager.h"
#include "voxel_VoxelUtils.h"
#include "voxel_RegionManager.h"
#include "voxel/voxel_ChunkMesh.h"

namespace ld3d
{
	namespace voxel
	{
		ChunkLoader::ChunkLoader(void) : m_loadingQueue(allocator()), m_unloadingQueue(allocator())
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
			if(pMesh != nullptr)
			{
				return false;
			}
			
			pMesh = pool_manager()->AllocChunkMesh();
			

			Coord chunk_origin = pChunk->GetKey().ToChunkOrigin();
			Coord region_origin = VoxelUtils::ToRegionOrigin(chunk_origin);


			Coord chunk_mesh_base = chunk_origin - region_origin;

			m_pMeshizer->GenerateMesh(pChunk, chunk_mesh_base, pMesh);
			if(pMesh->GetSubsetCount() == 0)
			{
				return false;
			}
			pChunk->SetMesh(pMesh);

			return true;
		}
		bool ChunkLoader::_do_load_chunk(const ChunkKey& key)
		{
			ChunkPtr pChunk = m_pChunkManager->FindChunk(key);
			if(pChunk != nullptr)
			{
				return false;
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
				m_pRegionManager->AddChunk(pChunk);
			}
			else
			{
				pChunk = nullptr;
			}

			Coord this_coord = key.ToChunkCoord();
			m_pChunkManager->PickAdjacentChunks(key, [&](const ChunkKey& adjKey, ChunkPtr pAdj)
			{
				if(pChunk != nullptr)
				{
					pChunk->GetAdjacency().OnAdjacentChunkLoaded(adjKey.ToChunkCoord(), pAdj);
				}

				if(pAdj == nullptr)
				{
					return;
				}

				pAdj->GetAdjacency().OnAdjacentChunkLoaded(this_coord, pChunk);

				if(pAdj != nullptr)
				{
					if(false == pChunk->GetAdjacency().IsVisible())
					{
						ChunkMeshPtr pMesh = pChunk->GetMesh();
						if(pMesh)
						{
							pMesh->Reset();
						}
					}
				}

			});
			
			return true;
		}
		bool ChunkLoader::ProcessLoadingQueue()
		{
			LoaderCommand cmd;
			bool ret = false;
			while(m_loadingQueue.size() != 0)
			{
				cmd = m_loadingQueue.front();
				if(cmd.canceled == true)
				{
					m_loadingQueue.pop_front();
					continue;
				}

				

				switch(cmd.id)
				{
				case LoaderCommand::load_chunk:
					ret = _do_load_chunk(cmd.key);
					if(ret == false)
					{
						m_loadingQueue.pop_front();
						continue;
					}
					break;
				case LoaderCommand::gen_chunkmesh:
					{
						ChunkPtr pChunk = m_pChunkManager->FindChunk(cmd.key);
						if(pChunk == nullptr)
						{
							m_loadingQueue.pop_front();
							continue;
						}
						ret = GenerateChunkMesh(pChunk);
					}
					break;
				default:
					break;
				}

				break;
			}

			if(m_loadingQueue.size() == 0)
			{
				return ret;
			}
			
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

			LoaderCommand cmd = m_unloadingQueue.front();



			if(cmd.key == ChunkKey())
			{
				m_unloadingQueue.pop_front();
				return true;
			}

			//	bool ret = _do_unload_chunk(info.pRegion, info.key);

			m_unloadingQueue.pop_front();

			return true;
		}
		bool ChunkLoader::LoadChunkSync(RegionPtr pRegion, const ChunkKey& key, const std::function<void(RegionPtr, ChunkPtr)>& on_loaded)
		{
			return _do_load_chunk(key);
		}
		void ChunkLoader::LoadChunk(RegionPtr pRegion , const ChunkKey& key, const std::function<void(RegionPtr, ChunkPtr)>& on_loaded)
		{

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
		bool ChunkLoader::RequestChunkMesh(ChunkPtr pChunk)
		{
			if(pChunk == nullptr)
			{
				return false;
			}

			if(false == pChunk->GetAdjacency().IsVisible())
			{
				ChunkMeshPtr pMesh = pChunk->GetMesh();
				if(pMesh)
				{
					pMesh->Reset();
				}
				return false;
			}

			return GenerateChunkMesh(pChunk);
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
					float h = 0;

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
		bool ChunkLoader::RequestChunkAsync(const ChunkKey& key)
		{
			LoaderCommand cmd;
			cmd.id = LoaderCommand::load_chunk;
			cmd.key = key;
			cmd.canceled = false;
			m_loadingQueue.push_back(cmd);

			return true;
		}
		bool ChunkLoader::RequestChunk(const Coord& center, uint32 radius)
		{
			m_pChunkManager->PickChunk(center, radius, [&](const ChunkKey& key, ChunkPtr pChunk)
			{
				if(pChunk != nullptr)
				{
					return;
				}
				RequestChunk(key);
			});

			m_pChunkManager->PickChunk(center, radius, [&](const ChunkKey& key, ChunkPtr pChunk)
			{
				if(pChunk == nullptr)
				{
					return;
				}
				RequestChunkMesh(pChunk);
			});


			return true;
		}
		bool ChunkLoader::RequestChunkAsync(const Coord& center, uint32 radius)
		{
			m_pChunkManager->PickChunk(center, radius, [&](const ChunkKey& key, ChunkPtr pChunk)
			{
				if(pChunk != nullptr)
				{
					return;
				}
				RequestChunk(key);
			});

			m_pChunkManager->PickChunk(center, radius, [&](const ChunkKey& key, ChunkPtr pChunk)
			{
				if(pChunk == nullptr)
				{
					return;
				}
				RequestChunkMeshAsync(key);
			});


			return true;
		}
		bool ChunkLoader::RequestChunkDiffSet(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius)
		{
			m_pChunkManager->PickChunkDiffSet(center, radius, refer_center, refer_radius, [&](const ChunkKey& key, ChunkPtr pChunk)
			{
				if(pChunk != nullptr)
				{
					return;
				}
				RequestChunk(key);
			});

			m_pChunkManager->PickChunkDiffSet(center, radius, refer_center, refer_radius, [&](const ChunkKey& key, ChunkPtr pChunk)
			{
				if(pChunk == nullptr)
				{
					return;
				}
				RequestChunkMesh(pChunk);
			});

			return true;
		}
		bool ChunkLoader::RequestChunkDiffSetAsync(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius)
		{
			m_pChunkManager->PickChunkDiffSet(center, radius, refer_center, refer_radius, [&](const ChunkKey& key, ChunkPtr pChunk)
			{
				if(pChunk != nullptr)
				{
					return;
				}
				RequestChunk(key);
			});

			m_pChunkManager->PickChunkDiffSet(center, radius, refer_center, refer_radius, [&](const ChunkKey& key, ChunkPtr pChunk)
			{
				if(pChunk == nullptr)
				{
					return;
				}
				RequestChunkMeshAsync(key);
			});

			return true;
		}
		bool ChunkLoader::RequestChunkMeshAsync(const ChunkKey& key)
		{
			ChunkPtr pChunk = m_pChunkManager->FindChunk(key);

			if(pChunk == nullptr)
			{
				return false;
			}

			if(false == pChunk->GetAdjacency().IsVisible())
			{
				ChunkMeshPtr pMesh = pChunk->GetMesh();
				if(pMesh)
				{
					pMesh->Reset();
				}
				return false;
			}


			LoaderCommand cmd;
			cmd.id = LoaderCommand::gen_chunkmesh;
			cmd.key = key;
			cmd.canceled = false;
			m_loadingQueue.push_back(cmd);

			return true;
		}
	}
}
