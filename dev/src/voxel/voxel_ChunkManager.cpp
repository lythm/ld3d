#include "voxel_pch.h"
#include "voxel_ChunkManager.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_PoolManager.h"

namespace ld3d
{
	namespace voxel
	{
		ChunkManager::ChunkManager(void) : m_chunkmap(GetAllocator())
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
				pChunk = CreateChunk(key, nullptr);
				AddChunk(pChunk);
			}

			if(pChunk->IsDirty() == false)
			{
				m_dirtyList.push_back(pChunk);
			}
			pChunk->SetBlock(c - key.ToChunkOrigin(), type);
			return true;
		}
		ChunkPtr ChunkManager::CreateChunk(const ChunkKey& key, uint8 data[])
		{
			ChunkPtr pChunk = AllocChunk(data);
			pChunk->SetKey(key);

			return pChunk;
		}
		bool ChunkManager::AddChunk(ChunkPtr pChunk)
		{
			uint64 key = pChunk->GetKey().AsUint64();

			auto it = m_chunkmap.find(key);
			if(it != m_chunkmap.end())
			{
				return false;
			}
			m_chunkmap[key] = pChunk;

			if(pChunk->IsDirty())
			{
				m_dirtyList.push_back(pChunk);
			}
			return true;
		}
		bool ChunkManager::RemoveBlock(const Coord& c)
		{
			return ReplaceBlock(c, VT_EMPTY);
		}
		bool ChunkManager::IsEmpty(const Coord& c)
		{
			if(GetBlock(c) == VT_EMPTY)
			{
				return true;
			}

			return false;

			//return GetBlock(c) == VT_EMPTY;
		}
		uint8 ChunkManager::GetBlock(const Coord& c)
		{
			ChunkKey key(c);

			ChunkPtr pChunk = FindChunk(key);
			
			return pChunk ? pChunk->GetBlock((c - key.ToChunkOrigin())) : VT_EMPTY;

		}
		ChunkPtr ChunkManager::FindChunk(const ChunkKey& key)
		{
			auto it = m_chunkmap.find(key.AsUint64());

			return it == m_chunkmap.end() ? nullptr : it->second;
		}
		ChunkPtr ChunkManager::AllocChunk(uint8 data[])
		{
			return GetPoolManager()->AllocChunk(shared_from_this(), data);


			//if(GetAllocator() != nullptr)
			//{
			//	return std::allocate_shared<Chunk, std_allocator_adapter<Chunk> >(GetAllocator(), shared_from_this(), data);
			//}
			//return std::make_shared<Chunk>(shared_from_this(), data);
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
		void ChunkManager::RemoveChunk(const ChunkKey& key)
		{
			auto it = m_chunkmap.find(key.AsUint64());

			if(it == m_chunkmap.end())
			{
				return;
			}

			m_chunkmap.erase(it);

		}
		void ChunkManager::Update(float dt)
		{
			for(auto chunk : m_dirtyList)
			{
				for(auto handler : m_dirtyChunkHandlers)
				{
					handler(chunk);
				}
			}
			
			ClearDirtyChunks();
		}
		void ChunkManager::AddDirtyChunkHandler(const std::function<void (ChunkPtr)>& handler)
		{
			m_dirtyChunkHandlers.push_back(handler);
		}
		uint32 ChunkManager::GetChunkCount() const
		{
			return (uint32)m_chunkmap.size();
		}
		void ChunkManager::PickChunk(const Coord& center, uint32 radius, const std::function<void(const ChunkKey&, ChunkPtr)>& op)
		{
			if(op == nullptr)
			{
				return;
			}

			for(int32 y = -(int32)radius; y <= (int32)radius; y += CHUNK_SIZE)
			{
				int32 r = sqrtf(float(radius * radius) - float(y * y));
				
				PickChunkSlice_XZ(Coord(center.x, center.y + y, center.z), r, op);

			}
		}
		void ChunkManager::PickChunkSlice_XZ(const Coord& center, uint32 radius, const std::function<void(const ChunkKey&, ChunkPtr)>& op)
		{
			for(int32 z = -(int32)radius; z <= (int32)radius; z += CHUNK_SIZE)
			{
				int32 x_abs = sqrtf(float(radius * radius) - float(z * z));

				for(int32 x = -x_abs; x <= x_abs; x+= CHUNK_SIZE)
				{
					ChunkKey key(Coord(x, 0, z) + center);

					ChunkPtr pChunk = FindChunk(key);
					op(key, pChunk);
				}
			}
		}
		void ChunkManager::PickChunkDiff(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius, const std::function<void(ChunkPtr)>& op)
		{
			//if((center - refer_center).Length() > (radius + refer_radius))
			//{
			//	PickChunk(center, radius, op);
			//	return;
			//}

			//for(int32 y = -(int32)radius; y <= (int32)radius; y += CHUNK_SIZE)
			//{
			//	int32 r_xz = sqrtf(float(radius * radius) - float(y * y));
			//	int32 rr_xz = sqrtf(float(refer_radius * refer_radius) - float(y * y));


			//	for(int32 z = -r_xz; z <= r_xz; z += CHUNK_SIZE)
			//	{
			//		//for(int x = 
			//	}
			//}

		}
	}
}
