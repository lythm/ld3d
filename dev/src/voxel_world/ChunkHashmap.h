#pragma once

#include "voxel_world/ChunkKey.h"


#include "voxel_world/Chunk.h"


#include <unordered_map>

namespace ld3d
{
	namespace voxel
	{
		class ChunkHashmap
		{
		public:
			ChunkHashmap(void);
			virtual ~ChunkHashmap(void);

			bool											Initialize();
			void											Release();
			ChunkPtr										FindChunk(const ChunkKey& key);

			void											AddChunk(const ChunkKey& key, ChunkPtr pChunk);
			ChunkPtr										RemoveChunk(const ChunkKey& key);
		private:


			std::vector<ChunkPtr>							m_chunks;

		};

	}
}
