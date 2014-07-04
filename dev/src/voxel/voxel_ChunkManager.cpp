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

			bool loaded = false;
			ChunkPtr pChunk = FindChunk(key, loaded);
			if(loaded == false)
			{
				return false;
			}

			pChunk = CreateChunk(key, ChunkData());
			AddChunk(pChunk);

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
		bool ChunkManager::AddChunk(const ChunkKey& chunk_key, ChunkPtr pChunk)
		{
			uint64 key = chunk_key.AsUint64();

			auto it = m_chunkmap.find(key);
			if(it != m_chunkmap.end())
			{
				return false;
			}
			m_chunkmap[key] = pChunk;

			if(pChunk && pChunk->IsDirty())
			{
				m_dirtyList.push_back(pChunk);
			}

			return true;
		}
		bool ChunkManager::AddChunk(ChunkPtr pChunk)
		{
			uint64 key = pChunk->GetKey().AsUint64();

			AddChunk(key, pChunk);

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

			bool loaded = false;
			ChunkPtr pChunk = FindChunk(key, loaded);

			return pChunk ? pChunk->GetBlock((c - key.ToChunkOrigin())) : VT_EMPTY;

		}
		ChunkPtr ChunkManager::FindChunk(const ChunkKey& key, bool& loaded)
		{
			auto it = m_chunkmap.find(key.AsUint64());

			loaded = (it != m_chunkmap.end());

			return it == m_chunkmap.end() ? nullptr : it->second;
		}

		void ChunkManager::UpdateBlock(const Coord& c)
		{
			bool loaded = false;
			ChunkPtr pChunk = FindChunk(ChunkKey(c), loaded);

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
		void ChunkManager::PickChunk(const Coord& center, uint32 radius, uint32 height, const std::function<void(const ChunkKey&)>& op)
		{
			int32 dx = radius * 2 / CHUNK_SIZE;
			int32 dz = radius * 2 / CHUNK_SIZE;
			int32 dy = height;

			Coord ch_center = center / CHUNK_SIZE;


			Spiral(dx, dz, [&](int32 x, int32 z)
			{
				if((x * x + z * z) >= radius / CHUNK_SIZE * radius / CHUNK_SIZE)
				{
					return;
				}

				for(int32 y = dy / 2; y >= -dy / 2; --y)
				{
					Coord c(x, y, z);
					c += ch_center;

					ChunkKey key;
					key.FromChunkCoord(c);
					op(key);
				}
			});

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

		void ChunkManager::PickChunkSliceCylinder(int32 sy, const Coord& center, uint32 radius, const std::function<void(const ChunkKey&)>& op)
		{
			float r = radius;//sqrtf((float(radius * radius) - float(sy * sy)));

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
		void ChunkManager::PickChunkDiffSet(const Coord& center, uint32 radius, uint32 height, const Coord& refer_center, uint32 refer_radius, uint32 refer_height, const std::function<void(const ChunkKey&)>& op)
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

			height /= 2;
			height /= CHUNK_SIZE;
			radius /= CHUNK_SIZE;


			for(int y = 0; y <= (int32)height; ++y)
				//for(int32 y = -(int32)height; y <= (int32)height; ++y)
			{
				PickChunkDiffSetSliceCylinder(y, VoxelUtils::ToChunkOrigin(center), radius, height, VoxelUtils::ToChunkOrigin(refer_center), refer_radius,  refer_height, op);
				PickChunkDiffSetSliceCylinder(-y, VoxelUtils::ToChunkOrigin(center), radius, height, VoxelUtils::ToChunkOrigin(refer_center), refer_radius,  refer_height, op);
			}
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
		void ChunkManager::PickChunkDiffSetSliceCylinder(int32 sy, const Coord& center, uint32 radius, uint32 height, const Coord& refer_center, uint32 refer_radius, uint32 refer_height, const std::function<void(const ChunkKey&)>& op)
		{
			float r = radius;//sqrtf(float(radius * radius) - float(sy * sy));

			for(int32 z = 0; z <= (int32)r; ++z)
				//for(int32 z = -(int32)r; z <= (int32)r; ++z)
			{
				float x_abs = sqrtf(r * r - z * z);

				for(int32 x = 0; x <= (int32)x_abs; ++x)
					//for(int32 x = -(int32)x_abs; x <= (int32)x_abs; ++x)
				{
					Coord c = Coord(x, sy, z) + center / CHUNK_SIZE;
					c *= CHUNK_SIZE;

					if(InCylinder(c, refer_center, refer_radius, refer_height) == false)
					{
						ChunkKey key(c);
						op(key);
					}

					c = Coord(-x, sy, z) + center / CHUNK_SIZE;
					c *= CHUNK_SIZE;

					if(InCylinder(c, refer_center, refer_radius, refer_height) == false)
					{
						ChunkKey key(c);
						op(key);
					}
				}


				for(int32 x = 0; x <= (int32)x_abs; ++x)
					//for(int32 x = -(int32)x_abs; x <= (int32)x_abs; ++x)
				{
					Coord c = Coord(x, sy, -z) + center / CHUNK_SIZE;
					c *= CHUNK_SIZE;

					if(InCylinder(c, refer_center, refer_radius, refer_height) == false)
					{
						ChunkKey key(c);
						op(key);
					}

					c = Coord(-x, sy, -z) + center / CHUNK_SIZE;
					c *= CHUNK_SIZE;

					if(InCylinder(c, refer_center, refer_radius, refer_height) == false)
					{
						ChunkKey key(c);
						op(key);
					}
				}
			}
		}
		bool ChunkManager::InCylinder(const Coord& c, const Coord& center, uint32 radius, uint32 height)
		{
			Coord rc = c - center;

			rc /= CHUNK_SIZE;

			height /= 2;
			height /= CHUNK_SIZE;
			radius = radius / CHUNK_SIZE;

			if(rc.y >= -(int32)height && rc.y <= (int32)height)
			{
				float r = radius;//sqrtf(float(radius * radius) - float(rc.y * rc.y));

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

		void ChunkManager::PickAdjacentChunks(const ChunkKey& key, const std::function<void(const ChunkKey&, ChunkPtr, bool)>& op)
		{
			Coord this_coord = key.ToChunkCoord();

			ChunkPtr pChunk;
			ChunkKey chunk_key;
			bool loaded = false;
			chunk_key.FromChunkCoord(this_coord + Coord(-1, 0, 0));
			pChunk = FindChunk(chunk_key, loaded);
			op(chunk_key, pChunk, loaded);

			chunk_key.FromChunkCoord(this_coord + Coord(+1, 0, 0));
			pChunk = FindChunk(chunk_key, loaded);
			op(chunk_key, pChunk, loaded);

			chunk_key.FromChunkCoord(this_coord + Coord(0, -1, 0));
			pChunk = FindChunk(chunk_key, loaded);
			op(chunk_key, pChunk, loaded);

			chunk_key.FromChunkCoord(this_coord + Coord(0, +1, 0));
			pChunk = FindChunk(chunk_key, loaded);
			op(chunk_key, pChunk, loaded);

			chunk_key.FromChunkCoord(this_coord + Coord(0, 0, -1));
			pChunk = FindChunk(chunk_key, loaded);
			op(chunk_key, pChunk, loaded);

			chunk_key.FromChunkCoord(this_coord + Coord(0, 0, +1));
			pChunk = FindChunk(chunk_key, loaded);
			op(chunk_key, pChunk, loaded);

		}

		void ChunkManager::PickSurroundingChunks(const ChunkKey& key, const std::function<void(const ChunkKey& , ChunkPtr, bool)>& op)
		{
			Coord this_coord = key.ToChunkCoord();

			ChunkPtr pChunk;
			ChunkKey chunk_key;

			for(int x = -1; x <= 1; ++x)
			{

				for(int y = -1; y <= 1; ++y)
				{
					for(int z = -1; z <= 1; ++z)
					{
						if(x == 0 && y == 0 && z == 0)
						{
							continue;
						}

						bool loaded = false;
						chunk_key.FromChunkCoord(this_coord + Coord(x, y, z));
						pChunk = FindChunk(chunk_key, loaded);
						op(chunk_key, pChunk, loaded);
					}
				}
			}
		}


		void ChunkManager::PickChunk(const Bound& bound, const std::function<void(const ChunkKey&)>& op)
		{
			Coord min_coord = bound.GetMinCoord();
			Coord max_coord = bound.GetMaxCoord();

			min_coord /= CHUNK_SIZE;
			max_coord /= CHUNK_SIZE;

			int32 dx = max_coord.x - min_coord.x;
			int32 dz = max_coord.z - min_coord.z;
			int32 dy = max_coord.y - min_coord.y;

			Coord center = (max_coord + min_coord) / 2;


			Spiral(dx, dz, [&](int32 x, int32 z)
			{
				for(int32 y = dy / 2; y >= -dy / 2; --y)
				{
					Coord c(x, y, z);
					c += center;

					ChunkKey key;
					key.FromChunkCoord(c);
					op(key);
				}
			});
		}
		void ChunkManager::PickChunkSubtract(const Bound& bound, const Bound& refer_bound, const std::function<void(const ChunkKey&)>& op)
		{
			Coord min_coord = bound.GetMinCoord();
			Coord max_coord = bound.GetMaxCoord();

			min_coord /= CHUNK_SIZE;
			max_coord /= CHUNK_SIZE;

			int32 dx = max_coord.x - min_coord.x;
			int32 dz = max_coord.z - min_coord.z;
			int32 dy = max_coord.y - min_coord.y;

			Coord center = (max_coord + min_coord) / 2;


			Coord r_min_coord = refer_bound.GetMinCoord();
			Coord r_max_coord = refer_bound.GetMaxCoord();

			r_min_coord /= CHUNK_SIZE;
			r_max_coord /= CHUNK_SIZE;

			Bound r_bound(r_min_coord, r_max_coord);
			
			Spiral(dx, dz, [&](int32 x, int32 z)
			{
				for(int32 y = -dy / 2; y <= dy / 2; ++y)
				{
					Coord c(x, y, z);
					c += center;

					if(r_bound.Inside(c))
					{
						continue;
					}

					ChunkKey key;
					key.FromChunkCoord(c);
					op(key);
				}
			});
		}
		void ChunkManager::Spiral(uint32 w, uint32 h, const std::function<void(int32, int32)>& op)
		{
			int x		= 0;
			int y		= 0;
			int dx		= 0;
			int dy		= -1;
			
			int t = std::max(w , h);
			int maxI = t * t;
			for(int i = 0; i < maxI; i++)
			{
				if (abs(x) <= w / 2 && abs(y) <= h / 2)
				{
					op(x, y);
					// DO STUFF...
				}
				if( (x == y) || ((x < 0) && (x == -y)) || ((x > 0) && (x == 1 - y)))
				{
					t = dx;
					dx = -dy;
					dy = t;
				}
				x += dx;
				y += dy;
			}
		}
	}
}
