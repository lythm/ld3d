#include "voxel_pch.h"
#include "voxel/voxel_WorldViewPort.h"
#include "voxel/voxel_World.h"
#include "voxel_RegionManager.h"
#include "voxel/voxel_Region.h"
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
			m_pLoader = pWorld->GetChunkLoader();
			m_pRegionManager = pWorld->GetRegionManager();


			m_VP.center = center;
			m_VP.radius = radius;

			m_pWorld->AddDirtyChunkHandler(std::bind(&WorldViewport::_on_dirty_chunk, this, std::placeholders::_1));
			
			uint64 t = os_get_tick();
			m_pLoader->RequestChunk(m_VP.center, m_VP.radius);

			uint64 dt = os_get_tick() - t;

			m_lastVP = m_VP;
			return true;
		}
		void WorldViewport::Close()
		{
			m_pWorld.reset();
			m_pRegionManager.reset();
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
			m_pRegionManager->FrustumCull(vf, op);
		}

		const Coord& WorldViewport::GetCenterCoord() const
		{
			return m_VP.center;
		}
		/*bool WorldViewport::RayPick(const math::Ray& r, Coord& block, float& t, math::Vector3& normal)
		{
			bool ret				= false;
			float min_t				= std::numeric_limits<float>::max();
			Coord min_block;
			math::Vector3 min_normal;
			for(auto region : m_regionBuffer)
			{
				if(region->RayPick(r, block, t, normal) == false)
				{
					continue;
				}
				ret = true;

				if(t < min_t)
				{
					min_t = t;
					min_block = block;
					min_normal = normal;
				}
			}

			t			= min_t;
			block		= min_block;
			normal		= min_normal;

			return ret;
		}*/
		
		void WorldViewport::UpdateVP()
		{
			Coord dc = m_VP.center - m_lastVP.center;

			if(abs(dc.x) < CHUNK_SIZE && abs(dc.y) < CHUNK_SIZE && abs(dc.z) < CHUNK_SIZE  && m_VP.radius == m_lastVP.radius)
			{
				return;
			}
			m_pLoader->RequestChunkDiffSetAsync(m_VP.center, m_VP.radius, m_lastVP.center, m_lastVP.radius);

			m_lastVP.center = m_VP.center;
			m_lastVP.radius = m_VP.radius;
		}
		void WorldViewport::SetRadius(uint32 radius)
		{
			m_VP.radius = radius;
		}
	}
}

