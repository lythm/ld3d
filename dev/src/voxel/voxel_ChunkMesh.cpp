#include "voxel_pch.h"
#include "voxel/voxel_ChunkMesh.h"
#include "voxel/voxel_World.h"
#include "voxel/voxel_Chunk.h"

namespace ld3d
{
	namespace voxel
	{
		ChunkMesh::ChunkMesh(void)
		{
		}

		ChunkMesh::~ChunkMesh(void)
		{
		}
		bool ChunkMesh::UpdateMesh(WorldPtr pWorld, const ChunkKey& key)
		{
			m_chunkCoord = key.ToCoord();

			ChunkPtr pChunk = pWorld->FindChunk(key);
			if(pChunk == nullptr)
			{
				return false;
			}
			return _gen_mesh_simple(pWorld, pChunk);
		}
		bool ChunkMesh::_gen_mesh_simple(WorldPtr pWorld, ChunkPtr pChunk)
		{
			m_mesh.clear();

			for(int x = 0; x < CHUNK_SIZE; ++x)
			{
				for(int y = 0; y < CHUNK_SIZE; ++y)
				{
					for(int z = 0; z < CHUNK_SIZE; ++z)
					{

					}
				}
			}
			return true;
		}
	}
}
