#include "voxel_pch.h"
#include "voxel_RegionManager.h"
#include "voxel/voxel_Region.h"
#include "voxel_ChunkLoader.h"
#include "voxel/voxel_World.h"

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
			m_pChunkLoader = std::allocate_shared<ChunkLoader, std_allocator_adapter<ChunkLoader>>(GetAllocator());
			if(m_pChunkLoader->Initialize(m_pWorld->GetChunkManager()) == false)
			{
				return false;
			}
			return true;
		}
		void RegionManager::Release()
		{
			m_pChunkLoader->Release();
			m_pChunkLoader.reset();

			m_pWorld.reset();
		}
		RegionPtr RegionManager::LoadRegion(const Coord& c, const std::function<void(RegionPtr, ChunkPtr)>& on_chunk_loaded)
		{
			RegionPtr pRegion = FindRegion(c);

			if(pRegion == nullptr)
			{
				pRegion = std::allocate_shared<Region, std_allocator_adapter<Region>>(GetAllocator());
				pRegion->Initialize(m_pWorld, c);
				pRegion->Load(m_pChunkLoader, false, on_chunk_loaded);

				m_regions.push_back(pRegion);
			}
			return pRegion;
		}
		RegionPtr RegionManager::LoadRegionSync(const Coord& c, const std::function<void(RegionPtr, ChunkPtr)>& on_chunk_loaded)
		{
			RegionPtr pRegion = FindRegion(c);

			if(pRegion == nullptr)
			{
				pRegion = std::allocate_shared<Region, std_allocator_adapter<Region>>(GetAllocator());
				pRegion->Initialize(m_pWorld, c);
				
				pRegion->Load(m_pChunkLoader, true, on_chunk_loaded);

				m_regions.push_back(pRegion);
			}

			return pRegion;
		}
		void RegionManager::UnloadRegionSync(RegionPtr pRegion)
		{
			pRegion->DecRef();

			if(pRegion->GetRef() == 0)
			{
				pRegion->Unload(m_pChunkLoader, true);

				pRegion->Release();
				m_regions.remove(pRegion);
			}
		}
		void RegionManager::UnloadRegion(RegionPtr pRegion)
		{
			pRegion->DecRef();

			if(pRegion->GetRef() == 0)
			{
				pRegion->Unload(m_pChunkLoader);

				m_pChunkLoader->ReleaseRegion(pRegion);

				m_regions.remove(pRegion);
			}
		}
		void RegionManager::Update()
		{
			m_pChunkLoader->Update();
		}
		
		RegionPtr RegionManager::FindRegion(const Coord& c)
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
		ChunkLoaderPtr RegionManager::GetChunkLoader()
		{
			return m_pChunkLoader;
		}
	}
}
