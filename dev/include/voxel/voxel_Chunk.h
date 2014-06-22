#pragma once

#include "voxel/voxel_ChunkKey.h"

#include "voxel/voxel_Coord.h"
#include <bitset>

namespace ld3d
{
	namespace voxel
	{
		class _DLL_CLASS Chunk : public RefCount
		{
		public:
			enum
			{
				n_x			= 2,
				p_x			= 3,
				n_y			= 4,
				p_y			= 5,
				n_z			= 6,
				p_z			= 7,
				all_bits	= 0xfc,

			};
			// if data is null, empty chunk is constructed.
			Chunk(ChunkManagerPtr pChunkManager, uint8 data[]);

			// non virtual, do not subclass
			~Chunk(void);


			bool											IsEmpty() const
			{
				return m_counter == 0;
			}

			uint8											GetBlock(uint32 x, uint32 y, uint32 z)
			{
				uint32 index = ToIndex(x, y, z);
				return m_data[index];
			}
			uint8											GetBlock(const Coord& c)
			{
				return GetBlock(c.x, c.y, c.z);
			}
			void											SetBlock(uint32 x, uint32 y, uint32 z, uint8 val)
			{
				uint32 index	= ToIndex(x, y, z);

				if(m_data[index] != val)
				{
					m_counter += val == VT_EMPTY ? -1 : m_data[index] == VT_EMPTY ? 1 : 0;
				}

				m_data[index]	= val;
				UpdateAllNeighBour(x, y, z, val != VT_EMPTY);

				SetDirty(true);
				m_modified = true;
			}
			void											SetBlock(const Coord& c, uint8 val)
			{
				SetBlock(c.x, c.y, c.z, val);
			}

			static uint32									ToIndex(uint32 x, uint32 y, uint32 z)
			{
				uint32 index = y * CHUNK_SIZE * CHUNK_SIZE + z * CHUNK_SIZE + x;
				return index;
			}
			static uint32									ToIndex(const Coord& c)
			{
				return ToIndex(c.x, c.y, c.z);
			}
			static void										ToCoord(uint32 index, Coord& c)
			{
				c.y = index / (CHUNK_SIZE * CHUNK_SIZE);
				c.z = (index % (CHUNK_SIZE * CHUNK_SIZE)) / CHUNK_SIZE;
				c.x = (index % (CHUNK_SIZE * CHUNK_SIZE)) % CHUNK_SIZE;
			}
			const ChunkKey&									GetKey() const;
			void											SetKey(const ChunkKey& key);

			void											Update();

			bool											IsDirty() const;
			void											SetDirty(bool dirty);

			void											SetData(uint8 data[]);
			uint8*											GetData();
			bool											IsModified() const;

			void											SetUserData(void* pData);
			void*											GetUserData();

			ChunkManagerPtr									GetChunkManager();
			
			ChunkMeshPtr									GetMesh();
			void											SetMesh(ChunkMeshPtr pMesh);

			// set this block neightbour flag
			void											SetNeightbourFlag(int32 x, int32 y, int32 z, int32 neighbour, bool val);
			void											SetNeightbourFlag(int32 index, int32 neighbour, bool val);
			bool											CheckNeighbourFlag(int32 x, int32 y, int32 z, int32 neighbour);
			bool											CheckNeighbourFlag(int32 index, int32 neighbour);

			uint8											GetNeighbourFlag(int32 x, int32 y, int32 z);
			uint8											GetNeighbourFlag(int32 index);


			void											SetChunkNeighbour(uint32 neighbour, bool val);
			bool											GetChunkNeightbour(uint32 neighbour);

			void											OnNeibourChunkLoaded(ChunkPtr pChunk);

			bool											AllNeighbourLoaded();
		private:

			void											SetBit(uint8& bits, uint32 pos, bool val);
			bool											GetBit(uint8 bits, uint32 pos);

			bool											_check_coord_range(int32 x, int32 y, int32 z);
			void											UpdateAllNeighBour(int32 x, int32 y, int32 z, bool val);
		private:
			uint8											m_data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
			uint8											m_neighbour[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
			ChunkKey										m_key;

			int32											m_counter;
			bool											m_dirty;

			bool											m_modified;

			void*											m_userData;

			ChunkManagerPtr									m_pChunkManager;

			ChunkMeshPtr									m_pMesh;

			uint8											m_chunkNeighbour;
		};
	}
}
