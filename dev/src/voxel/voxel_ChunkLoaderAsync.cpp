#include "voxel_pch.h"
#include "voxel_ChunkLoaderAsync.h"
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
		ChunkLoaderAsync::ChunkLoaderAsync(void) : m_worker(50000, 50000)
		{
			m_pendingCount = 0;
		}


		ChunkLoaderAsync::~ChunkLoaderAsync(void)
		{
		}
		bool ChunkLoaderAsync::Initialize(ChunkManagerPtr pChunkManager, RegionManagerPtr pRegionManager, MeshizerPtr pMeshizer)
		{
			m_pChunkManager		= pChunkManager;
			m_pRegionManager	= pRegionManager;
			m_pMeshizer			= pMeshizer;

			m_worker.SetMeshizer(pMeshizer);
			m_worker.Start();
			return true;
		}
		void ChunkLoaderAsync::Release()
		{
			m_worker.Stop();
			m_worker.Join();
		}
		void ChunkLoaderAsync::Update()
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
		bool ChunkLoaderAsync::RequestChunkDiffSetAsync(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius)
		{
			m_pChunkManager->PickChunkDiffSet(center, radius, refer_center, refer_radius, [&](const ChunkKey& key, ChunkPtr pChunk)
			{
				if(pChunk != nullptr)
				{
					return;
				}
				RequestChunkAsync(key);
			});

			/*m_pChunkManager->PickChunkDiffSet(center, radius, refer_center, refer_radius, [&](const ChunkKey& key, ChunkPtr pChunk)
			{
				if(pChunk == nullptr)
				{
					return;
				}
				RequestChunkMeshAsync(key);
			});*/

			return true;
		}
		bool ChunkLoaderAsync::RequestChunkAsync(const ChunkKey& key)
		{
			ChunkPtr pChunk = m_pChunkManager->FindChunk(key);
			if(pChunk != nullptr)
			{
				return false;
			}

			ChunkLoaderWorker::Task t;
			t.ev = ChunkLoaderWorker::ev_load_chunk;
			t.chunk_data = (uint8*)allocator()->Alloc(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
			
			t.chunk_adjacency = ChunkAdjacency(key);
			t.key = key;

			m_worker.PushTask(t);
			m_pendingCount++;
			return true;
		}
		bool ChunkLoaderAsync::RequestChunkMeshAsync(const ChunkKey& key)
		{
			/*ChunkPtr pChunk = m_pChunkManager->FindChunk(key);

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

			return true;*/

			return true;
		}
		void ChunkLoaderAsync::_handle_gen_mesh(ChunkLoaderWorker::Task& t)
		{
			allocator()->Free(t.chunk_data);

			ChunkPtr pChunk = m_pChunkManager->FindChunk(t.key);
			if(pChunk == nullptr)
			{
				return;
			}
			if(pChunk->GetMesh() != nullptr)
			{
				return;
			}

			if(t.mesh->GetSubsetCount() == 0)
			{
				return;
			}
			ChunkMeshPtr pMesh = pool_manager()->AllocChunkMesh();
			pMesh->AllocVertexBuffer(t.mesh->GetVertexCount());
			memcpy(pMesh->GetVertexBuffer(), t.mesh->GetVertexBuffer(), sizeof(ChunkMesh::VoxelVertex) * t.mesh->GetVertexCount());

			for(int i = 0; i < t.mesh->GetSubsetCount(); ++i)
			{
				ChunkMesh::Subset s = t.mesh->GetSubset(i);

				uint64 offset = (uint8*)s.vertexBuffer - (uint8*)t.mesh->GetVertexBuffer();
				
				s.vertexBuffer = (uint8*)pMesh->GetVertexBuffer() + offset;

				pMesh->AddSubset(s);
			}

			pChunk->SetMesh(pMesh);
			t.mesh->Release();
			t.mesh.reset();

		//	t.mesh->Reset();

		}
		void ChunkLoaderAsync::_handle_load_chunk_ret(ChunkLoaderWorker::Task& t)
		{
			if(t.chunk_empty)
			{
				return;
			}
			ChunkPtr pChunk = m_pChunkManager->CreateChunk(t.key, t.chunk_data);
			pChunk->SetAdjacency(t.chunk_adjacency);

			m_pChunkManager->AddChunk(pChunk);
			m_pRegionManager->AddChunk(pChunk);
			
			Coord this_coord = t.key.ToChunkCoord();
			m_pChunkManager->PickAdjacentChunks(t.key, [&](const ChunkKey& adjKey, ChunkPtr pAdj)
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

			//allocator()->Free(t.chunk_data);


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

		uint32 ChunkLoaderAsync::GetLoadingQueueSize() const
		{
			return m_pendingCount;
		}
		bool ChunkLoaderAsync::GenerateChunkMesh(ChunkPtr pChunk)
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
	}
}
