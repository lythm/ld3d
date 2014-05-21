#include "voxel_pch.h"
#include "voxel_ChunkManager.h"
#include "voxel/voxel_Chunk.h"

namespace ld3d
{
	namespace voxel
	{
		ChunkManager::ChunkManager(void)
		{
		}


		ChunkManager::~ChunkManager(void)
		{
		}
		bool ChunkManager::AddBlock(const Coord& c, uint8 type)
		{
			return ReplaceBlock(c, type);
		}
		bool ChunkManager::ReplaceBlock(const Coord& c, uint8 type)
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
			pChunk->SetDirty(true);
			m_dirtyList.push_back(pChunk);
			return true;
		}
		bool ChunkManager::RemoveBlock(const Coord& c)
		{
			return ReplaceBlock(c, VT_EMPTY);
		}
		bool ChunkManager::IsEmpty(const Coord& c)
		{
			return GetBlock(c) == VT_EMPTY;
		}
		uint8 ChunkManager::GetBlock(const Coord& c)
		{
			ChunkKey key(c);

			ChunkPtr pChunk = FindChunk(key);
			
			return pChunk ? pChunk->GetBlock((c - key.ToCoord())) : VT_EMPTY;

		}
		ChunkPtr ChunkManager::FindChunk(const ChunkKey& key)
		{
			auto it = m_chunkmap.find(key.AsUint64());

			return it == m_chunkmap.end() ? nullptr : it->second;
		}
		ChunkPtr ChunkManager::AllocChunk()
		{
			return std::make_shared<Chunk>();
		}
		void ChunkManager::UpdateBlock(const Coord& c)
		{
			ChunkPtr pChunk = FindChunk(ChunkKey(c));

			pChunk ? pChunk->Update() : void(0);

		}
		const std::list<ChunkPtr>& ChunkManager::GetDirtyChunks() const
		{
			return m_dirtyList;
		}
		void ChunkManager::ClearDirtyChunks()
		{
			for(auto ch : m_dirtyList)
			{
				ch->SetDirty(false);
			}
			m_dirtyList.clear();
		}
		void ChunkManager::Clear()
		{
			ClearDirtyChunks();
			m_chunkmap.clear();
		}
	}
}