#pragma once

#include "voxel_world/Coord.h"

namespace ld3d
{
	namespace voxel
	{

		//
		// |-2-|-10-|-10-|-10-|
		//   0   x    y    z
		//



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
				int32 c_x = (m_key >> 20) & 0x000003ff;
				int32 c_y = (m_key >> 10) & 0x000003ff;
				int32 c_z = m_key & 0x000003ff;

				int32 x = c_x * CHUNK_SIZE * BLOCK_SIZE;
				int32 y = c_y * CHUNK_SIZE * BLOCK_SIZE;
				int32 z = c_z * CHUNK_SIZE * BLOCK_SIZE;

				return Coord(x, y, z);
			}
			void												FromCoord(const Coord& coord)
			{
				uint32 c_x = uint32(coord.x / (CHUNK_SIZE * BLOCK_SIZE));
				uint32 c_y = uint32(coord.y / (CHUNK_SIZE * BLOCK_SIZE));
				uint32 c_z = uint32(coord.z / (CHUNK_SIZE * BLOCK_SIZE));

				m_key = ((c_x << 20) | (c_y << 10) | (c_z));
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