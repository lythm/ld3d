#include "voxel_pch.h"
#include "voxel_ChunkManager.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_PoolManager.h"
#include "voxel_VoxelUtils.h"


namespace ld3d
{
	namespace voxel
	{
		ChunkManager::ChunkManager(void) : m_chunkmap(allocator()), m_dirtyList(allocator())
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
				pChunk = CreateChunk(key, ChunkData());
				AddChunk(pChunk);
			}

			if(pChunk->IsDirty() == false)
			{
				m_dirtyList.push_back(pChunk);
			}
			pChunk->SetBlock(c - key.ToChunkOrigin(), type);
			return true;
		}
		ChunkPtr ChunkManager::CreateChunk(const ChunkKey& key, const ChunkData& data)
		{
			ChunkPtr pChunk = pool_manager()->AllocChunk(shared_from_this(), key, data);

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
		
		void ChunkManager::UpdateBlock(const Coord& c)
		{
			ChunkPtr pChunk = FindChunk(ChunkKey(c));

			pChunk ? pChunk->Update() : void(0);

		}
		const ChunkManager::DirtyChunkList& ChunkManager::GetDirtyChunks() const
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
		void ChunkManager::RemoveChunk(ChunkPtr pChunk)
		{
			RemoveChunk(pChunk->GetKey());
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
		
		void ChunkManager::PickChunk(const Coord& center, uint32 radius, const std::function<void(const ChunkKey&)>& op)
		{
			if(op == nullptr)
			{
				return;
			}

			radius /= CHUNK_SIZE;

			for(int32 y = -(int32)radius; y <= (int32)radius; ++y)
			{
				PickChunkSlice(y, VoxelUtils::ToChunkOrigin(center), radius, op);
			}
		}
		void ChunkManager::PickChunkSlice(int32 sy, const Coord& center, uint32 radius, const std::function<void(const ChunkKey&)>& op)
		{
			float r = sqrtf((float(radius * radius) - float(sy * sy)));

			for(int32 z = -(int32)r; z <= (int32)r; ++z)
			{
				float x_abs = sqrtf(r * r - z * z);

				for(int32 x = -(int32)x_abs; x <= (int32)x_abs; ++x)
				{
					Coord c = Coord(x, sy, z) + center / CHUNK_SIZE;
					ChunkKey key(c * CHUNK_SIZE);

					op(key);
				}
			}
		}

		void ChunkManager::PickChunkDiffSet1(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius, const std::function<void(const ChunkKey&)>& op)
		{
			if(op == nullptr)
			{
				return;
			}

			std::vector<ChunkKey> keys;

			PickChunk(refer_center, refer_radius, [&](const ChunkKey& key)
			{
				keys.push_back(key);
			});

			PickChunk(center, radius, [&](const ChunkKey& key)
			{
				if(std::find(keys.begin(), keys.end(), key) == keys.end())
				{
					op(key);
				}

			});
		}
		void ChunkManager::PickChunkDiffSet(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius, const std::function<void(const ChunkKey&)>& op)
		{
			if(op == nullptr)
			{
				return;
			}

			/*if((center - refer_center).Length() > (radius + refer_radius))
			{
				PickChunk(center, radius, op);
				return;
			}*/

			radius /= CHUNK_SIZE;

			for(int32 y = -(int32)radius; y <= (int32)radius; ++y)
			{
				PickChunkDiffSetSlice(y, VoxelUtils::ToChunkOrigin(center), radius, VoxelUtils::ToChunkOrigin(refer_center), refer_radius,  op);
			}
		}
		void ChunkManager::PickChunkDiffSetSlice(int32 sy, const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius, const std::function<void(const ChunkKey&)>& op)
		{
			float r = sqrtf(float(radius * radius) - float(sy * sy));

			for(int32 z = -(int32)r; z <= (int32)r; ++z)
			{
				float x_abs = sqrtf(r * r - z * z);

				for(int32 x = -(int32)x_abs; x <= (int32)x_abs; ++x)
				{
					Coord c = Coord(x, sy, z) + center / CHUNK_SIZE;
					c *= CHUNK_SIZE;

					if(InSphere(c, refer_center, refer_radius))
					{
						continue;
					}

					ChunkKey key(c);
					op(key);
				}
			}
		}
		bool ChunkManager::InSphere(const Coord& c, const Coord& center, uint32 radius)
		{
			Coord rc = c - center;

			rc /= CHUNK_SIZE;

			radius = radius / CHUNK_SIZE;

			if(rc.y >= -(int32)radius && rc.y <= (int32)radius)
			{
				float r = sqrtf(float(radius * radius) - float(rc.y * rc.y));
				
				if(rc.z >=-r && rc.z <= r)
				{
					float x_abs = sqrtf(r * r - rc.z * rc.z);

					if(rc.x >= -(int32)x_abs&& rc.x <= (int32)x_abs)
					{
						return true;
					}
				}
			}

			return false;

		}

		void ChunkManager::PickAdjacentChunks(const ChunkKey& key, const std::function<void(const ChunkKey&, ChunkPtr)>& op)
		{
			Coord this_coord = key.ToChunkCoord();

			ChunkPtr pChunk;
			ChunkKey chunk_key;

			chunk_key.FromChunkCoord(this_coord + Coord(-1, 0, 0));
			pChunk = FindChunk(chunk_key);
			op(chunk_key, pChunk);

			chunk_key.FromChunkCoord(this_coord + Coord(+1, 0, 0));
			pChunk = FindChunk(chunk_key);
			op(chunk_key, pChunk);

			chunk_key.FromChunkCoord(this_coord + Coord(0, -1, 0));
			pChunk = FindChunk(chunk_key);
			op(chunk_key, pChunk);

			chunk_key.FromChunkCoord(this_coord + Coord(0, +1, 0));
			pChunk = FindChunk(chunk_key);
			op(chunk_key, pChunk);

			chunk_key.FromChunkCoord(this_coord + Coord(0, 0, -1));
			pChunk = FindChunk(chunk_key);
			op(chunk_key, pChunk);

			chunk_key.FromChunkCoord(this_coord + Coord(0, 0, +1));
			pChunk = FindChunk(chunk_key);
			op(chunk_key, pChunk);

		}

	}
}
