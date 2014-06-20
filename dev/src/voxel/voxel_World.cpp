#include "voxel_pch.h"

#include "voxel/voxel_World.h"
#include "voxel/voxel_Chunk.h"
#include "voxel/voxel_WorldGen.h"

#include "voxel/voxel_WorldGenPass_Heightmap.h"
#include "voxel_ChunkManager.h"
#include "voxel/voxel_Region.h"
#include "voxel/voxel_WorldViewPort.h"
#include "voxel_RegionManager.h"
#include "voxel_ChunkLoader.h"

namespace ld3d
{
	namespace voxel
	{
		static Allocator*				g_pAllocator = nullptr;
		Allocator*						GetAllocator()
		{
			return g_pAllocator;
		}


		World::World(void)
		{
			m_worldBound = Bound(Coord(-0x10000000/2 * (int32)CHUNK_SIZE, -128 * (int32)CHUNK_SIZE, -0x10000000/2 * (int32)CHUNK_SIZE), 
								Coord((0x10000000/2 - 1) * CHUNK_SIZE, 127 * CHUNK_SIZE, (0x10000000/2 - 1) * CHUNK_SIZE));

		}


		World::~World(void)
		{
		}
		bool World::Create(const std::string& name, WorldGenPtr pGen, MeshizerPtr pMeshizer, Allocator* pAlloc)
		{
			g_pAllocator = pAlloc;

			m_name = name;

			m_pChunkManager		= alloc_object<ChunkManager>(GetAllocator());//std::make_shared<ChunkManager>();
			

			m_pRegionManager	= alloc_object<RegionManager>(GetAllocator());//std::make_shared<RegionManager>();
			
			if(m_pRegionManager->Initialize(shared_from_this()) == false)
			{
				return false;
			}

			m_pChunkLoader		= alloc_object<ChunkLoader>(GetAllocator());
			if(m_pChunkLoader->Initialize(m_pChunkManager, m_pRegionManager, pMeshizer) == false)
			{
				return false;
			}
			
			m_pGen = pGen;

			m_pGen = alloc_object<WorldGen>(GetAllocator());//std::make_shared<WorldGen>();

			m_pGen->Initialize();

			m_pGen->SetWorld(shared_from_this());


			m_pGen->AddPass(alloc_object<WorldGenPass_Heightmap>(GetAllocator()));

		//	m_pGen->GenChunk(Coord(0, 0, 0));

			
			return true;
		}
		void World::Destroy()
		{
			m_pChunkManager->Clear();
			m_pChunkManager.reset();
			m_pRegionManager->Release();
			m_pRegionManager.reset();
			m_pChunkLoader->Release();
			m_pChunkLoader.reset();

		}
		bool World::AddBlock(const Coord& c, uint8 type)
		{
			if(Inside(c) == false)
			{
				return false;
			}
			
			return m_pChunkManager->AddBlock(c, type);
		}
		bool World::ReplaceBlock(const Coord& c, uint8 type)
		{
			if(Inside(c) == false)
			{
				return false;
			}

			return m_pChunkManager->ReplaceBlock(c, type);
		}
		bool World::RemoveBlock(const Coord& c)
		{
			if(Inside(c) == false)
			{
				return false;
			}

			return m_pChunkManager->RemoveBlock(c);
		}
		bool World::IsEmpty(const Coord& c)
		{
			return m_pChunkManager->IsEmpty(c);
		}
		uint8 World::GetBlock(const Coord& c)
		{
			if(Inside(c) == false)
			{
				return false;
			}
			return m_pChunkManager->GetBlock(c);

		}
		ChunkPtr World::FindChunk(const ChunkKey& key)
		{
			if(Inside(key.ToChunkOrigin()) == false)
			{
				return false;
			}

			return m_pChunkManager->FindChunk(key);
		}
		
		void World::UpdateBlock(const Coord& c)
		{
			if(Inside(c) == false)
			{
				return;
			}

			m_pChunkManager->UpdateBlock(c);

		}
		bool World::Inside(const Coord& c) const
		{
			return m_worldBound.Inside(c);
			
		}
		const Bound& World::GetBound() const
		{
			return m_worldBound;
		}
		
		void World::ClearDirtyChunks()
		{
			m_pChunkManager->ClearDirtyChunks();
		}
		
		void World::Update(float dt)
		{
			m_pChunkManager->Update(dt);
		}
		void World::UpdateLoaderProcess()
		{
			m_pChunkLoader->Update();
		}
		ChunkManagerPtr	World::GetChunkManager()
		{
			return m_pChunkManager;
		}
		RegionManagerPtr World::GetRegionManager()
		{
			return m_pRegionManager;
		}

		
		WorldGenPtr World::GetWorldGen()
		{
			return m_pGen;
		}
		void World::AddDirtyChunkHandler(const std::function<void (ChunkPtr)>& handler)
		{
			m_pChunkManager->AddDirtyChunkHandler(handler);
		}
		uint32 World::GetLoadingQueueSize() const
		{
			return m_pChunkLoader->GetLoadingQueueSize();
		}
		uint32 World::GetUnloadingQueueSize() const
		{
			return m_pChunkLoader->GetUnloadingQueueSize();
		}
		uint32 World::GetChunkCount() const
		{
			return m_pChunkManager->GetChunkCount();
		}
		void World::SetMeshizer(MeshizerPtr pMeshizer)
		{
			m_pChunkLoader->SetMeshizer(pMeshizer);
		}
		ChunkLoaderPtr World::GetChunkLoader()
		{
			return m_pChunkLoader;
		}
	}
}


