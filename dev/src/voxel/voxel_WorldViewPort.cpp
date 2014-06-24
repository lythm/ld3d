#include "voxel_pch.h"
#include "voxel/voxel_WorldViewPort.h"
#include "voxel/voxel_World.h"
#include "voxel_OctreeManager.h"
#include "voxel/voxel_Chunk.h"
#include "voxel/voxel_Meshizer.h"
#include "voxel/voxel_ChunkMesh.h"
#include "voxel_PoolManager.h"
#include "voxel_VoxelUtils.h"
#include "voxel_ChunkManager.h"
#include "voxel_ChunkLoader.h"

namespace ld3d
{
	namespace voxel
	{
		WorldViewport::WorldViewport()
		{
			m_VP.radius = 32;
			m_lastVP.radius = 32;
		}


		WorldViewport::~WorldViewport(void)
		{
		}
		
		void WorldViewport::MoveTo(const Coord& c)
		{
			m_VP.center = c;
		}
		
		bool WorldViewport::Open(WorldPtr pWorld, const Coord& center, uint32 radius)
		{
			m_pWorld = pWorld;
			m_pLoader = pWorld->GetChunkLoaderAsync();
			m_pOctreeManager = pWorld->GetOctreeManager();


			m_VP.center = center;
			m_VP.radius = radius;

			uint32 size = (radius * 2) / 16 + 3;
			size = size * size * size;

			m_chunkCache.set_capacity(size);

			m_pWorld->AddDirtyChunkHandler(std::bind(&WorldViewport::_on_dirty_chunk, this, std::placeholders::_1));
			
			m_pLoader->RequestChunkAsync(m_VP.center, m_VP.radius, std::bind(&WorldViewport::AddChunkToCache, this, std::placeholders::_1));

			while(m_pLoader->GetPendingCount() != 0)
			{
				m_pLoader->Update();
				os_sleep(1);
			}
			m_lastVP = m_VP;
			return true;
		}
		void WorldViewport::Close()
		{
			for(auto chunk : m_chunkCache)
			{
				m_pLoader->RequestUnloadChunk(chunk);
			}
			m_chunkCache.clear();

			m_pWorld.reset();
			m_pOctreeManager.reset();
			m_pLoader.reset();
		}
		
		void WorldViewport::Update()
		{
			UpdateVP();
		}
		
		void WorldViewport::SetDirtyChunkHandler(const std::function<void (const Coord&, ChunkPtr)>& handler)
		{
			handler_dirty_chunk = handler;
		}
		
		void WorldViewport::ClearDirtyChunkList()
		{
			m_pWorld->ClearDirtyChunks();
		}
		void WorldViewport::_on_dirty_chunk(ChunkPtr pChunk)
		{
			const ChunkKey& key = pChunk->GetKey();

			Coord c = key.ToChunkOrigin();

			c = VoxelUtils::ToRegionCoord(c);



			if(handler_dirty_chunk == nullptr)
			{
				return;
			}

			handler_dirty_chunk(c, pChunk);
		}
		
		void WorldViewport::FrustumCull(const math::ViewFrustum& vf, const std::function<void(const Coord&, ChunkMeshPtr)>& op)
		{
			m_pOctreeManager->FrustumCull(vf, op);
		}

		const Coord& WorldViewport::GetCenterCoord() const
		{
			return m_VP.center;
		}
				
		void WorldViewport::UpdateVP()
		{
			Coord dc = m_VP.center - m_lastVP.center;

			if(abs(dc.x) < CHUNK_SIZE && abs(dc.y) < CHUNK_SIZE && abs(dc.z) < CHUNK_SIZE  && m_VP.radius == m_lastVP.radius)
			{
				return;
			}
			m_pLoader->RequestChunkDiffSetAsync(m_VP.center, m_VP.radius, m_lastVP.center, m_lastVP.radius, std::bind(&WorldViewport::AddChunkToCache, this, std::placeholders::_1));

			m_lastVP.center = m_VP.center;
			m_lastVP.radius = m_VP.radius;
		}
		void WorldViewport::SetRadius(uint32 radius)
		{
			m_VP.radius = radius;
		}
		void WorldViewport::AddChunkToCache(ChunkPtr pChunk)
		{
			if(m_chunkCache.full())
			{
				ChunkPtr pRemove = m_chunkCache.front();
				m_pLoader->RequestUnloadChunk(pRemove);
			}
			m_chunkCache.push_back(pChunk);
		}
	}
}

