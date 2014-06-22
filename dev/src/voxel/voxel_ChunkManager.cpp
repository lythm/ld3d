#include "voxel_pch.h"
#include "voxel_ChunkManager.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_PoolManager.h"

namespace ld3d
{
	namespace voxel
	{
		ChunkManager::ChunkManager(void) : m_chunkmap(GetAllocator()), m_dirtyList(GetAllocator())
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
		void ChunkManager::UpdateChunkNeighbour(ChunkPtr pChunk)
		{

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
		/*void ChunkManager::PickChunk(const Coord& center, uint32 radius, const std::function<void(const ChunkKey&, ChunkPtr)>& op)
		{
			if(op == nullptr)
			{
				return;
			}

			int32 round = radius / CHUNK_SIZE * CHUNK_SIZE;

			for(int32 y = -(int32)round; y <= (int32)round; y += CHUNK_SIZE)
			{
				PickChunkSlice(y, center, radius, op);
			}
		}
		void ChunkManager::PickChunkSlice(int32 sy, const Coord& center, uint32 radius, const std::function<void(const ChunkKey&, ChunkPtr)>& op)
		{
			int32 r = sqrtf(float(radius * radius) - float(sy * sy));
			int32 round_z = r / CHUNK_SIZE * CHUNK_SIZE;

			for(int32 z = -(int32)round_z; z <= (int32)round_z; z += CHUNK_SIZE)
			{
				int32 x_abs = sqrtf(float(r * r) - float(z * z));

				int32 round_x = x_abs / CHUNK_SIZE * CHUNK_SIZE;

				for(int32 x = -round_x; x <= round_x; x+= CHUNK_SIZE)
				{
					ChunkKey key(Coord(x, sy, z) + center);

					ChunkPtr pChunk = FindChunk(key);
					op(key, pChunk);
				}
			}
		}*/

		void ChunkManager::PickChunk(const Coord& center, uint32 radius, const std::function<void(const ChunkKey&, ChunkPtr)>& op)
		{
			if(op == nullptr)
			{
				return;
			}

			radius /= CHUNK_SIZE;

			for(int32 y = -(int32)radius; y <= (int32)radius; ++y)
			{
				PickChunkSlice(y, center, radius, op);
			}
		}
		void ChunkManager::PickChunkSlice(int32 sy, const Coord& center, uint32 radius, const std::function<void(const ChunkKey&, ChunkPtr)>& op)
		{
			float r = sqrtf(radius * radius - sy * sy);

			for(int32 z = -r; z <= r; ++z)
			{
				float x_abs = sqrtf(r * r - z * z);

				for(int32 x = -x_abs; x <= x_abs; ++x)
				{
					Coord c = Coord(x, sy, z) + center / CHUNK_SIZE;
					ChunkKey key(c * CHUNK_SIZE);

					ChunkPtr pChunk = FindChunk(key);
					op(key, pChunk);
				}
			}
		}

		void ChunkManager::PickChunkDiffSet1(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius, const std::function<void(const ChunkKey&, ChunkPtr)>& op)
		{
			if(op == nullptr)
			{
				return;
			}

			std::vector<ChunkKey> keys;

			PickChunk(refer_center, refer_radius, [&](const ChunkKey& key, ChunkPtr pChunk)
			{
				keys.push_back(key);
			});

			PickChunk(center, radius, [&](const ChunkKey& key, ChunkPtr pChunk)
			{
				if(std::find(keys.begin(), keys.end(), key) == keys.end())
				{
					op(key, pChunk);
				}

			});
		}
		void ChunkManager::PickChunkDiffSet(const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius, const std::function<void(const ChunkKey&, ChunkPtr)>& op)
		{
			if(op == nullptr)
			{
				return;
			}

			if((center - refer_center).Length() > (radius + refer_radius))
			{
				PickChunk(center, radius, op);
				return;
			}

			radius /= CHUNK_SIZE;

			for(int32 y = -(int32)radius; y <= (int32)radius; ++y)
			{
				PickChunkDiffSetSlice(y, center, radius, refer_center, refer_radius,  op);
			}
		}
		void ChunkManager::PickChunkDiffSetSlice(int32 sy, const Coord& center, uint32 radius, const Coord& refer_center, uint32 refer_radius, const std::function<void(const ChunkKey&, ChunkPtr)>& op)
		{
			float r = sqrtf(radius * radius - sy * sy);

			for(int32 z = -r; z <= r; ++z)
			{
				float x_abs = sqrtf(r * r - z * z);

				for(int32 x = -x_abs; x <= x_abs; ++x)
				{
					Coord c = Coord(x, sy, z) + center / CHUNK_SIZE;
					c *= CHUNK_SIZE;

					if(InSphere(c, refer_center, refer_radius))
					{
						continue;
					}

					ChunkKey key(c);

					ChunkPtr pChunk = FindChunk(key);
					op(key, pChunk);
				}
			}
		}
		bool ChunkManager::InSphere(const Coord& c, const Coord& center, uint32 radius)
		{
			Coord rc = c - center;

			rc /= CHUNK_SIZE;

			radius = radius / CHUNK_SIZE;

			if(rc.y >= -radius && rc.y <= radius)
			{
				float r = sqrtf(radius * radius - rc.y * rc.y);
				
				if(rc.z >=-r && rc.z <= r)
				{
					float x_abs = sqrtf(r * r - rc.z * rc.z);

					if(rc.x >= -x_abs&& rc.x <= x_abs)
					{
						return true;
					}
				}
			}

			return false;

		}
	}
}
