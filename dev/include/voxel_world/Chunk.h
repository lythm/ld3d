#pragma once

namespace ld3d
{
	namespace voxel
	{
		class Chunk
		{
		public:
			Chunk(void);
			virtual ~Chunk(void);


		private:
			uint8											m_data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
			uint32											m_key;
		};
	}
}
