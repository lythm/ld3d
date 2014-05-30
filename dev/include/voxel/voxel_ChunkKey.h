#pragma once

#include "voxel/voxel_Coord.h"

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

			Coord												ToChunkOrigin() const
			{

				int32 c_x = (m_key >> 36) & 0x000000000fffffff;
				int8 c_y = (m_key >> 28) & 0x00000000000000ff;
				int32 c_z = m_key & 0x000000000fffffff;

				int32 x = c_x * CHUNK_SIZE;
				int32 y = c_y * CHUNK_SIZE;
				int32 z = c_z * CHUNK_SIZE;

				return Coord(x, y, z );
			}

			void												FromCoord(const Coord& coord)
			{
				uint64 c_x = uint64(coord.x) / CHUNK_SIZE;
				uint64 c_y = uint64(coord.y) / CHUNK_SIZE;
				uint64 c_z = uint64(coord.z) / CHUNK_SIZE;

				m_key = (((c_x & 0x000000000fffffff) << 36 ) | 
					((c_y & 0x00000000000000ff) << 28) |
					 (c_z & 0x000000000fffffff));
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

		private:

			uint64												m_key;
		};

	}
}

