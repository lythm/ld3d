#include "voxel_pch.h"
#include "voxel/voxel_Meshizer.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_ChunkManager.h"
#include "voxel/voxel_ChunkMesh.h"

namespace ld3d
{
	namespace voxel
	{
		Meshizer::VoxelFace Meshizer::s_Cube[6];


		// index : 0 - 1 - 2, 1 - 3 - 2
		void Meshizer::InitializeCubeVertex(uint32 size)
		{
			// -x
			s_Cube[0].verts[0] = math::Vector3(0, 0, 0);
			s_Cube[0].verts[1] = math::Vector3(0, 0, 1);
			s_Cube[0].verts[2] = math::Vector3(0, 1, 0);
			s_Cube[0].verts[3] = math::Vector3(0, 1, 1);

			s_Cube[0].ao[0]		= math::Vector4(1, 1, 1, 1);
			s_Cube[0].ao[1]		= math::Vector4(1, 1, 1, 1);
			s_Cube[0].ao[2]		= math::Vector4(1, 1, 1, 1);
			s_Cube[0].ao[3]		= math::Vector4(1, 1, 1, 1);

			s_Cube[0].normal = math::Vector3(-1, 0, 0);

			// +x
			s_Cube[1].verts[0] = math::Vector3(1, 0, 0);
			s_Cube[1].verts[1] = math::Vector3(1, 1, 0);
			s_Cube[1].verts[2] = math::Vector3(1, 0, 1);
			s_Cube[1].verts[3] = math::Vector3(1, 1, 1);

			s_Cube[1].ao[0]		= math::Vector4(1, 1, 1, 1);
			s_Cube[1].ao[1]		= math::Vector4(1, 1, 1, 1);
			s_Cube[1].ao[2]		= math::Vector4(1, 1, 1, 1);
			s_Cube[1].ao[3]		= math::Vector4(1, 1, 1, 1);

			s_Cube[1].normal = math::Vector3(1, 0, 0);

			// -y
			s_Cube[2].verts[0] = math::Vector3(0, 0, 0);
			s_Cube[2].verts[1] = math::Vector3(1, 0, 0);
			s_Cube[2].verts[2] = math::Vector3(0, 0, 1);
			s_Cube[2].verts[3] = math::Vector3(1, 0, 1);

			s_Cube[2].ao[0]		= math::Vector4(1, 1, 1, 1);
			s_Cube[2].ao[1]		= math::Vector4(1, 1, 1, 1);
			s_Cube[2].ao[2]		= math::Vector4(1, 1, 1, 1);
			s_Cube[2].ao[3]		= math::Vector4(1, 1, 1, 1);

			s_Cube[2].normal = math::Vector3(0, -1, 0);

			// +y
			s_Cube[3].verts[0] = math::Vector3(0, 1, 0);
			s_Cube[3].verts[1] = math::Vector3(0, 1, 1);
			s_Cube[3].verts[2] = math::Vector3(1, 1, 0);
			s_Cube[3].verts[3] = math::Vector3(1, 1, 1);

			s_Cube[3].ao[0]		= math::Vector4(1, 1, 1, 1);
			s_Cube[3].ao[1]		= math::Vector4(1, 1, 1, 1);
			s_Cube[3].ao[2]		= math::Vector4(1, 1, 1, 1);
			s_Cube[3].ao[3]		= math::Vector4(1, 1, 1, 1);

			s_Cube[3].normal = math::Vector3(0, 1, 0);


			// -z
			s_Cube[4].verts[0] = math::Vector3(0, 0, 0);
			s_Cube[4].verts[1] = math::Vector3(0, 1, 0);
			s_Cube[4].verts[2] = math::Vector3(1, 0, 0);
			s_Cube[4].verts[3] = math::Vector3(1, 1, 0);

			s_Cube[4].ao[0]		= math::Vector4(1, 1, 1, 1);
			s_Cube[4].ao[1]		= math::Vector4(1, 1, 1, 1);
			s_Cube[4].ao[2]		= math::Vector4(1, 1, 1, 1);
			s_Cube[4].ao[3]		= math::Vector4(1, 1, 1, 1);

			s_Cube[4].normal = math::Vector3(0, 0, -1);

			// +z
			s_Cube[5].verts[0] = math::Vector3(0, 0, 1);
			s_Cube[5].verts[1] = math::Vector3(1, 0, 1);
			s_Cube[5].verts[2] = math::Vector3(0, 1, 1);
			s_Cube[5].verts[3] = math::Vector3(1, 1, 1);

			s_Cube[5].ao[0]		= math::Vector4(1, 1, 1, 1);
			s_Cube[5].ao[1]		= math::Vector4(1, 1, 1, 1);
			s_Cube[5].ao[2]		= math::Vector4(1, 1, 1, 1);
			s_Cube[5].ao[3]		= math::Vector4(1, 1, 1, 1);

			s_Cube[5].normal = math::Vector3(0, 0, 1);


			for(int i = 0; i < 5; ++i)
			{
				s_Cube[i].verts[0] *= (float)size;
				s_Cube[i].verts[1] *= (float)size;
				s_Cube[i].verts[2] *= (float)size;
				s_Cube[i].verts[3] *= (float)size;
			}
		}

		Meshizer::Meshizer(void)
		{
			InitializeCubeVertex(BLOCK_SIZE);
		}


		Meshizer::~Meshizer(void)
		{
			m_materialMap.clear();
			m_templates.clear();
		}
		void Meshizer::GenerateFaceAO(const ChunkKey& key, uint8* chunk_data, const ChunkAdjacency& adj, VoxelFace& face)
		{
			//Coord chunk_coord = key.ToChunkOrigin();
			//
			//for(int i = 0; i < 4; ++i)
			//{
			//	float ao = 0;

			//	if(adj.CheckBlockAdjacency(face.verts[i].x + c_x + 0.5, face.verts[i].y + c_y + 0.5, face.verts[i].z + c_z + 0.5f))
			//	{
			//		ao ++;
			//	}


			//	if(pRegion->Empty(face.verts[i].x + c_x + 0.5, face.verts[i].y + c_y + 0.5, face.verts[i].z + c_z - 0.5f))
			//	{
			//		ao ++;
			//	}


			//	if(pRegion->Empty(face.verts[i].x + c_x -0.5 , face.verts[i].y + c_y + 0.5, face.verts[i].z + c_z + 0.5))
			//	{
			//		ao ++;
			//	}


			//	if(pRegion->Empty(face.verts[i].x + c_x - 0.5, face.verts[i].y + c_y + 0.5, face.verts[i].z + c_z - 0.5))
			//	{
			//		ao ++;
			//	}


			//	///
			//	if(pRegion->Empty(face.verts[i].x + c_x + 0.5, face.verts[i].y + c_y - 0.5, face.verts[i].z + c_z + 0.5f))
			//	{
			//		ao ++;
			//	}


			//	if(pRegion->Empty(face.verts[i].x + c_x + 0.5, face.verts[i].y + c_y - 0.5, face.verts[i].z + c_z - 0.5f))
			//	{
			//		ao ++;
			//	}


			//	if(pRegion->Empty(face.verts[i].x + c_x -0.5 , face.verts[i].y + c_y - 0.5, face.verts[i].z + c_z + 0.5))
			//	{
			//		ao ++;
			//	}


			//	if(pRegion->Empty(face.verts[i].x + c_x - 0.5, face.verts[i].y + c_y - 0.5, face.verts[i].z + c_z - 0.5))
			//	{
			//		ao ++;
			//	}



			//	ao = ao / 8.0f ;

			//	ao += 0.3f;
			//	ao = ao > 1? 1 : ao;

			//	face.ao[i] = math::Vector4(ao, ao, ao, 1);

			//	//face.ao[i] = math::Color4(1, 1, 1, 1);
			//}
		}
		void Meshizer::DoGenerateMesh(const ChunkKey& key, const ChunkData& chunk_data, const ChunkAdjacency& adj, const Coord& base_coord, ChunkMeshPtr pMesh)
		{
			Coord chunk_base = key.ToChunkOrigin();

			math::Vector3 vertex_offset( (float)base_coord.x, (float)base_coord.y, (float)base_coord.z);

			std::vector<VoxelFace, std_allocator_adapter<VoxelFace>>			mesh(allocator());
			mesh.reserve(10000);

			for(int32 x = 0; x < CHUNK_SIZE; ++x)
			{
				for(int32 y = 0; y < CHUNK_SIZE; ++y)
				{
					for(int32 z = 0; z < CHUNK_SIZE; ++z)
					{
						uint8 type = chunk_data.Get(x, y, z);

						if(type == VT_EMPTY)
						{
							continue;
						}


						//if(is_templated_mesh)
						//{
						//	// replace by template mesh
						//	continue;
						//}


						// cube block

						std::map<uint8, VoxelMaterial>::iterator it = m_materialMap.find(type);
						if(it == m_materialMap.end())
						{
							// no material
							continue;
						}

						const VoxelMaterial& mat = it->second;


						// -x
						//if(pChunkManager->IsEmpty(Coord(x - 1, y, z) + chunk_base))
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::n_x) == false)
						{
							VoxelFace face = s_Cube[0];
							face.verts[0] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[1] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[2] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[3] += math::Vector3((float)x, (float)y, (float)z);

							face.uv[0] = mat.uv[VoxelMaterial::n_x][0];
							face.uv[1] = mat.uv[VoxelMaterial::n_x][1];
							face.uv[2] = mat.uv[VoxelMaterial::n_x][2];
							face.uv[3] = mat.uv[VoxelMaterial::n_x][3];


							face.material = mat.materials[VoxelMaterial::n_x];
							face.type = type;

							mesh.push_back(face);
						}

						// +x
						//if(pChunkManager->IsEmpty(Coord(x + 1, y, z) + chunk_base))
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::p_x) == false)
						{
							VoxelFace face = s_Cube[1];
							face.verts[0] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[1] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[2] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[3] += math::Vector3((float)x, (float)y, (float)z);

							face.uv[0] = mat.uv[VoxelMaterial::p_x][0];
							face.uv[1] = mat.uv[VoxelMaterial::p_x][1];
							face.uv[2] = mat.uv[VoxelMaterial::p_x][2];
							face.uv[3] = mat.uv[VoxelMaterial::p_x][3];


							face.material = mat.materials[VoxelMaterial::p_x];
							face.type = type;

							mesh.push_back(face);
						}

						// -y
						//if(pChunkManager->IsEmpty(Coord(x , y - 1, z) + chunk_base))
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::n_y) == false)
						{
							VoxelFace face = s_Cube[2];
							face.verts[0] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[1] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[2] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[3] += math::Vector3((float)x, (float)y, (float)z);

							face.uv[0] = mat.uv[VoxelMaterial::n_y][0];
							face.uv[1] = mat.uv[VoxelMaterial::n_y][1];
							face.uv[2] = mat.uv[VoxelMaterial::n_y][2];
							face.uv[3] = mat.uv[VoxelMaterial::n_y][3];


							face.material = mat.materials[VoxelMaterial::n_y];
							face.type = type;

							mesh.push_back(face);
						}

						// +y
						//if(pChunkManager->IsEmpty(Coord(x, y + 1, z) + chunk_base))
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::p_y) == false)
						{
							VoxelFace face = s_Cube[3];
							face.verts[0] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[1] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[2] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[3] += math::Vector3((float)x, (float)y, (float)z);

							face.uv[0] = mat.uv[VoxelMaterial::p_y][0];
							face.uv[1] = mat.uv[VoxelMaterial::p_y][1];
							face.uv[2] = mat.uv[VoxelMaterial::p_y][2];
							face.uv[3] = mat.uv[VoxelMaterial::p_y][3];


							face.material = mat.materials[VoxelMaterial::p_y];
							face.type = type;

							mesh.push_back(face);
						}

						// -z
						//if(pChunkManager->IsEmpty(Coord(x, y, z - 1) + chunk_base))
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::n_z) == false)
						{
							VoxelFace face = s_Cube[4];
							face.verts[0] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[1] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[2] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[3] += math::Vector3((float)x, (float)y, (float)z);

							face.uv[0] = mat.uv[VoxelMaterial::n_z][0];
							face.uv[1] = mat.uv[VoxelMaterial::n_z][1];
							face.uv[2] = mat.uv[VoxelMaterial::n_z][2];
							face.uv[3] = mat.uv[VoxelMaterial::n_z][3];


							face.material = mat.materials[VoxelMaterial::n_z];
							face.type = type;

							mesh.push_back(face);
						}

						// +z
						//if(pChunkManager->IsEmpty(Coord(x, y, z + 1) + chunk_base))
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::p_z) == false)
						{
							VoxelFace face = s_Cube[5];
							face.verts[0] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[1] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[2] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[3] += math::Vector3((float)x, (float)y, (float)z);

							face.uv[0] = mat.uv[VoxelMaterial::p_z][0];
							face.uv[1] = mat.uv[VoxelMaterial::p_z][1];
							face.uv[2] = mat.uv[VoxelMaterial::p_z][2];
							face.uv[3] = mat.uv[VoxelMaterial::p_z][3];


							face.material = mat.materials[VoxelMaterial::p_z];
							face.type = type;

							mesh.push_back(face);
						}
					}
				}
			}

			std::sort(mesh.begin(), mesh.end(), [](VoxelFace& a,VoxelFace& b){return a.material < b.material;});

			if(mesh.size() == 0)
			{
				return;
			}

			for(auto& face : mesh)
			{
				float ao = ((float)rand() / RAND_MAX) / 2.0f + 0.5f;
				face.ao[0] = math::Vector4(ao, ao, ao, 1);

				ao = ((float)rand() / RAND_MAX) / 2.0f + 0.5f;
				face.ao[1] = math::Vector4(ao, ao, ao, 1);

				ao = ((float)rand() / RAND_MAX) / 2.0f + 0.5f;
				face.ao[2] = math::Vector4(ao, ao, ao, 1);

				ao = ((float)rand() / RAND_MAX) / 2.0f + 0.5f;
				face.ao[3] = math::Vector4(ao, ao, ao, 1);
			}

			pMesh->Reset();

			ChunkMesh::Subset sub;
			sub.type = VT_EMPTY;
			sub.vertexCount				= 0;
			sub.vertexBuffer			= nullptr;

			sub.type					= mesh[0].type;
			sub.material_id				= mesh[0].material;
			pMesh->AllocVertexBuffer((uint32)mesh.size() * 6);

			ChunkMesh::VoxelVertex* pData = (ChunkMesh::VoxelVertex*)pMesh->GetVertexBuffer();

			sub.vertexBuffer = pData;

			for(size_t i = 0; i < mesh.size(); ++i)
			{
				const VoxelFace& face = mesh[i];

				if(face.type != sub.type && sub.vertexCount != 0)
				{
					pMesh->AddSubset(sub);

					sub.type			= face.type;
					sub.material_id		= face.material;
					sub.vertexCount		= 0;
					sub.vertexBuffer	= pData;
				}

				pData->pos = face.verts[0] + vertex_offset;
				pData->normal = face.normal;
				pData->uv = face.uv[0];
				pData->ao = face.ao[0];
				++pData;
				sub.vertexCount++;

				pData->pos = face.verts[1] + vertex_offset;
				pData->normal = face.normal;
				pData->uv = face.uv[1];
				pData->ao = face.ao[1];
				++pData;
				sub.vertexCount++;

				pData->pos = face.verts[2] + vertex_offset;
				pData->normal = face.normal;
				pData->uv = face.uv[2];
				pData->ao = face.ao[2];
				++pData;
				sub.vertexCount++;

				pData->pos = face.verts[1] + vertex_offset;
				pData->normal = face.normal;
				pData->uv = face.uv[1];
				pData->ao = face.ao[1];
				++pData;
				sub.vertexCount++;

				pData->pos = face.verts[3] + vertex_offset;
				pData->normal = face.normal;
				pData->uv = face.uv[3];
				pData->ao = face.ao[3];
				++pData;
				sub.vertexCount++;

				pData->pos = face.verts[2] + vertex_offset;
				pData->normal = face.normal;
				pData->uv = face.uv[2];
				pData->ao = face.ao[2];

				++pData;
				sub.vertexCount++;
			}
			pMesh->AddSubset(sub);
		}
		void Meshizer::GenerateMesh(ChunkPtr pChunk, const Coord& base_coord, ChunkMeshPtr pMesh)
		{
			ChunkManagerPtr pChunkManager = pChunk->GetChunkManager();

			/*if(pChunk->IsEmpty())
			{
			return;
			}
			*/

			Coord chunk_base = pChunk->GetKey().ToChunkOrigin();
			ChunkAdjacency& adj = pChunk->GetAdjacency();

			math::Vector3 vertex_offset( (float)base_coord.x, (float)base_coord.y, (float)base_coord.z);

			std::vector<VoxelFace, std_allocator_adapter<VoxelFace>>			mesh(allocator());
			mesh.reserve(10000);

			for(int32 x = 0; x < CHUNK_SIZE; ++x)
			{
				for(int32 y = 0; y < CHUNK_SIZE; ++y)
				{
					for(int32 z = 0; z < CHUNK_SIZE; ++z)
					{
						uint8 type = pChunk->GetBlock(x, y, z);

						if(type == VT_EMPTY)
						{
							continue;
						}


						//if(is_templated_mesh)
						//{
						//	// replace by template mesh
						//	continue;
						//}


						// cube block

						std::map<uint8, VoxelMaterial>::iterator it = m_materialMap.find(type);
						if(it == m_materialMap.end())
						{
							// no material
							continue;
						}

						const VoxelMaterial& mat = it->second;


						// -x
						//if(pChunkManager->IsEmpty(Coord(x - 1, y, z) + chunk_base))
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::n_x) == false)
						{
							VoxelFace face = s_Cube[0];
							face.verts[0] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[1] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[2] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[3] += math::Vector3((float)x, (float)y, (float)z);

							face.uv[0] = mat.uv[VoxelMaterial::n_x][0];
							face.uv[1] = mat.uv[VoxelMaterial::n_x][1];
							face.uv[2] = mat.uv[VoxelMaterial::n_x][2];
							face.uv[3] = mat.uv[VoxelMaterial::n_x][3];


							face.material = mat.materials[VoxelMaterial::n_x];
							face.type = type;

							mesh.push_back(face);
						}

						// +x
						//if(pChunkManager->IsEmpty(Coord(x + 1, y, z) + chunk_base))
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::p_x) == false)
						{
							VoxelFace face = s_Cube[1];
							face.verts[0] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[1] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[2] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[3] += math::Vector3((float)x, (float)y, (float)z);

							face.uv[0] = mat.uv[VoxelMaterial::p_x][0];
							face.uv[1] = mat.uv[VoxelMaterial::p_x][1];
							face.uv[2] = mat.uv[VoxelMaterial::p_x][2];
							face.uv[3] = mat.uv[VoxelMaterial::p_x][3];


							face.material = mat.materials[VoxelMaterial::p_x];
							face.type = type;

							mesh.push_back(face);
						}

						// -y
						//if(pChunkManager->IsEmpty(Coord(x , y - 1, z) + chunk_base))
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::n_y) == false)
						{
							VoxelFace face = s_Cube[2];
							face.verts[0] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[1] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[2] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[3] += math::Vector3((float)x, (float)y, (float)z);

							face.uv[0] = mat.uv[VoxelMaterial::n_y][0];
							face.uv[1] = mat.uv[VoxelMaterial::n_y][1];
							face.uv[2] = mat.uv[VoxelMaterial::n_y][2];
							face.uv[3] = mat.uv[VoxelMaterial::n_y][3];


							face.material = mat.materials[VoxelMaterial::n_y];
							face.type = type;

							mesh.push_back(face);
						}

						// +y
						//if(pChunkManager->IsEmpty(Coord(x, y + 1, z) + chunk_base))
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::p_y) == false)
						{
							VoxelFace face = s_Cube[3];
							face.verts[0] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[1] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[2] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[3] += math::Vector3((float)x, (float)y, (float)z);

							face.uv[0] = mat.uv[VoxelMaterial::p_y][0];
							face.uv[1] = mat.uv[VoxelMaterial::p_y][1];
							face.uv[2] = mat.uv[VoxelMaterial::p_y][2];
							face.uv[3] = mat.uv[VoxelMaterial::p_y][3];


							face.material = mat.materials[VoxelMaterial::p_y];
							face.type = type;

							mesh.push_back(face);
						}

						// -z
						//if(pChunkManager->IsEmpty(Coord(x, y, z - 1) + chunk_base))
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::n_z) == false)
						{
							VoxelFace face = s_Cube[4];
							face.verts[0] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[1] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[2] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[3] += math::Vector3((float)x, (float)y, (float)z);

							face.uv[0] = mat.uv[VoxelMaterial::n_z][0];
							face.uv[1] = mat.uv[VoxelMaterial::n_z][1];
							face.uv[2] = mat.uv[VoxelMaterial::n_z][2];
							face.uv[3] = mat.uv[VoxelMaterial::n_z][3];


							face.material = mat.materials[VoxelMaterial::n_z];
							face.type = type;

							mesh.push_back(face);
						}

						// +z
						//if(pChunkManager->IsEmpty(Coord(x, y, z + 1) + chunk_base))
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::p_z) == false)
						{
							VoxelFace face = s_Cube[5];
							face.verts[0] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[1] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[2] += math::Vector3((float)x, (float)y, (float)z);
							face.verts[3] += math::Vector3((float)x, (float)y, (float)z);

							face.uv[0] = mat.uv[VoxelMaterial::p_z][0];
							face.uv[1] = mat.uv[VoxelMaterial::p_z][1];
							face.uv[2] = mat.uv[VoxelMaterial::p_z][2];
							face.uv[3] = mat.uv[VoxelMaterial::p_z][3];


							face.material = mat.materials[VoxelMaterial::p_z];
							face.type = type;

							mesh.push_back(face);
						}
					}
				}
			}

			std::sort(mesh.begin(), mesh.end(), [](VoxelFace& a,VoxelFace& b){return a.material < b.material;});

			if(mesh.size() == 0)
			{
				return;
			}

			pMesh->Reset();

			ChunkMesh::Subset sub;
			sub.type = VT_EMPTY;
			sub.vertexCount				= 0;
			sub.vertexBuffer			= nullptr;

			sub.type					= mesh[0].type;
			sub.material_id				= mesh[0].material;
			pMesh->AllocVertexBuffer((uint32)mesh.size() * 6);

			ChunkMesh::VoxelVertex* pData = (ChunkMesh::VoxelVertex*)pMesh->GetVertexBuffer();

			sub.vertexBuffer = pData;

			for(size_t i = 0; i < mesh.size(); ++i)
			{
				const VoxelFace& face = mesh[i];

				if(face.type != sub.type && sub.vertexCount != 0)
				{
					pMesh->AddSubset(sub);

					sub.type			= face.type;
					sub.material_id		= face.material;
					sub.vertexCount		= 0;
					sub.vertexBuffer	= pData;
				}

				pData->pos = face.verts[0] + vertex_offset;
				pData->normal = face.normal;
				pData->uv = face.uv[0];
				pData->ao = face.ao[0];
				++pData;
				sub.vertexCount++;

				pData->pos = face.verts[1] + vertex_offset;
				pData->normal = face.normal;
				pData->uv = face.uv[1];
				pData->ao = face.ao[1];
				++pData;
				sub.vertexCount++;

				pData->pos = face.verts[2] + vertex_offset;
				pData->normal = face.normal;
				pData->uv = face.uv[2];
				pData->ao = face.ao[2];
				++pData;
				sub.vertexCount++;

				pData->pos = face.verts[1] + vertex_offset;
				pData->normal = face.normal;
				pData->uv = face.uv[1];
				pData->ao = face.ao[1];
				++pData;
				sub.vertexCount++;

				pData->pos = face.verts[3] + vertex_offset;
				pData->normal = face.normal;
				pData->uv = face.uv[3];
				pData->ao = face.ao[3];
				++pData;
				sub.vertexCount++;

				pData->pos = face.verts[2] + vertex_offset;
				pData->normal = face.normal;
				pData->uv = face.uv[2];
				pData->ao = face.ao[2];

				++pData;
				sub.vertexCount++;
			}
			pMesh->AddSubset(sub);
		}
		void Meshizer::AddVoxelMaterial(uint8 type, const VoxelMaterial& mat)
		{
			m_materialMap[type] = mat;
		}
		void Meshizer::GenerateChunkBox(const ChunkKey& key, const Coord& base_coord, ChunkMeshPtr pMesh)
		{
			uint32 nVerts = 24;

			pMesh->AllocVertexBuffer(nVerts);
			
			ChunkMesh::VoxelVertex* data = (ChunkMesh::VoxelVertex*)pMesh->GetVertexBuffer();

			math::Vector3 min_v, max_v;

			min_v = base_coord.ToVector3();
			max_v = min_v + math::Vector3(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE);

			// verticle
			data[0].pos = min_v;
			data[1].pos = math::Vector3(min_v.x, max_v.y, min_v.z);

			data[2].pos = math::Vector3(max_v.x, min_v.y, min_v.z);
			data[3].pos = math::Vector3(max_v.x, max_v.y, min_v.z);

			data[4].pos = math::Vector3(max_v.x, min_v.y, max_v.z);
			data[5].pos = math::Vector3(max_v.x, max_v.y, max_v.z);

			data[6].pos = math::Vector3(min_v.x, min_v.y, max_v.z);
			data[7].pos = math::Vector3(min_v.x, max_v.y, max_v.z);

			// top
			data[8].pos = math::Vector3(min_v.x, max_v.y, min_v.z);
			data[9].pos = math::Vector3(max_v.x, max_v.y, min_v.z);

			data[10].pos = math::Vector3(max_v.x, max_v.y, min_v.z);
			data[11].pos = math::Vector3(max_v.x, max_v.y, max_v.z);

			data[12].pos = math::Vector3(max_v.x, max_v.y, max_v.z);
			data[13].pos = math::Vector3(min_v.x, max_v.y, max_v.z);

			data[14].pos = math::Vector3(min_v.x, max_v.y, min_v.z);
			data[15].pos = math::Vector3(min_v.x, max_v.y, max_v.z);


			// bottom
			data[16].pos = math::Vector3(min_v.x, min_v.y, min_v.z);
			data[17].pos = math::Vector3(max_v.x, min_v.y, min_v.z);

			data[18].pos = math::Vector3(max_v.x, min_v.y, min_v.z);
			data[19].pos = math::Vector3(max_v.x, min_v.y, max_v.z);

			data[20].pos = math::Vector3(max_v.x, min_v.y, max_v.z);
			data[21].pos = math::Vector3(min_v.x, min_v.y, max_v.z);

			data[22].pos = math::Vector3(min_v.x, min_v.y, min_v.z);
			data[23].pos = math::Vector3(min_v.x, min_v.y, max_v.z);

			ChunkMesh::Subset sub;
			sub.vertexBuffer = data;
			sub.vertexCount = nVerts;
			sub.type = -1;
			sub.material_id = 1;

			pMesh->AddSubset(sub);
		}
	}
}
