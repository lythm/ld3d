#include "voxel_pch.h"
#include "voxel_ChunkLoader.h"
#include "voxel_ChunkManager.h"
#include "voxel/voxel_Chunk.h"
#include "voxel/voxel_Meshizer.h"
#include "voxel_PoolManager.h"
#include "voxel_VoxelUtils.h"
#include "voxel_OctreeManager.h"
#include "voxel/voxel_ChunkMesh.h"
namespace ld3d
{
	namespace voxel
	{
		ChunkLoader::ChunkLoader(void) : m_worker(3000, 3000)
		{
			m_pendingCount = 0;
		}


		ChunkLoader::~ChunkLoader(void)
		{
		}
		bool ChunkLoader::Initialize(ChunkManagerPtr pChunkManager, OctreeManagerPtr pOctreeManager, MeshizerPtr pMeshizer)
		{
			m_pChunkManager		= pChunkManager;
			m_pOctreeManager	= pOctreeManager;
			m_pMeshizer			= pMeshizer;

			m_worker.SetMeshizer(pMeshizer);
			m_worker.Start();
			return true;
		}
		void ChunkLoader::Release()
		{
			m_worker.Stop();
			m_worker.Join();
		}
		void ChunkLoader::Update()
		{
			ChunkLoaderWorker::Task t;
			
			while(m_worker.PopTask(t))
			{
				// process task result
				--m_pendingCount;
				switch(t.ev)
				{
				case ChunkLoaderWorker::ev_load_chunk:
					_handle_load_chunk_ret(t);
					break;
				case ChunkLoaderWorker::ev_gen_mesh:
					_handle_gen_mesh(t);
					break;
				default:
					break;
				}
			}
		}
		bool ChunkLoader::RequestChunkDiffSetAsync(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius, const std::function<void(ChunkPtr)>& on_loaded)
		{
			int a = 0;
			int b = 0;
			m_pChunkManager->PickChunkDiffSet(center, radius, refer_center, refer_radius, [&](const ChunkKey& key)
			{
				++a;
				RequestChunkAsync(key, on_loaded);
			});


			/*m_pChunkManager->PickChunkDiffSet1(center, radius, refer_center, refer_radius, [&](const ChunkKey& key)
			{
				++b;
			});

			if(a != b)
			{
				int debug = 0;
			}*/

			return true;
		}
		bool ChunkLoader::RequestChunkAsync(const ChunkKey& key, const std::function<void(ChunkPtr)>& on_loaded)
		{
			ChunkPtr pChunk = m_pChunkManager->FindChunk(key);
			if(pChunk != nullptr)
			{
				pChunk->IncRef();

				if(on_loaded)
				{
					on_loaded(pChunk);
				}

				ChunkMeshPtr pMesh = pChunk->GetMesh();
				if(pMesh == nullptr || pMesh->GetSubsetCount() == 0)
				{
					RequestMeshAsync(pChunk);
				}

				return true;
			}

			ChunkLoaderWorker::Task t;
			t.ev = ChunkLoaderWorker::ev_load_chunk;
			t.chunk_data.Fill(0);
			
			t.chunk_adjacency = ChunkAdjacency(key);
			t.key = key;
			t.on_loaded = on_loaded;
			PushTaskUntilSuccess(t);
			m_pendingCount++;
			return true;
		}
		
		void ChunkLoader::_handle_gen_mesh(ChunkLoaderWorker::Task& t)
		{
			ChunkPtr pChunk = m_pChunkManager->FindChunk(t.key);
			if(pChunk == nullptr)
			{
				t.mesh->Release();
				t.mesh.reset();
				return;
			}
			if(pChunk->GetMesh() != nullptr)
			{
				t.mesh->Release();
				t.mesh.reset();
				return;
			}

			if(t.mesh->GetSubsetCount() == 0)
			{
				t.mesh->Release();
				t.mesh.reset();
				return;
			}
			ChunkMeshPtr pMesh = pool_manager()->AllocChunkMesh();
			pMesh->AllocVertexBuffer(t.mesh->GetVertexCount());
			memcpy(pMesh->GetVertexBuffer(), t.mesh->GetVertexBuffer(), sizeof(ChunkMesh::VoxelVertex) * t.mesh->GetVertexCount());

			for(uint32 i = 0; i < t.mesh->GetSubsetCount(); ++i)
			{
				ChunkMesh::Subset s = t.mesh->GetSubset(i);

				uint64 offset = (uint8*)s.vertexBuffer - (uint8*)t.mesh->GetVertexBuffer();
				
				s.vertexBuffer = (uint8*)pMesh->GetVertexBuffer() + offset;

				pMesh->AddSubset(s);
			}

			pChunk->SetMesh(pMesh);
			t.mesh->Release();
			t.mesh.reset();

			m_pOctreeManager->AddChunk(pChunk);
		}
		
		void ChunkLoader::_handle_load_chunk_ret(ChunkLoaderWorker::Task& t)
		{
			if(t.chunk_empty)
			{
				UpdateChunkAdjacency(t.key);
				return;
			}
			ChunkPtr pChunk = m_pChunkManager->CreateChunk(t.key, t.chunk_data.GetData());
			pChunk->SetAdjacency(t.chunk_adjacency);
			pChunk->SetGenerated(true);
			m_pChunkManager->AddChunk(pChunk);
			UpdateChunkAdjacency(t.key);


			if(t.on_loaded)
			{
				t.on_loaded(pChunk);
			}

			//if(false == pChunk->GetAdjacency().IsVisible())
			//{
			//	return;
			//}

			RequestMeshAsync(pChunk);
		}

		uint32 ChunkLoader::GetPendingCount() const
		{
			return m_pendingCount;
		}
		bool ChunkLoader::RequestChunkAsync(const Coord& center, uint32 radius, const std::function<void(ChunkPtr)>& on_loaded)
		{
			m_pChunkManager->PickChunk(center, radius, [&](const ChunkKey& key)
			{
				RequestChunkAsync(key, on_loaded);
			});

			return true;
		}

		
		void ChunkLoader::UpdateChunkAdjacency(const ChunkKey& key)
		{
			ChunkPtr pChunk = m_pChunkManager->FindChunk(key);

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

				/*if(pChunk != nullptr)
				{
					RequestMeshAsync(pAdj);
				}*/
				/*if(pAdj != nullptr)
				{
					if(false == pAdj->GetAdjacency().IsVisible())
					{
						ChunkMeshPtr pMesh = pAdj->GetMesh();
						if(pMesh)
						{
							pMesh->Reset();
						}
					}
				}*/

			});
		}

		bool ChunkLoader::RequestUnloadChunk(ChunkPtr pChunk)
		{
			pChunk->DecRef();
			if(pChunk->GetRef() != 0)
			{
				return true;
			}

			m_pOctreeManager->RemoveChunk(pChunk);
			m_pChunkManager->RemoveChunk(pChunk);
			UpdateChunkAdjacency(pChunk->GetKey());
			return true;
		}
		bool ChunkLoader::RequestUnloadChunk(const ChunkKey& key)
		{
			ChunkPtr pChunk = m_pChunkManager->FindChunk(key);
			if(pChunk == nullptr)
			{
				return true;
			}
			pChunk->DecRef();
			if(pChunk->GetRef() != 0)
			{
				return true;
			}

			m_pOctreeManager->RemoveChunk(pChunk);
			m_pChunkManager->RemoveChunk(key);
			UpdateChunkAdjacency(key);
			
			return true;
		}

		void ChunkLoader::PushTaskUntilSuccess(ChunkLoaderWorker::Task& t)
		{
			while(m_worker.PushTask(t) == false)
			{
				Update();
				boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
			}
		}
		bool ChunkLoader::RequestMeshAsync(ChunkPtr pChunk)
		{
			ChunkLoaderWorker::Task t;
			t.key = pChunk->GetKey();
			t.chunk_adjacency = pChunk->GetAdjacency();
			t.chunk_data = pChunk->GetData();
			t.ev = ChunkLoaderWorker::ev_gen_mesh;
			t.mesh = pool_manager()->AllocChunkMesh();

			++m_pendingCount;

			PushTaskUntilSuccess(t);

			return true;
		}
	}
}
