#pragma once

#include "voxel_world/Coord.h"

namespace ld3d
{
	namespace voxel
	{
		class ChunkKey
		{
		public:

			ChunkKey(uint32 key = 0xffffffff)
			{
				m_key											= key;
			}

			ChunkKey(const Coord& coord)
			{
				FromCoord(coord);
			}

			~ChunkKey(void)
			{
			}

			uint32												AsUint32() const
			{
				return m_key;
			}

			Coord												ToCoord() const
			{
				int32 c_x = (m_key >> 16) & 0x000000ff;
				int32 c_y = (m_key >> 8) & 0x000000ff;
				int32 c_z = m_key & 0x000000ff;

				int32 x = c_x * CHUNK_SIZE * BLOCK_SIZE;
				int32 y = c_y * CHUNK_SIZE * BLOCK_SIZE;
				int32 z = c_z * CHUNK_SIZE * BLOCK_SIZE;

				return Coord(x, y, z);
			}
			void												FromCoord(const Coord& coord)
			{
				uint32 c_x = uint32(coord.x / CHUNK_SIZE);
				uint32 c_y = uint32(coord.y / CHUNK_SIZE);
				uint32 c_z = uint32(coord.z / CHUNK_SIZE);

				m_key = ((c_x << 16) | (c_y << 8) | (c_z));
			}

			bool operator ==(const ChunkKey& key) const
			{
				return m_key == key.AsUint32();
			}
			bool operator!=(const ChunkKey& key) const
			{
				return !operator==(key);
			}

		private:
			uint32												m_key;
		};


	}
}