#include "voxel_pch.h"
#include "voxel_PoolManager.h"

#include "voxel/voxel_ChunkMesh.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_OctTree.h"

namespace ld3d
{
	namespace voxel
	{
		
		PoolManager::PoolManager(void) : 
			m_meshPool(sizeof(ChunkMesh), 1024), 
			m_chunkPool(sizeof(Chunk), 1024),
			m_octTreePool(sizeof(OctTree), 1024)
		{
		}


		PoolManager::~PoolManager(void)
		{
		}
		ChunkPtr PoolManager::AllocChunk(ChunkManagerPtr pManager, uint8 data[])
		{
			void* p = m_chunkPool.malloc();
			
			return ChunkPtr(new(p)Chunk(pManager, data), [&](Chunk* pData){if(pData ==nullptr) return; pData->~Chunk();m_chunkPool.free(pData);});

		}
		ChunkMeshPtr PoolManager::AllocChunkMesh()
		{
			void* p = m_meshPool.malloc();
			return ChunkMeshPtr(new(p)ChunkMesh(), [&](ChunkMesh* pData){if(pData == nullptr) return; pData->~ChunkMesh(); m_meshPool.free(pData);});
		}
		OctTreePtr PoolManager::AllocOctTree(const Coord& region_origin)
		{
			void* p = m_octTreePool.malloc();
			return OctTreePtr(new(p)OctTree(region_origin), [&](OctTree* pData){if(pData == nullptr) return; pData->~OctTree(); m_octTreePool.free(pData);});
		}
	}
}