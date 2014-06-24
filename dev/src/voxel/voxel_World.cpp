#include "voxel_pch.h"

#include "voxel/voxel_World.h"
#include "voxel/voxel_Chunk.h"
#include "voxel/voxel_WorldGen.h"

#include "voxel/voxel_WorldGenPass_Heightmap.h"
#include "voxel_ChunkManager.h"
#include "voxel/voxel_WorldViewPort.h"
#include "voxel_ChunkLoader.h"
#include "voxel_OctreeManager.h"

namespace ld3d
{
	namespace voxel
	{
		static Logger					g_logger;
		static Allocator*				g_pAllocator = nullptr;
		Allocator*						allocator()
		{
			return g_pAllocator;
		}
		Logger&							logger()
		{
			return g_logger;
		}

		World::World(void)
		{
			m_worldBound = Bound(Coord(-0x10000000/2 * (int32)CHUNK_SIZE, -128 * (int32)CHUNK_SIZE, -0x10000000/2 * (int32)CHUNK_SIZE), 
								Coord((0x10000000/2 - 1) * CHUNK_SIZE, 127 * CHUNK_SIZE, (0x10000000/2 - 1) * CHUNK_SIZE));

		}


		World::~World(void)
		{
		}
		bool World::Create(const std::string& name, WorldGenPtr pGen, MeshizerPtr pMeshizer, Allocator* pAlloc, Logger logger)
		{
			g_logger = logger;
			g_pAllocator = pAlloc;

			m_name = name;

			m_pChunkManager		= alloc_object<ChunkManager>(allocator());//std::make_shared<ChunkManager>();
			
			m_pOctreeManager	= alloc_object<OctreeManager>(allocator());
			
			m_pChunkLoader = alloc_object<ChunkLoader>(allocator());
			if(m_pChunkLoader->Initialize(m_pChunkManager, m_pOctreeManager, pMeshizer) == false)
			{
				return false;
			}

			m_pGen = pGen;

			m_pGen = alloc_object<WorldGen>(allocator());//std::make_shared<WorldGen>();

			m_pGen->Initialize();

			m_pGen->SetWorld(shared_from_this());


			m_pGen->AddPass(alloc_object<WorldGenPass_Heightmap>(allocator()));

		//	m_pGen->GenChunk(Coord(0, 0, 0));

			
			return true;
		}
		void World::Destroy()
		{
			m_pChunkManager->Clear();
			m_pChunkManager.reset();

			m_pChunkLoader->Release();
			m_pChunkLoader.reset();
			m_pOctreeManager.reset();

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
		
		uint32 World::GetChunkCount() const
		{
			return m_pChunkManager->GetChunkCount();
		}
		
		ChunkLoaderPtr	World::GetChunkLoaderAsync()
		{
			return m_pChunkLoader;
		}
		OctreeManagerPtr World::GetOctreeManager()
		{
			return m_pOctreeManager;
		}
	}
}


