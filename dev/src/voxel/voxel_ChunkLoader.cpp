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
			ChunkLoaderWorker::Command t;

			while(m_worker.PopTask(t))
			{
				// process task result
				--m_pendingCount;
				switch(t.id)
				{
				case ChunkLoaderWorker::cmd_load_chunk:
					_handle_load_chunk_ret(t);
					break;
				case ChunkLoaderWorker::cmd_gen_mesh:
					_handle_gen_mesh(t);
					break;
				default:
					break;
				}
			}
		}
		bool ChunkLoader::RequestChunkDiffSetAsync(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius, bool gen_mesh, const ChunkLoadedHandler& on_loaded)
		{
			int a = 0;
			int b = 0;
			m_pChunkManager->PickChunkDiffSet(center, radius, refer_center, refer_radius, [&](const ChunkKey& key)
			{
				++a;
				RequestChunkAsync(key, gen_mesh, on_loaded);
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
		bool ChunkLoader::RequestChunkAsync(const ChunkKey& key, bool gen_mesh, const ChunkLoadedHandler& on_loaded)
		{
			bool loaded = false;
			ChunkPtr pChunk = m_pChunkManager->FindChunk(key, loaded);

			if(pChunk != nullptr)
			{
				pChunk->IncRef();

				if(on_loaded)
				{
					on_loaded(key);
				}

				if(gen_mesh)
				{
					if(pChunk->GetMesh() == nullptr || pChunk->GetMesh()->GetSubsetCount() == 0)
					{
						RequestMeshAsync(pChunk);
					}
				}
				return true;
			}

			if(loaded == true)
			{
				return true;
			}
			ChunkLoaderWorker::Command t;
			t.id = ChunkLoaderWorker::cmd_load_chunk;
			t.chunk_data.Fill(0);
			t.chunk_adjacency = ChunkAdjacency(key);
			t.key = key;
			t.on_loaded = on_loaded;
			t.gen_mesh = gen_mesh;
			t.force_regen = false;
			if(gen_mesh)
			{
				t.mesh = pool_manager()->AllocChunkMeshRaw();
			}
			PushTaskUntilSuccess(t);
			m_pendingCount++;
			return true;
		}

		void ChunkLoader::_handle_gen_mesh(ChunkLoaderWorker::Command& t)
		{
			bool loaded = false;
			ChunkPtr pChunk = m_pChunkManager->FindChunk(t.key, loaded);
			if(pChunk == nullptr)
			{
				t.mesh->Release();
				pool_manager()->FreeChunkMesh(t.mesh);
				return;
			}

			if(t.force_regen == false)
			{
				if(t.mesh->GetSubsetCount() == 0)
				{
					t.mesh->Release();
					pool_manager()->FreeChunkMesh(t.mesh);
					return;
				}

				if(pChunk->GetMesh() != nullptr && pChunk->GetMesh()->GetSubsetCount() != 0)
				{
					t.mesh->Release();
					pool_manager()->FreeChunkMesh(t.mesh);
					return;
				}
			}


			bool added = false;
			if(pChunk->GetMesh() != nullptr && pChunk->GetMesh()->GetSubsetCount() != 0)
			{
				added = true;
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
			pool_manager()->FreeChunkMesh(t.mesh);

			if(added == false)
			{
				m_pOctreeManager->AddChunk(pChunk);
			}
		}

		void ChunkLoader::_handle_load_chunk_ret(ChunkLoaderWorker::Command& t)
		{
			ChunkPtr pChunk = nullptr;
			if(t.chunk_empty == false)
			{
				pChunk = m_pChunkManager->CreateChunk(t.key, t.chunk_data.GetData());
				pChunk->SetAdjacency(t.chunk_adjacency);
				pChunk->SetGenerated(true);
			}
			
			m_pChunkManager->AddChunk(t.key, pChunk);
			
			UpdateChunkAdjacency(t.key);

			//// test

			/*Coord this_coord = t.key.ToChunkCoord();
			m_pChunkManager->PickAdjacentChunks(t.key, [&](const ChunkKey& adjKey, ChunkPtr pAdj)
			{
				if(pAdj)
				{
					RequestMeshAsync(pAdj, true);
				}
			});
*/

			//// test

			if(t.on_loaded)
			{
				t.on_loaded(t.key);
			}

			if(t.gen_mesh)
			{
				_handle_gen_mesh(t);
			}
		}

		uint32 ChunkLoader::GetPendingCount() const
		{
			return m_pendingCount;
		}
		bool ChunkLoader::RequestChunkAsync(const Coord& center, uint32 radius, bool gen_mesh, const ChunkLoadedHandler& on_loaded)
		{
			m_pChunkManager->PickChunk(center, radius, [&](const ChunkKey& key)
			{
				RequestChunkAsync(key, gen_mesh, on_loaded);
			});

			return true;
		}


		void ChunkLoader::UpdateChunkAdjacency(const ChunkKey& key)
		{
			bool loaded = false;
			ChunkPtr pChunk = m_pChunkManager->FindChunk(key, loaded);
			if(loaded == false)
			{
				return;
			}

			Coord this_coord = key.ToChunkCoord();
			m_pChunkManager->PickSurroundingChunks(key, [&](const ChunkKey& adjKey, ChunkPtr pAdj, bool adjLoaded)
			{
				if(adjLoaded == false)
				{
					return;
				}
				if(pChunk != nullptr)
				{
					pChunk->GetAdjacency().UpdateChunkAdjacency(adjKey, pAdj);
				}
				
				if(pAdj == nullptr)
				{
					return;
				}
				
				pAdj->GetAdjacency().UpdateChunkAdjacency(key, pChunk);
				if(pAdj->GetAdjacency().IsComplete())
				{
					RequestMeshAsync(pAdj);
				}
			});
		}
		void ChunkLoader::RequestUpdateAdjacency(const ChunkKey& key)
		{

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
			bool loaded = false;
			ChunkPtr pChunk = m_pChunkManager->FindChunk(key, loaded);
			if(loaded == false)
			{
				return true;
			}
			if(pChunk)
			{
				pChunk->DecRef();
				if(pChunk->GetRef() != 0)
				{
					return true;
				}
			}

			m_pOctreeManager->RemoveChunk(pChunk);
			m_pChunkManager->RemoveChunk(key);
			UpdateChunkAdjacency(key);

			return true;
		}

		void ChunkLoader::PushTaskUntilSuccess(ChunkLoaderWorker::Command& t)
		{
			while(m_worker.PushTask(t) == false)
			{
				Update();
				boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
			}
		}
		bool ChunkLoader::RequestMeshAsync(ChunkPtr pChunk, bool force)
		{
			ChunkLoaderWorker::Command t;
			t.key = pChunk->GetKey();
			t.chunk_adjacency = pChunk->GetAdjacency();
			t.chunk_data = pChunk->GetData();
			t.id = ChunkLoaderWorker::cmd_gen_mesh;
			t.mesh = pool_manager()->AllocChunkMeshRaw();
			t.gen_mesh = true;
			t.force_regen = force;
			++m_pendingCount;

			PushTaskUntilSuccess(t);




			/*for(int x = 0; x < CHUNK_SIZE; ++x)
			{
				for(int 
			}*/


			return true;
		}
	}
}
