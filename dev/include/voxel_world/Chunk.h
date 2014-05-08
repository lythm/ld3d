#pragma once

#include "voxel_world/ChunkKey.h"

namespace ld3d
{
	namespace voxel
	{
		class Chunk
		{
		public:
			Chunk(void);
			virtual ~Chunk(void);

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

		private:
			uint8											m_data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
			ChunkKey										m_key;
		};
	}
}
