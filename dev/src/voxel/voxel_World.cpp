#include "voxel_pch.h"

#include "voxel/voxel_World.h"
#include "voxel/voxel_Chunk.h"
#include "voxel/voxel_WorldGen.h"

#include "voxel/voxel_WorldGenPass_Heightmap.h"
#include "voxel_ChunkManager.h"
#include "voxel/voxel_Region.h"
#include "voxel/voxel_WorldViewPort.h"
#include "voxel_RegionManager.h"
namespace ld3d
{
	namespace voxel
	{
		World::World(void)
		{
			m_worldBound = Bound(Coord(-0x10000000/2 * (int32)CHUNK_SIZE, -128 * (int32)CHUNK_SIZE, -0x10000000/2 * (int32)CHUNK_SIZE), 
								Coord((0x10000000/2 - 1) * CHUNK_SIZE, 127 * CHUNK_SIZE, (0x10000000/2 - 1) * CHUNK_SIZE));

		}


		World::~World(void)
		{
		}
		bool World::Initialize(WorldGenPtr pGen)
		{
			m_pChunkManager = std::make_shared<ChunkManager>();
			m_pRegionManager = std::make_shared<RegionManager>();
			if(m_pRegionManager->Initialize(shared_from_this()) == false)
			{
				return false;
			}
			m_pGen = pGen;

			m_pGen = std::make_shared<WorldGen>();

			m_pGen->Initialize();

			m_pGen->SetWorld(shared_from_this());


			m_pGen->AddPass(std::make_shared<WorldGenPass_Heightmap>());

		//	m_pGen->GenChunk(Coord(0, 0, 0));

			
			return true;
		}
		void World::Release()
		{
			m_pChunkManager->Clear();
			m_pChunkManager.reset();
			m_pRegionManager->Release();
			m_pRegionManager.reset();

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
		
		const std::list<ChunkPtr>& World::GetDirtyChunks() const
		{
			return m_pChunkManager->GetDirtyChunks();
		}
		void World::ClearDirtyChunks()
		{
			m_pChunkManager->ClearDirtyChunks();
		}
		
		void World::Update(float dt)
		{
			m_pRegionManager->Update();
		}
				
		ChunkManagerPtr	World::GetChunkManager()
		{
			return m_pChunkManager;
		}
		RegionManagerPtr World::GetRegionManager()
		{
			return m_pRegionManager;
		}

		Coord World::ToRegionOrigin(const Coord& c) const
		{
			Coord region_coord = ToRegionCoord(c);

			region_coord.x *= REGION_SIZE;
			region_coord.y *= REGION_HEIGHT;
			region_coord.z *= REGION_SIZE;

			return region_coord;
		}
		Coord World::ToRegionCoord(const Coord& c) const
		{
			int64 c_x = uint64(c.x) / (REGION_SIZE);
			int64 c_y = uint64(c.y) / (REGION_HEIGHT);
			int64 c_z = uint64(c.z) / (REGION_SIZE);
			
			return Coord(c_x, c_y, c_z);
		}
		Coord World::ToChunkOrigin(const Coord& c) const
		{
			Coord chunk_coord = ToChunkCoord(c);
			return chunk_coord * CHUNK_SIZE;

		}
		Coord World::ToChunkCoord(const Coord& c) const
		{
			int64 c_x = uint64(c.x) / (CHUNK_SIZE);
			int64 c_y = uint64(c.y) / (CHUNK_SIZE);
			int64 c_z = uint64(c.z) / (CHUNK_SIZE);
			
			return Coord(c_x, c_y, c_z);
		}
		WorldGenPtr World::GetWorldGen()
		{
			return m_pGen;
		}
		
	}
}


