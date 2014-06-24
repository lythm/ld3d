#include "voxel_pch.h"
#include "voxel/voxel_ChunkAdjacency.h"
#include "voxel/voxel_Chunk.h"

namespace ld3d
{
	namespace voxel
	{
		ChunkAdjacency::ChunkAdjacency(const ChunkKey& key)
		{
			m_key = key;
			Reset();
		}
		ChunkAdjacency::ChunkAdjacency()
		{
			Reset();
		}
		ChunkAdjacency::~ChunkAdjacency(void)
		{
		}

		ChunkAdjacency::ChunkAdjacency(const ChunkAdjacency& other)
		{
			memcpy(m_blockAdjacency, other.m_blockAdjacency, sizeof(uint8) * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
			m_key = other.m_key;
			m_visible = other.m_visible;

		}
		void ChunkAdjacency::Reset()
		{
			m_visible = true;
			memset(m_blockAdjacency, 0, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
		}
		void ChunkAdjacency::SetBit(uint8& bits, uint32 pos, bool val)
		{
			if(val)
			{
				bits |= (1 << pos);
			}
			else
			{
				bits &= ~(1 << pos);
			}
		}
		bool ChunkAdjacency::GetBit(uint8 bits, uint32 pos) const 
		{
			return (bits & (1 << pos)) != 0;
		}
		void ChunkAdjacency::SetBlockAdjacency(int32 x, int32 y, int32 z, int32 v, bool val)
		{
			if(CheckCorrd(x, y, z) == false)
			{
				return;
			}
			int32 index = Chunk::ToIndex(x, y, z);
			SetBit(m_blockAdjacency[index], v, val);
		}

		void ChunkAdjacency::OnBlockChange(int32 x, int32 y, int32 z, bool val)
		{
			SetBlockAdjacency(x - 1, y, z, p_x, val != VT_EMPTY);
			SetBlockAdjacency(x + 1, y, z, n_x, val != VT_EMPTY);

			SetBlockAdjacency(x, y - 1, z, p_y, val != VT_EMPTY);
			SetBlockAdjacency(x, y + 1, z, n_y, val != VT_EMPTY);

			SetBlockAdjacency(x, y, z - 1, p_z, val != VT_EMPTY);
			SetBlockAdjacency(x, y, z + 1, n_z, val != VT_EMPTY);
		}

		bool ChunkAdjacency::CheckBlockAdjacency(int32 x, int32 y, int32 z, int32 neighbour) const
		{
			int32 index = Chunk::ToIndex(x, y, z);

			return GetBit(m_blockAdjacency[index], neighbour);
		}


		void ChunkAdjacency::OnAdjacentChunkLoaded(const Coord& chunk_coord, ChunkPtr pChunk)
		{
			const ChunkKey& this_key = m_key;

			Coord this_coord = this_key.ToChunkCoord();

			Coord dc = chunk_coord - this_coord;

			// nx
			if(dc.x == -1)
			{
				int32 x = 0;
				for(int32 z = 0; z < CHUNK_SIZE; ++z)
				{
					for(int32 y = 0; y < CHUNK_SIZE; ++y)
					{
						bool val = pChunk == nullptr? false : pChunk->GetBlock(CHUNK_SIZE - 1, y, z) != VT_EMPTY;
						SetBlockAdjacency(x, y, z, n_x, val);
					}
				}
			}
			//px
			if(dc.x == 1)
			{
				int32 x = CHUNK_SIZE - 1;
				for(int32 z = 0; z < CHUNK_SIZE; ++z)
				{
					for(int32 y = 0; y < CHUNK_SIZE; ++y)
					{
						bool val = pChunk == nullptr? false : pChunk->GetBlock(0, y, z) != VT_EMPTY;
						SetBlockAdjacency(x, y, z, p_x, val);
					}
				}
			}

			// ny
			if(dc.y == -1)
			{
				int32 y = 0;
				for(int32 z = 0; z < CHUNK_SIZE; ++z)
				{
					for(int32 x = 0; x < CHUNK_SIZE; ++x)
					{
						bool val = pChunk == nullptr? false : pChunk->GetBlock(x, CHUNK_SIZE - 1, z) != VT_EMPTY;
						SetBlockAdjacency(x, y, z, n_y, val);
					}
				}
			}
			//py
			if(dc.y == 1)
			{
				int32 y = CHUNK_SIZE - 1;
				for(int32 z = 0; z < CHUNK_SIZE; ++z)
				{
					for(int32 x = 0; x < CHUNK_SIZE; ++x)
					{
						bool val = pChunk == nullptr? false : pChunk->GetBlock(x, 0, z) != VT_EMPTY;
						SetBlockAdjacency(x, y, z, p_y, val);
					}
				}
			}

			// nz
			if(dc.z == -1)
			{
				int32 z = 0;
				for(int32 y = 0; y < CHUNK_SIZE; ++y)
				{
					for(int32 x = 0; x < CHUNK_SIZE; ++x)
					{
						bool val = pChunk == nullptr? false : pChunk->GetBlock(x, y, CHUNK_SIZE - 1) != VT_EMPTY;
						SetBlockAdjacency(x, y, z, n_z, val);
					}
				}
			}
			//pz
			if(dc.z == 1)
			{
				int32 z = CHUNK_SIZE - 1;
				for(int32 y = 0; y < CHUNK_SIZE; ++y)
				{
					for(int32 x = 0; x < CHUNK_SIZE; ++x)
					{
						bool val = pChunk == nullptr? false : pChunk->GetBlock(x, y, 0) != VT_EMPTY;
						SetBlockAdjacency(x, y, z, p_z, val);
					}
				}
			}

			m_visible = CheckVisiblity();
		}

		bool ChunkAdjacency::CheckCorrd(int32 x, int32 y, int32 z)
		{
			return (x >= 0 && x < CHUNK_SIZE) && ( y >= 0 && y < CHUNK_SIZE) && (z >= 0 && z < CHUNK_SIZE);
		}
		bool ChunkAdjacency::IsVisible() const
		{
			return m_visible;
		}
		bool ChunkAdjacency::CheckVisiblity() const
		{
			// nx
			for(int32 z = 0; z < CHUNK_SIZE; ++z)
			{
				for(int32 y = 0; y < CHUNK_SIZE; ++y)
				{
					if(CheckBlockAdjacency(0, y, z, n_x) == false)
					{
						return true;
					}
				}
			}
			//px
			for(int32 z = 0; z < CHUNK_SIZE; ++z)
			{
				for(int32 y = 0; y < CHUNK_SIZE; ++y)
				{
					if(CheckBlockAdjacency(CHUNK_SIZE - 1, y, z, p_x) == false)
					{
						return true;
					}
				}
			}

			// ny
			for(int32 z = 0; z < CHUNK_SIZE; ++z)
			{
				for(int32 x = 0; x < CHUNK_SIZE; ++x)
				{
					if(CheckBlockAdjacency(x, 0, z, n_y) == false)
					{
						return true;
					}
				}
			}

			// py
			for(int32 z = 0; z < CHUNK_SIZE; ++z)
			{
				for(int32 x = 0; x < CHUNK_SIZE; ++x)
				{
					if(CheckBlockAdjacency(x, CHUNK_SIZE - 1, z, p_y) == false)
					{
						return true;
					}
				}
			}

			// nz
			for(int32 y = 0; y < CHUNK_SIZE; ++y)
			{
				for(int32 x = 0; x < CHUNK_SIZE; ++x)
				{
					if(CheckBlockAdjacency(x, y, 0, n_z) == false)
					{
						return true;
					}
				}
			}

			// pz
			for(int32 y = 0; y < CHUNK_SIZE; ++y)
			{
				for(int32 x = 0; x < CHUNK_SIZE; ++x)
				{
					if(CheckBlockAdjacency(x, y, CHUNK_SIZE - 1, p_z) == false)
					{
						return true;
					}
				}
			}

			return false;
		}
	}
}
