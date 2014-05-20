#include "voxel_world_pch.h"

#include "voxel_world/World.h"
#include "voxel_world/Chunk.h"

namespace ld3d
{
	namespace voxel
	{
		World::World(void)
		{
			m_worldSize = Coord(200 * 1024, 1024, 200 * 1024);

		}


		World::~World(void)
		{
		}
		bool World::Initialize(WorldGenPtr pGen)
		{
			m_pGen = pGen;

			Coord c(1, 17, 0xffffffe);

			ChunkKey k(c);

			Coord kk = k.ToCoord();



			AddBlock(c, 1);
			uint8 t = GetBlock(c);
			return true;
		}
		void World::Release()
		{
		}
		bool World::AddBlock(const Coord& c, uint8 type)
		{
			if(IsEmpty(c) == false)
			{
				return false;
			}

			ReplaceBlock(c, type);

			return true;
		}
		void World::ReplaceBlock(const Coord& c, uint8 type)
		{
			ChunkKey key(c);

			ChunkPtr pChunk = FindChunk(key);

			if(pChunk == nullptr)
			{
				pChunk = AllocChunk();
				pChunk->SetKey(key);
				m_chunkmap[key.AsUint64()] = pChunk;
			}

			pChunk->SetBlock(c - key.ToCoord(), type);

		}
		void World::RemoveBlock(const Coord& c)
		{
			ReplaceBlock(c, VT_EMPTY);
		}
		bool World::IsEmpty(const Coord& c)
		{
			return GetBlock(c) == VT_EMPTY;
		}
		uint8 World::GetBlock(const Coord& c)
		{
			ChunkKey key(c);

			ChunkPtr pChunk = FindChunk(key);
			
			return pChunk ? pChunk->GetBlock((c - key.ToCoord())) : VT_EMPTY;

		}
		ChunkPtr World::FindChunk(const ChunkKey& key)
		{
			auto it = m_chunkmap.find(key.AsUint64());

			return it == m_chunkmap.end() ? nullptr : it->second;
		}
		ChunkPtr World::AllocChunk()
		{
			return std::make_shared<Chunk>();
		}
		void World::UpdateBlock(const Coord& c)
		{
			ChunkPtr pChunk = FindChunk(ChunkKey(c));

			pChunk ? pChunk->Update() : void(0);

		}
		bool World::InWorld(const Coord& c) const
		{
			if((c.x < -m_worldSize.x / 2) || (c.x > m_worldSize.x / 2))
			{
				return false;
			}

			if((c.y < -m_worldSize.y / 2) || (c.y > m_worldSize.y / 2))
			{
				return false;
			}

			if((c.z < -m_worldSize.z / 2) || (c.z > m_worldSize.z / 2))
			{
				return false;
			}

			return true;
		}
	}
}

