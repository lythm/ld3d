#pragma once

#include "voxel_world/ChunkKey.h"

namespace ld3d
{
	namespace voxel
	{
		class _DLL_CLASS Chunk
		{
		public:
			Chunk(void);
			virtual ~Chunk(void);

			void											RemoveBlock(uint32 index);
			void											ReplaceBlock(uint32 index, uint8 v);
			void											AddBlock(uint32 index, uint8 v);


			uint8&											operator[](uint32 index)
			{
				return m_data[index];
			}

			const uint8&									operator[](uint32 index) const
			{
				return m_data[index];
			}
			
			uint8											GetBlock(uint32 x, uint32 y, uint32 z)
			{
				uint32 index = ToIndex(x, y, z);
				return m_data[index];
			}
			void											SetBlock(uint32 x, uint32 y, uint32 z, uint8 val)
			{
				uint32 index	= ToIndex(x, y, z);
				m_data[index]	= val;
			}

			uint8											ToIndex(uint32 x, uint32 y, uint32 z)
			{
				uint32 index = z * CHUNK_SIZE * CHUNK_SIZE + y * CHUNK_SIZE + x;
				return index;
			}


			const ChunkKey&									GetKey() const;
			void											SetKey(const ChunkKey& key);

			ChunkPtr										GetNext();
			void											SetNext(ChunkPtr pNext);

		private:
			uint8											m_data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
			ChunkKey										m_key;

			ChunkPtr										m_pNext;
			
		};
	}
}
