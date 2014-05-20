#pragma once

#include "voxel_world/Coord.h"

#include "voxel_world/ChunkKey.h"

namespace ld3d
{
	namespace voxel
	{
		class _DLL_CLASS World
		{
		public:
			World(void);
			virtual ~World(void);

			bool											Initialize(WorldGenPtr pGen);

			void											Release();

			bool											AddBlock(const Coord& c, uint8 type);
			void											ReplaceBlock(const Coord& c, uint8 type);
			void											RemoveBlock(const Coord& c);
			bool											IsEmpty(const Coord& c);
			uint8											GetBlock(const Coord& c);
			void											UpdateBlock(const Coord& c);


		private:

			bool											InWorld(const Coord& c) const;

			ChunkPtr										AllocChunk();
			ChunkPtr										FindChunk(const ChunkKey& key);
		private:
			WorldGenPtr										m_pGen;

			std::unordered_map<uint64, ChunkPtr>			m_chunkmap;

			Coord											m_worldSize;
		};

	}
}

