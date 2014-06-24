#include "voxel_pch.h"
#include "voxel_PoolManager.h"

#include "voxel/voxel_ChunkMesh.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_Octree.h"

namespace ld3d
{
	namespace voxel
	{
		
		PoolManager::PoolManager(void) : 
			m_meshPool(sizeof(ChunkMesh), 1024), 
			m_chunkPool(sizeof(Chunk), 1024),
			m_octTreePool(sizeof(Octree), 1024)
		{
		}


		PoolManager::~PoolManager(void)
		{
		}
		ChunkPtr PoolManager::AllocChunk(ChunkManagerPtr pManager, const ChunkKey& key, const ChunkData& data)
		{
			void* p = m_chunkPool.malloc();
			
			return ChunkPtr(new(p)Chunk(pManager, key, data), [&](Chunk* pData){if(pData ==nullptr) return; pData->~Chunk();m_chunkPool.free(pData);});

		}
		ChunkMeshPtr PoolManager::AllocChunkMesh()
		{
			void* p = m_meshPool.malloc();
			return ChunkMeshPtr(new(p)ChunkMesh(), [&](ChunkMesh* pData){if(pData == nullptr) return; pData->~ChunkMesh(); m_meshPool.free(pData);});
		}
		OctreePtr PoolManager::AllocOctTree(const Coord& region_origin)
		{
			void* p = m_octTreePool.malloc();
			return OctreePtr(new(p)Octree(region_origin), [&](Octree* pData){if(pData == nullptr) return; pData->~Octree(); m_octTreePool.free(pData);});
		}
	}
}