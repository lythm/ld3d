#include "voxel_pch.h"
#include "voxel_RegionManager.h"
#include "voxel/voxel_Region.h"
#include "voxel_ChunkLoader.h"
#include "voxel/voxel_World.h"
#include "voxel_PoolManager.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_VoxelUtils.h"

namespace ld3d
{
	namespace voxel
	{
		RegionManager::RegionManager(void)
		{

		}


		RegionManager::~RegionManager(void)
		{
		}
		bool RegionManager::Initialize(WorldPtr pWorld)
		{
			m_pWorld = pWorld;
			return true;
		}
		void RegionManager::Release()
		{
			m_pWorld.reset();
		}
		RegionPtr RegionManager::LoadRegion(const Coord& c, const std::function<void(RegionPtr, ChunkPtr)>& on_chunk_loaded)
		{
			RegionPtr pRegion = FindRegionByRegionCoord(c);

			if(pRegion == nullptr)
			{
				pRegion = std::allocate_shared<Region, std_allocator_adapter<Region>>(GetAllocator());
				pRegion->Initialize(m_pWorld, c);
			//	pRegion->Load(m_pChunkLoader, false, on_chunk_loaded);

				m_regions.push_back(pRegion);
			}
			return pRegion;
		}
		RegionPtr RegionManager::LoadRegionSync(const Coord& c, const std::function<void(RegionPtr, ChunkPtr)>& on_chunk_loaded)
		{
			RegionPtr pRegion = FindRegionByRegionCoord(c);

			if(pRegion == nullptr)
			{
				pRegion = std::allocate_shared<Region, std_allocator_adapter<Region>>(GetAllocator());
				pRegion->Initialize(m_pWorld, c);
				
			//	pRegion->Load(m_pChunkLoader, true, on_chunk_loaded);

				m_regions.push_back(pRegion);
			}

			return pRegion;
		}
		void RegionManager::UnloadRegionSync(RegionPtr pRegion)
		{
			pRegion->DecRef();

			if(pRegion->GetRef() == 0)
			{
				//pRegion->Unload(m_pChunkLoader, true);

				pRegion->Release();
				m_regions.remove(pRegion);
			}
		}
		void RegionManager::UnloadRegion(RegionPtr pRegion)
		{
			pRegion->DecRef();

			if(pRegion->GetRef() == 0)
			{
				//pRegion->Unload(m_pChunkLoader);

			//	m_pChunkLoader->ReleaseRegion(pRegion);

				m_regions.remove(pRegion);
			}
		}
		void RegionManager::Update()
		{
			//m_pChunkLoader->Update();
		}
		
		RegionPtr RegionManager::FindRegionByRegionCoord(const Coord& c)
		{
			for(auto r : m_regions)
			{
				if(r->GetRegionCoord() == c)
				{
					r->IncRef();
					return r;
				}
			}

			return RegionPtr();
		}

		void RegionManager::AddChunk(ChunkPtr pChunk)
		{
			const Coord& chunk_origin = pChunk->GetKey().ToChunkOrigin();
			Coord region_coord = VoxelUtils::ToRegionCoord(chunk_origin);

			RegionPtr pRegion = FindRegionByRegionCoord(region_coord);
						
			if(pRegion == nullptr)
			{
				pRegion = alloc_object<Region>(GetAllocator());
				pRegion->Initialize(m_pWorld, region_coord);
			
				m_regions.push_back(pRegion);
			}
			
			pRegion->AddChunk(pChunk);
		}
		void RegionManager::FrustumCull(const math::ViewFrustum& vf, const std::function<void(const Coord&, ChunkMeshPtr)>& op)
		{
			for(auto r : m_regions)
			{
				const Coord& region_pos = r->GetRegionOrigin();

				math::ViewFrustum v = vf;
				math::Vector3 trans = region_pos.ToVector3();
				
				v.Transform(math::MatrixTranslation(-trans));

				r->FrustumCull(v, std::bind(op, region_pos, std::placeholders::_1));
			}
		}
	}
}
