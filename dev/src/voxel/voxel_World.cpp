#include "voxel_pch.h"

#include "voxel/voxel_World.h"
#include "voxel/voxel_Chunk.h"
#include "voxel/voxel_WorldGen.h"

#include "voxel/voxel_WorldGenPass_Heightmap.h"
#include "voxel_ChunkManager.h"
#include "voxel/voxel_Region.h"
#include "voxel/voxel_WorldViewPort.h"

namespace ld3d
{
	namespace voxel
	{
		World::World(void)
		{
			m_worldBound = Bound(Coord(-134217728 * (int32)CHUNK_SIZE, -128 * (int32)CHUNK_SIZE, -134217728 * (int32)CHUNK_SIZE), 
								Coord((134217728 - 1) * CHUNK_SIZE, 127 * CHUNK_SIZE, (134217728 - 1) * CHUNK_SIZE));
		}


		World::~World(void)
		{
		}
		bool World::Initialize(WorldGenPtr pGen)
		{
			m_pChunkManager = std::make_shared<ChunkManager>();

			m_pGen = pGen;

			m_pGen = std::make_shared<WorldGen>();

			m_pGen->Initialize();

			m_pGen->SetWorld(shared_from_this());


			m_pGen->AddPass(std::make_shared<WorldGenPass_Heightmap>());

			m_pGen->GenAll();

			
			return true;
		}
		void World::Release()
		{
			m_pChunkManager->Clear();
			m_pChunkManager.reset();

			m_viewPorts.clear();

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
			if(Inside(key.ToCoord()) == false)
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
		Coord World::ToChunkCoord(const Coord& c)
		{
			uint32 c_x = uint32(c.x / (CHUNK_SIZE * BLOCK_SIZE));
			uint32 c_y = uint8(c.y / (CHUNK_SIZE * BLOCK_SIZE));
			uint32 c_z = uint32(c.z / (CHUNK_SIZE * BLOCK_SIZE));

			return Coord(c_x, c_y, c_z);
		}
		Coord World::ToRegionCoord(const Coord& c)
		{
			uint32 c_x = uint32(c.x / (CHUNK_SIZE * BLOCK_SIZE * REGION_SIZE));
			uint32 c_y = uint8(c.y / (CHUNK_SIZE * BLOCK_SIZE * REGION_HEIGHT));
			uint32 c_z = uint32(c.z / (CHUNK_SIZE * BLOCK_SIZE * REGION_SIZE));

			return Coord(c_x, c_y, c_z);
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
		}
		WorldViewportPtr World::OpenViewport(const Coord& c, uint32 size)
		{
			WorldViewportPtr pVP = std::make_shared<WorldViewport>(shared_from_this());
			pVP->SetSize(size);
			pVP->MoveTo(c);

			m_viewPorts.push_back(pVP);
			return pVP;
		}
		void World::CloseViewport(WorldViewportPtr pViewport)
		{
			pViewport->Close();
			m_viewPorts.remove(pViewport);
		}
	}
}


