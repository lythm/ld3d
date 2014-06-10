#include "voxel_pch.h"
#include "voxel_RegionManager.h"
#include "voxel/voxel_Region.h"

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
			m_loadingQueue.clear();

			while(ProcessUnloadingQueue());

			m_pWorld.reset();
		}
		RegionPtr RegionManager::LoadRegion(const Coord& c)
		{
			RegionPtr pRegion = FindRegion(c);

			if(pRegion == nullptr)
			{
				pRegion = std::allocate_shared<Region, std_allocator_adapter<Region>>(GetAllocator());
				pRegion->Initialize(m_pWorld, c);

				m_loadingQueue.push_back(pRegion);
				m_regions.push_back(pRegion);
			}

			return pRegion;
		}
		void RegionManager::UnloadRegion(RegionPtr pRegion)
		{
			pRegion->DecRef();

			if(pRegion->GetRef() == 0)
			{
				m_unloadingQueue.push_back(pRegion);
				m_regions.remove(pRegion);
			}
		}
		void RegionManager::Update()
		{
			if(ProcessLoadingQueue() == true)
			{
				return;
			}

			ProcessUnloadingQueue();
		}
		bool RegionManager::ProcessLoadingQueue()
		{
			std::list<RegionPtr>::iterator it = m_loadingQueue.begin();

			if(it == m_loadingQueue.end())
			{
				return false;
			}

			(*it)->Load();
				
			(*it)->SetLoaded(true);

			m_loadingQueue.erase(it);
			
			return true;

			
		}
		bool RegionManager::ProcessUnloadingQueue()
		{
			std::list<RegionPtr>::iterator it = m_unloadingQueue.begin();
			if(it == m_unloadingQueue.end())
			{
				return false;
			}

			assert((*it)->IsLoaded() == true);

			(*it)->Unload();
			(*it)->SetLoaded(false);
			
			(*it)->Release();

			m_unloadingQueue.erase(it);

			return true;
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
	}
}
