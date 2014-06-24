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
		ChunkLoader::ChunkLoader(void) : m_worker(50000, 50000)
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
		bool ChunkLoader::RequestChunkDiffSetAsync(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius)
		{
			m_pChunkManager->PickChunkDiffSet(center, radius, refer_center, refer_radius, [&](const ChunkKey& key)
			{
				RequestChunkAsync(key);
			});

			return true;
		}
		bool ChunkLoader::RequestChunkAsync(const ChunkKey& key)
		{
			ChunkPtr pChunk = m_pChunkManager->FindChunk(key);
			if(pChunk != nullptr)
			{
				pChunk->IncRef();
				return true;
			}

			ChunkLoaderWorker::Task t;
			t.ev = ChunkLoaderWorker::ev_load_chunk;
			t.chunk_data.Fill(0);
			
			t.chunk_adjacency = ChunkAdjacency(key);
			t.key = key;

			m_worker.PushTask(t);
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
				return;
			}
			ChunkPtr pChunk = m_pChunkManager->CreateChunk(t.key, t.chunk_data.GetData());
			pChunk->SetAdjacency(t.chunk_adjacency);
			pChunk->SetGenerated(true);
			m_pChunkManager->AddChunk(pChunk);
			UpdateChunkAdjacency(pChunk);

			if(false == pChunk->GetAdjacency().IsVisible())
			{
				return;
			}

			t.mesh = pool_manager()->AllocChunkMesh();
			t.mesh->AllocVertexBuffer(80000);

			t.ev = ChunkLoaderWorker::ev_gen_mesh;
			++m_pendingCount;
			m_worker.PushTask(t);
		}

		uint32 ChunkLoader::GetPendingCount() const
		{
			return m_pendingCount;
		}
		bool ChunkLoader::RequestChunkAsync(const Coord& center, uint32 radius)
		{
			m_pChunkManager->PickChunk(center, radius, [&](const ChunkKey& key)
			{
				RequestChunkAsync(key);
			});

			return true;
		}

		
		void ChunkLoader::UpdateChunkAdjacency(ChunkPtr pChunk)
		{
			const ChunkKey& key = pChunk->GetKey();

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
			return true;
		}
		
	}
}
