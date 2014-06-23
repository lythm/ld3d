#pragma once

#include "voxel/voxel_Coord.h"
#include "voxel/voxel_ChunkKey.h"

namespace ld3d
{
	namespace voxel
	{
		class PoolManager
		{
		public:
			PoolManager(void);
			virtual ~PoolManager(void);

			ChunkPtr										AllocChunk(ChunkManagerPtr pManager, const ChunkKey& key, uint8 data[]);
			ChunkMeshPtr									AllocChunkMesh();
			OctreePtr										AllocOctTree(const Coord& region_origin);
		private:
			boost::pool<pool_allocator>						m_meshPool;
			boost::pool<pool_allocator>						m_chunkPool;
			boost::pool<pool_allocator>						m_octTreePool;
		};


	}
}