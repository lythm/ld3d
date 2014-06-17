#include "voxel_pch.h"
#include "voxel/voxel_WorldViewPort.h"
#include "voxel/voxel_World.h"
#include "voxel_RegionManager.h"
#include "voxel/voxel_Region.h"
#include "voxel/voxel_Chunk.h"
#include "voxel/voxel_Meshizer.h"
#include "voxel/voxel_ChunkMesh.h"

namespace ld3d
{
	namespace voxel
	{
		WorldViewport::WorldViewport()
		{
			m_size = 0;
		}


		WorldViewport::~WorldViewport(void)
		{
		}
		bool WorldViewport::Inside(const Coord& coord) const
		{
			Coord min_coord = m_center - m_size / 2;
			Coord max_coord = m_center + m_size / 2;
			
			// 2d. axis y is ignored
			return coord.x >= min_coord.x && coord.x <= max_coord.x 
				&& coord.z >= min_coord.z && coord.z <= max_coord.z;
		}
		
		void WorldViewport::MoveTo(const Coord& c)
		{
			m_center = c;
		}
		
		bool WorldViewport::Open(WorldPtr pWorld, const Coord& center, uint32 size, MeshizerPtr pMeshizer)
		{
			m_pMeshizer = pMeshizer;
			m_pWorld = pWorld;
			m_center = center;
			m_center.y = 0;

			m_size = size;

			
			m_pRegionManager = pWorld->GetRegionManager();

			if(InitRegionBuffer() == false)
			{
				return false;
			}


			m_pWorld->AddDirtyChunkHandler(std::bind(&WorldViewport::_on_dirty_chunk, this, std::placeholders::_1));

			return true;
		}
		void WorldViewport::Close()
		{
			ReleaseRegionBuffer();

			m_pWorld.reset();
			m_center = Coord();
			m_size = 0;
			m_pRegionManager.reset();
		}
		bool WorldViewport::InitRegionBuffer()
		{
			UpdateRegionBuffer(true);
			return true;
		}
		void WorldViewport::ReleaseRegionBuffer()
		{
			for(auto r : m_regionBuffer)
			{
				if(r == nullptr)
				{
					continue;
				}
				m_pRegionManager->UnloadRegionSync(r);
			}
			m_regionBuffer.clear();

			for(auto r : m_regionCache)
			{
				m_pRegionManager->UnloadRegionSync(r);
			}
			m_regionCache.clear();
		}
		void WorldViewport::Update()
		{
			Coord center_coord = m_center / (REGION_SIZE);
			center_coord.y = 0;

			if(center_coord != m_centerRegionCoord)
			{
				UpdateRegionBuffer(false);
			}

			UpdateRegionCache();
		}
		void WorldViewport::UpdateRegionCache()
		{
			Coord center_coord = m_center / (REGION_SIZE);
			center_coord.y = 0;

			Coord min_coord = (m_center - m_size / 2) / (REGION_SIZE);
			min_coord.y = 0;
			Coord max_coord = (m_center + m_size / 2) / (REGION_SIZE);
			max_coord.y = 0;

			uint32 dx = max_coord.x - min_coord.x;
			uint32 dz = max_coord.z - min_coord.z;

			std::vector<std::list<RegionPtr>::iterator> erase_list;

			std::list<RegionPtr>::iterator it = m_regionCache.begin();

			int32 cache_margin = 2;

			for(it; it != m_regionCache.end(); ++it)
			{

				Coord r_coord = (*it)->GetRegionCoord();
				
				if(r_coord.x < (min_coord.x - cache_margin) || r_coord.x > (min_coord.x + cache_margin))
				{
					erase_list.push_back(it);
					continue;
				}

				if(r_coord.z < (min_coord.z - cache_margin) || r_coord.z > (min_coord.z + cache_margin))
				{
					erase_list.push_back(it);
					continue;
				}
			}

			for(auto r : erase_list)
			{
				m_pRegionManager->UnloadRegion(*r);
				m_regionCache.erase(r);
			}

			erase_list.clear();
		}
		RegionPtr WorldViewport::FindInCache(const Coord& c)
		{
			for(auto r : m_regionCache)
			{
				if(r->GetRegionCoord() == c)
				{
					return r;
				}
			}

			return nullptr;
		}
		RegionPtr WorldViewport::FindInBuffer(const Coord& c)
		{
			for(auto r : m_regionBuffer)
			{
				if(r->GetRegionCoord() == c)
				{
					return r;
				}
			}

			return nullptr;
		}
		RegionPtr WorldViewport::GetFromCache(const Coord& c)
		{
			std::list<RegionPtr>::iterator it = m_regionCache.begin();
			for(; it != m_regionCache.end(); ++it)
			{
				if((*it)->GetRegionCoord() == c)
				{
					break;
				}
			}

			if(it == m_regionCache.end())
			{
				return nullptr;
			}

			RegionPtr pRegion = *it;

			m_regionCache.erase(it);

			return pRegion;

		}
		void WorldViewport::AddToCache(RegionPtr pRegion)
		{
			m_regionCache.push_back(pRegion);
		}
		void WorldViewport::UpdateRegionBuffer(bool sync)
		{
			m_centerRegionCoord = m_center / REGION_SIZE;
			m_centerRegionCoord.y = 0;

			Coord min_coord = (m_center - m_size / 2) / REGION_SIZE;
			min_coord.y = 0;
			Coord max_coord = (m_center + m_size / 2) / REGION_SIZE;
			max_coord.y = 0;

			uint32 dx = max_coord.x - min_coord.x;
			uint32 dz = max_coord.z - min_coord.z;

			uint32 region_count = (dx + 1) * (dz + 1);

			for(auto r : m_regionBuffer)
			{
				AddToCache(r);
			}

			if(m_regionBuffer.size() != region_count)
			{
				m_regionBuffer.resize(region_count);
			}

			for(size_t x = 0; x <= dx; ++x)
			{
				for(size_t z = 0; z <= dz; ++z)
				{
					Coord c(x, 0, z);
					c += min_coord;

					RegionPtr pRegion = GetFromCache(c);
					if(pRegion == nullptr)
					{
						if(sync)
						{
							pRegion = m_pRegionManager->LoadRegionSync(c, std::bind(&WorldViewport::_on_chunk_loaded, this, std::placeholders::_1, std::placeholders::_2));
						}
						else
						{
							pRegion = m_pRegionManager->LoadRegion(c, std::bind(&WorldViewport::_on_chunk_loaded, this, std::placeholders::_1, std::placeholders::_2));
						}
					}
					m_regionBuffer[x + z * (dx + 1)] = pRegion;
				}
			}
		}
		Coord WorldViewport::GetBaseCoord()
		{
			return m_pWorld->ToRegionOrigin(m_center);
		}
		void WorldViewport::SetDirtyChunkHandler(const std::function<void (const Coord&, ChunkPtr)>& handler)
		{
			handler_dirty_chunk = handler;
		}
		const std::list<ChunkPtr> WorldViewport::GetDirtyChunkList()
		{
			return m_pWorld->GetDirtyChunks();
		}
		void WorldViewport::ClearDirtyChunkList()
		{
			m_pWorld->ClearDirtyChunks();
		}
		void WorldViewport::_on_dirty_chunk(ChunkPtr pChunk)
		{
			if(handler_dirty_chunk == nullptr)
			{
				return;
			}
			const ChunkKey& key = pChunk->GetKey();

			Coord c = key.ToChunkOrigin();

			c = m_pWorld->ToRegionCoord(c);

			handler_dirty_chunk(c, pChunk);
		}
		void WorldViewport::SetRegionLoadedHandler(const std::function<void (RegionPtr)>& handler)
		{
			handler_region_loaded = handler;
		}
		void WorldViewport::SetRegionUnloadedHandler(const std::function<void (RegionPtr)>& handler)
		{
			handler_region_unloaded = handler;
		}
		void WorldViewport::SetViewportSize(uint32 size)
		{
			m_size = size;
			UpdateRegionBuffer(false);
			UpdateRegionCache();
		}
		void WorldViewport::FrustumCull(const math::ViewFrustum& vf, const std::function<void(const Coord&, ChunkMeshPtr)>& op)
		{
			if(m_pMeshizer == nullptr)
			{
				return;
			}

			for(auto r : m_regionBuffer)
			{
				const Coord& region_pos = r->GetRegionOrigin();

				math::ViewFrustum v = vf;
				math::Vector3 trans = region_pos.ToVector3();
				
				v.Transform(math::MatrixTranslation(-trans));

				r->FrustumCull(v, std::bind(op, region_pos, std::placeholders::_1));
			}

		}

		void WorldViewport::_on_chunk_loaded(RegionPtr pRegion, ChunkPtr pChunk)
		{
			if(m_pMeshizer == nullptr)
			{
				return;
			}
			
			ChunkMeshPtr pMesh = pChunk->GetMesh();

			if(pMesh != nullptr)
			{
				return;
			}

			pMesh = std::allocate_shared<ChunkMesh, std_allocator_adapter<ChunkMesh>>(GetAllocator());

			Coord chunk_mesh_base = pChunk->GetKey().ToChunkOrigin() - pRegion->GetRegionOrigin();

			m_pMeshizer->GenerateMesh(pChunk, chunk_mesh_base, pMesh);

			pChunk->SetMesh(pMesh);
	
		}
		const Coord& WorldViewport::GetCenterCoord() const
		{
			return m_center;
		}
	}
}

