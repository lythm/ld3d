#pragma once

#include "voxel/voxel_ChunkKey.h"

#include "voxel/voxel_Coord.h"
#include "voxel/voxel_ChunkAdjacency.h"

namespace ld3d
{
	namespace voxel
	{
		class _DLL_CLASS Chunk : public RefCount, public std::enable_shared_from_this<Chunk>
		{
		public:
			
			// if data is null, empty chunk is constructed.
			Chunk(ChunkManagerPtr pChunkManager, const ChunkKey& key, uint8 data[]);

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

				m_adjacency.OnBlockChange(x, y, z, val != VT_EMPTY);

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

			ChunkAdjacency&									GetAdjacency();
			void											SetAdjacency(const ChunkAdjacency& adj);
		private:
						
		private:
			uint8											m_data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
			ChunkKey										m_key;

			int32											m_counter;
			bool											m_dirty;

			bool											m_modified;

			void*											m_userData;

			ChunkManagerPtr									m_pChunkManager;

			ChunkMeshPtr									m_pMesh;

			ChunkAdjacency									m_adjacency;
		};
	}
}
