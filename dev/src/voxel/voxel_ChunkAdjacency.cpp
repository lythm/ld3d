#include "voxel_pch.h"
#include "voxel/voxel_ChunkAdjacency.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_VoxelUtils.h"

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
			m_key = other.m_key;
			m_visible = other.m_visible;
			m_blocks = other.m_blocks;

		}
		void ChunkAdjacency::Reset()
		{
			m_visible = true;
			m_blocks.reset();
			m_adj.set(1 * 3 * 3 + 1 * 3 + 1);
		}
		
		void ChunkAdjacency::OnBlockChange(int32 x, int32 y, int32 z, bool val)
		{
			int32 index = ToIndex(x, y, z);
			m_blocks.set(index, val);
		}
		Coord ChunkAdjacency::ToAdjacentBlockCoord(const Coord& c, uint32 adj) const
		{
			Coord ac = c;

			adj & n_x ? --ac.x : void(0);
			adj & p_x ? ++ac.x : void(0);

			adj & n_y ? --ac.y : void(0);
			adj & p_y ? ++ac.y : void(0);

			adj & n_z ? --ac.z : void(0);
			adj & p_z ? ++ac.z : void(0);

			return ac;

		}
		bool ChunkAdjacency::CheckBlock(int32 x, int32 y, int32 z) const
		{
			int32 index = ToIndex(x, y, z);
			if(index == -1)
			{
				return false;
			}

			return m_blocks.at(index);
		}
		bool ChunkAdjacency::CheckBlockAdjacency(int32 x, int32 y, int32 z, int32 neighbour) const
		{
			Coord c = ToAdjacentBlockCoord(Coord(x, y, z), neighbour);

			int32 index = ToIndex(c.x, c.y, c.z);
			if(index == -1)
			{
				return true;
			}
			return m_blocks.at(index);
		}
	
		
		void ChunkAdjacency::UpdateChunkAdjacency(const ChunkKey& key, ChunkPtr pChunk)
		{

			Coord this_coord = m_key.ToChunkCoord();
			Coord chunk_coord = key.ToChunkCoord();

			Coord dc = chunk_coord - this_coord;

			uint32 dim = 3;
			
			uint32 index = (dc.y + 1) * dim * dim + (dc.z + 1) * dim + (dc.x + 1);
			
			m_adj.set(index, true);




			int32 sx = dc.x == -1 ? CHUNK_SIZE - 1 : 0;
			int32 ex = dc.x == 1 ? 1 : CHUNK_SIZE;
			int32 sz = dc.z == -1 ? (CHUNK_SIZE - 1) : 0;
			int32 ez = dc.z == 1 ? 1 : CHUNK_SIZE;
			int32 sy = dc.y == -1 ? (CHUNK_SIZE - 1) : 0;
			int32 ey = dc.y == 1 ? 1 : CHUNK_SIZE;


			for(int32 x = sx; x < ex; ++x)
			{
				for(int32 y = sy; y < ey; ++y)
				{
					for(int32 z = sz; z < ez; ++z)
					{
						Coord this_coord = VoxelUtils::ChunkToChunk(key, Coord(x, y, z), m_key);
						int32 index = ToIndex(this_coord.x, this_coord.y, this_coord.z);
						if(index == -1)
						{
							continue;
						}

						bool val = pChunk == nullptr? false : pChunk->GetBlock(x, y, z) != VT_EMPTY;
						m_blocks.set(index, val);
					}
				}
			}

			//if(dc.x == 1)
			//{
			//	// nx
			//	int32 x = 0;

			//	int32 z = dc.z == -1 ? (CHUNK_SIZE - 1) : 0;
			//	int32 ez = dc.z == 1 ? 1 : CHUNK_SIZE;

			//	for(z = 0; z < ez; ++z)
			//	{
			//		int32 y = dc.y == -1 ? (CHUNK_SIZE - 1) : 0;
			//		int32 ey = dc.y == 1 ? 1 : CHUNK_SIZE;

			//		for(y = 0; y < ey; ++y)
			//		{
			//			Coord this_coord = VoxelUtils::ChunkToChunk(key, Coord(x, y, z), m_key);
			//			int32 index = ToIndex(this_coord.x, this_coord.y, this_coord.z);
			//			if(index == -1)
			//			{
			//				continue;
			//			}

			//			bool val = pChunk == nullptr? false : pChunk->GetBlock(x, y, z) != VT_EMPTY;
			//			m_blocks.set(index, val);
			//		}
			//	}
			//}

			//if(dc.x == -1)
			//{
			//	int32 x = CHUNK_SIZE - 1;

			//	int32 z = dc.z == -1 ? (CHUNK_SIZE - 1) : 0;
			//	int32 ez = dc.z == 1 ? 1 : CHUNK_SIZE;

			//	for(z = 0; z < ez; ++z)
			//	{
			//		int32 y = dc.y == -1 ? (CHUNK_SIZE - 1) : 0;
			//		int32 ey = dc.y == 1 ? 1 : CHUNK_SIZE;

			//		for(y = 0; y < ey; ++y)
			//		{
			//			Coord this_coord = VoxelUtils::ChunkToChunk(key, Coord(x, y, z), m_key);
			//			int32 index = ToIndex(this_coord.x, this_coord.y, this_coord.z);
			//			if(index == -1)
			//			{
			//				continue;
			//			}

			//			bool val = pChunk == nullptr? false : pChunk->GetBlock(x, y, z) != VT_EMPTY;
			//			m_blocks.set(index, val);
			//		}
			//	}
			//}

			//if(dc.y == 1)
			//{
			//	int32 y = 0;
			//	int32 z = dc.z == -1 ? (CHUNK_SIZE - 1) : 0;
			//	int32 ez = dc.z == 1 ? 1 : CHUNK_SIZE;

			//	for(z = 0; z < ez; ++z)
			//	{
			//		int32 x = dc.x == -1 ? CHUNK_SIZE - 1 : 0;
			//		int32 ex = dc.x == 1 ? 1 : CHUNK_SIZE;

			//		for(x = 0; x < ex; ++x)
			//		{
			//			Coord this_coord = VoxelUtils::ChunkToChunk(key, Coord(x, y, z), m_key);
			//			int32 index = ToIndex(this_coord.x, this_coord.y, this_coord.z);
			//			if(index == -1)
			//			{
			//				continue;
			//			}

			//			bool val = pChunk == nullptr? false : pChunk->GetBlock(x, y, z) != VT_EMPTY;
			//			m_blocks.set(index, val);

			//			int ddd = 0;
			//		}
			//	}
			//}

			//if(dc.y == -1)
			//{

			//	int32 y = CHUNK_SIZE - 1;
			//	int32 z = dc.z == -1 ? (CHUNK_SIZE - 1) : 0;
			//	int32 ez = dc.z == 1 ? 1 : CHUNK_SIZE;

			//	for(z = 0; z < ez; ++z)
			//	{
			//		int32 x = dc.x == -1 ? CHUNK_SIZE - 1 : 0;
			//		int32 ex = dc.x == 1 ? 1 : CHUNK_SIZE;

			//		for(x = 0; x < ex; ++x)
			//		{
			//			Coord this_coord = VoxelUtils::ChunkToChunk(key, Coord(x, y, z), m_key);
			//			int32 index = ToIndex(this_coord.x, this_coord.y, this_coord.z);
			//			if(index == -1)
			//			{
			//				continue;
			//			}

			//			bool val = pChunk == nullptr? false : pChunk->GetBlock(x, y, z) != VT_EMPTY;
			//			m_blocks.set(index, val);
			//		}
			//	}
			//}

			//if(dc.z == 1)
			//{
			//	int32 z = 0;
			//	int32 y = dc.y == -1 ? (CHUNK_SIZE - 1) : 0;
			//	int32 ey = dc.y == 1 ? 1 : CHUNK_SIZE;

			//	for(y = 0; y < ey; ++y)
			//	{
			//		int32 x = dc.x == -1 ? CHUNK_SIZE - 1 : 0;
			//		int32 ex = dc.x == 1 ? 1 : CHUNK_SIZE;

			//		for(x = 0; x < ex; ++x)
			//		{
			//			Coord this_coord = VoxelUtils::ChunkToChunk(key, Coord(x, y, z), m_key);
			//			int32 index = ToIndex(this_coord.x, this_coord.y, this_coord.z);
			//			if(index == -1)
			//			{
			//				continue;
			//			}

			//			bool val = pChunk == nullptr? false : pChunk->GetBlock(x, y, z) != VT_EMPTY;
			//			m_blocks.set(index, val);
			//		}
			//	}
			//}

			//if(dc.z == -1)
			//{
			//	int32 z = CHUNK_SIZE - 1;
			//	int32 y = dc.y == -1 ? (CHUNK_SIZE - 1) : 0;
			//	int32 ey = dc.y == 1 ? 1 : CHUNK_SIZE;

			//	for(y = 0; y < ey; ++y)
			//	{
			//		int32 x = dc.x == -1 ? CHUNK_SIZE - 1 : 0;
			//		int32 ex = dc.x == 1 ? 1 : CHUNK_SIZE;

			//		for(x = 0; x < ex; ++x)
			//		{
			//			Coord this_coord = VoxelUtils::ChunkToChunk(key, Coord(x, y, z), m_key);
			//			int32 index = ToIndex(this_coord.x, this_coord.y, this_coord.z);
			//			if(index == -1)
			//			{
			//				continue;
			//			}

			//			bool val = pChunk == nullptr? false : pChunk->GetBlock(x, y, z) != VT_EMPTY;
			//			m_blocks.set(index, val);
			//		}
			//	}
			//}
	
		}
		bool ChunkAdjacency::IsComplete() const
		{
			return m_adj.all();
		}
		bool ChunkAdjacency::CheckCoord(int32 x, int32 y, int32 z) const
		{
			int32 dim = CHUNK_SIZE;
			if(x < -1 || x > dim || y <-1 || y > dim || z < -1 || z > dim)
			{
				return false;
			}

			return true;
		}
		bool ChunkAdjacency::IsVisible() const
		{
			return m_visible;
		}
		bool ChunkAdjacency::CheckVisiblity() const
		{
			return true;

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
		int32 ChunkAdjacency::ToIndex(int32 x, int32 y, int32 z) const
		{
			if(CheckCoord(x, y, z) == false)
			{
				return -1;
			}
			uint32 dim = CHUNK_SIZE + 2;
			
			uint32 index = (y + 1) * dim * dim + (z + 1) * dim + (x + 1);
			return index;
		}
	}
}
