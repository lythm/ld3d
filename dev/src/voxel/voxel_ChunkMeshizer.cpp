#include "voxel_pch.h"
#include "voxel/voxel_ChunkMeshizer.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_ChunkManager.h"

namespace ld3d
{
	namespace voxel
	{
		ChunkMeshizer::ChunkMeshizer(void)
		{
		}


		ChunkMeshizer::~ChunkMeshizer(void)
		{

		}
		void ChunkMeshizer::GenerateMesh(ChunkPtr pChunk, const Coord& base_coord, std::vector<VoxelMesh>& result)
		{
			ChunkManagerPtr pChunkManager = pChunk->GetChunkManager();

			for(int32 x = 0; x < CHUNK_SIZE; ++x)
			{
				for(int32 y = 0; y < CHUNK_SIZE; ++y)
				{
					for(int32 z = 0; z < CHUNK_SIZE; ++z)
					{
						//if(is_templated_mesh)
						//{
						//	// replace by template mesh
						//	continue;
						//}


						// cube block

						uint8 type = pChunk->GetBlock(x, y, z);

						std::map<uint8, VoxelMaterial>::iterator it = m_materialMap.find(type);
						if(it == m_materialMap.end())
						{
							// no material
							continue;
						}



					}
				}
			}
		}
		void ChunkMeshizer::AddVoxelMaterial(uint8 type, const VoxelMaterial& mat)
		{
			m_materialMap[type] = mat;
		}
	}
}
