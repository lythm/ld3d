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
#include "voxel_ChunkCache.h"

namespace ld3d
{
	namespace voxel
	{
		WorldViewport::WorldViewport()
		{
			m_VP.radius = 32;
			m_VP.height = 32;
			m_lastVP.radius = 32;
			m_lastVP.height = 32;

			m_pChunkCache = alloc_object<ChunkCache>(allocator(), nullptr);
		}


		WorldViewport::~WorldViewport(void)
		{
		}
		
		void WorldViewport::MoveTo(const Coord& c)
		{
			//m_VP.MoveTo(c);

			m_VP.center = c;
		}
		
		bool WorldViewport::Open(WorldPtr pWorld, const Coord& center, uint32 radius)
		{
			m_pWorld = pWorld;
			m_pLoader = pWorld->GetChunkLoader();
			m_pOctreeManager = pWorld->GetOctreeManager();
			m_pChunkManager = pWorld->GetChunkManager();


			Coord center_offset  = Coord(0, 0 , 0);
			radius = 256;
			uint32 height = 128;
			m_VP.center = center;
			m_VP.radius = radius;
			m_VP.height = height;
			m_VP.center_offset = center_offset;

			uint32 size = (radius * 2) / 16;
			size = size * size * size;

			size *= 4;

			m_pChunkCache->Initialize(m_pLoader, size);

			m_pWorld->AddDirtyChunkHandler(std::bind(&WorldViewport::_on_dirty_chunk, this, std::placeholders::_1));
			
			m_pLoader->RequestChunk(m_VP.center + m_VP.center_offset, m_VP.radius, m_VP.height, [&](const ChunkKey& key)
			{
				if(m_pChunkCache->InCache(key))
				{
					return false;
				}
				m_pChunkCache->AddChunk(key);

				return true;
			});

			m_lastVP = m_VP;
			return true;
		}
		void WorldViewport::Close()
		{
			m_pChunkCache->Release();
			m_pChunkCache.reset();

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

			if(abs(dc.x) < CHUNK_SIZE && abs(dc.y) < CHUNK_SIZE && abs(dc.z) < CHUNK_SIZE)
			{
				return;
			}

			m_pLoader->RequestChunk(m_VP.center + m_VP.center_offset, m_VP.radius, m_VP.height, [&](const ChunkKey& key)
			{
				if(m_pChunkCache->InCache(key))
				{
					return false;
				}
				m_pChunkCache->AddChunk(key);

				return true;
			});

			m_lastVP = m_VP;

		}
		void WorldViewport::SetRadius(uint32 radius)
		{
			m_VP.radius = radius;
		}

		void WorldViewport::RefreshMesh()
		{

		}
	}
}

