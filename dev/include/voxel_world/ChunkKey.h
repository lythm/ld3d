#pragma once

#include "voxel_world/Coord.h"

namespace ld3d
{
	namespace voxel
	{

		//
		// |28-|-8-|-28-|
		//  x    y   z
		//



		class ChunkKey
		{
		public:

			ChunkKey(uint64 key = 0xffffffffffffffff)
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

			uint64												AsUint64() const
			{
				return m_key;
			}

			Coord												ToCoord() const
			{
				uint32 c_x = (m_key >> 36) & 0x000000000fffffff;
				uint8 c_y = (m_key >> 28) & 0x00000000000000ff;
				uint32 c_z = m_key & 0x000000000fffffff;

				int32 x = c_x * CHUNK_SIZE * BLOCK_SIZE;
				int8 y = c_y * CHUNK_SIZE * BLOCK_SIZE;
				int32 z = c_z * CHUNK_SIZE * BLOCK_SIZE;

				return Coord(x, y, z);
			}
			void												FromCoord(const Coord& coord)
			{
				uint64 c_x = uint32(coord.x / (CHUNK_SIZE * BLOCK_SIZE));
				uint64 c_y = uint8(coord.y / (CHUNK_SIZE * BLOCK_SIZE));
				uint64 c_z = uint32(coord.z / (CHUNK_SIZE * BLOCK_SIZE));

				m_key = ((c_x << 36) | (c_y << 28) | (c_z));
			}

			bool operator ==(const ChunkKey& key) const
			{
				return m_key == key.AsUint64();
			}
			bool operator!=(const ChunkKey& key) const
			{
				return !operator==(key);
			}

		private:
			uint64												m_key;
		};

	}
}