#include "voxel_pch.h"
#include "voxel/voxel_Meshizer.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_ChunkManager.h"
#include "voxel/voxel_ChunkMesh.h"

namespace ld3d
{
	namespace voxel
	{
		void Meshizer::InitializeCubeVertex(uint32 size)
		{
			// -x
			m_Cube[0].verts[0] = math::Vector3(0, 0, 0);
			m_Cube[0].verts[1] = math::Vector3(0, 0, 1);
			m_Cube[0].verts[2] = math::Vector3(0, 1, 1);
			m_Cube[0].verts[3] = math::Vector3(0, 1, 0);

			m_Cube[0].uv[0]		= math::Vector2(1, 0);
			m_Cube[0].uv[1]		= math::Vector2(0, 0);
			m_Cube[0].uv[2]		= math::Vector2(0, 1);
			m_Cube[0].uv[3]		= math::Vector2(1, 1);

			m_Cube[0].ao_bits[0]		= 0;
			m_Cube[0].ao_bits[1]		= 0;
			m_Cube[0].ao_bits[2]		= 0;
			m_Cube[0].ao_bits[3]		= 0;

			//m_Cube[0].normal = math::Vector3(-1, 0, 0);
			m_Cube[0].normal = VoxelFaceNormal::normal_nx;

			// +x
			m_Cube[1].verts[0] = math::Vector3(1, 0, 0);
			m_Cube[1].verts[1] = math::Vector3(1, 1, 0);
			m_Cube[1].verts[2] = math::Vector3(1, 1, 1);
			m_Cube[1].verts[3] = math::Vector3(1, 0, 1);

			m_Cube[1].uv[0]		= math::Vector2(0, 0);
			m_Cube[1].uv[1]		= math::Vector2(0, 1);
			m_Cube[1].uv[2]		= math::Vector2(1, 1);
			m_Cube[1].uv[3]		= math::Vector2(1, 0);
						
			m_Cube[1].ao_bits[0]		= 0;
			m_Cube[1].ao_bits[1]		= 0;
			m_Cube[1].ao_bits[2]		= 0;
			m_Cube[1].ao_bits[3]		= 0;

			m_Cube[1].normal = VoxelFaceNormal::normal_px;

			// -y
			m_Cube[2].verts[0] = math::Vector3(0, 0, 0);
			m_Cube[2].verts[1] = math::Vector3(1, 0, 0);
			m_Cube[2].verts[2] = math::Vector3(1, 0, 1);
			m_Cube[2].verts[3] = math::Vector3(0, 0, 1);

			m_Cube[2].uv[0]		= math::Vector2(0, 1);
			m_Cube[2].uv[1]		= math::Vector2(1, 1);
			m_Cube[2].uv[2]		= math::Vector2(1, 0);
			m_Cube[2].uv[3]		= math::Vector2(0, 0);

			m_Cube[2].ao_bits[0]		= 0;
			m_Cube[2].ao_bits[1]		= 0;
			m_Cube[2].ao_bits[2]		= 0;
			m_Cube[2].ao_bits[3]		= 0;

			m_Cube[2].normal = VoxelFaceNormal::normal_ny;

			// +y
			m_Cube[3].verts[0] = math::Vector3(0, 1, 0);
			m_Cube[3].verts[1] = math::Vector3(0, 1, 1);
			m_Cube[3].verts[2] = math::Vector3(1, 1, 1);
			m_Cube[3].verts[3] = math::Vector3(1, 1, 0);

			m_Cube[3].uv[0]		= math::Vector2(0, 0);
			m_Cube[3].uv[1]		= math::Vector2(0, 1);
			m_Cube[3].uv[2]		= math::Vector2(1, 1);
			m_Cube[3].uv[3]		= math::Vector2(1, 0);
					

			m_Cube[3].ao_bits[0]		= 0;
			m_Cube[3].ao_bits[1]		= 0;
			m_Cube[3].ao_bits[2]		= 0;
			m_Cube[3].ao_bits[3]		= 0;

			m_Cube[3].normal = VoxelFaceNormal::normal_py;


			// -z
			m_Cube[4].verts[0] = math::Vector3(0, 0, 0);
			m_Cube[4].verts[1] = math::Vector3(0, 1, 0);
			m_Cube[4].verts[2] = math::Vector3(1, 1, 0);
			m_Cube[4].verts[3] = math::Vector3(1, 0, 0);

			m_Cube[4].uv[0]		= math::Vector2(0, 0);
			m_Cube[4].uv[1]		= math::Vector2(0, 1);
			m_Cube[4].uv[2]		= math::Vector2(1, 1);
			m_Cube[4].uv[3]		= math::Vector2(1, 0);

					
			m_Cube[4].ao_bits[0]		= 0;
			m_Cube[4].ao_bits[1]		= 0;
			m_Cube[4].ao_bits[2]		= 0;
			m_Cube[4].ao_bits[3]		= 0;

			m_Cube[4].normal = VoxelFaceNormal::normal_nz;

			// +z
			m_Cube[5].verts[0] = math::Vector3(0, 0, 1);
			m_Cube[5].verts[1] = math::Vector3(1, 0, 1);
			m_Cube[5].verts[2] = math::Vector3(1, 1, 1);
			m_Cube[5].verts[3] = math::Vector3(0, 1, 1);

			m_Cube[5].uv[0]		= math::Vector2(0, 0);
			m_Cube[5].uv[1]		= math::Vector2(1, 0);
			m_Cube[5].uv[2]		= math::Vector2(1, 1);
			m_Cube[5].uv[3]		= math::Vector2(0, 1);
				
			m_Cube[5].ao_bits[0]		= 0;
			m_Cube[5].ao_bits[1]		= 0;
			m_Cube[5].ao_bits[2]		= 0;
			m_Cube[5].ao_bits[3]		= 0;

			m_Cube[5].normal = VoxelFaceNormal::normal_pz;


			for(int i = 0; i < 5; ++i)
			{
				m_Cube[i].verts[0] *= (float)size;
				m_Cube[i].verts[1] *= (float)size;
				m_Cube[i].verts[2] *= (float)size;
				m_Cube[i].verts[3] *= (float)size;
			}
		}

		Meshizer::Meshizer(void)
		{
			InitializeCubeVertex(BLOCK_SIZE);
		}


		Meshizer::~Meshizer(void)
		{
			m_materialMap.clear();
		}
		math::Vector3 Meshizer::VoxelNormalToVector3(VoxelFaceNormal n)
		{
			math::Vector3 v(0, 0, 0);

			switch(n)
			{
			case VoxelFaceNormal::normal_nx:
				v.x = -1.0f;
				break;
			case VoxelFaceNormal::normal_px:
				v.x = 1.0f;
				break;
			case VoxelFaceNormal::normal_ny:
				v.y = -1.0f;
				break;
			case VoxelFaceNormal::normal_py:
				v.y = 1.0f;
				break;
			case VoxelFaceNormal::normal_nz:
				v.z = -1.0f;
				break;
			case VoxelFaceNormal::normal_pz:
				v.z = 1.0f;
				break;
			default:
				break;
			}

			return v;
		}
		void Meshizer::FaceAO(const ChunkKey& key, const ChunkAdjacency& adj, VoxelFace& face)
		{
			//return;

			using namespace math;

			for(int ivert = 0; ivert < 4; ++ivert)
			{
				uint8 ao = 0;
				Vector3 c = face.voxelCoord.ToVector3() + Vector3(0.5f, 0.5f, 0.5f);

				Vector3 v = face.verts[ivert] - c;
				std::vector<Vector3> normals;


				normals.push_back(v);

				normals.push_back(Vector3(0, v.y, v.z));

				normals.push_back(Vector3(v.x, 0, v.z));

				normals.push_back(Vector3(v.x, v.y, 0));

				for(size_t i = 0; i < normals.size(); ++i)
				{
					math::Vector3 vn = VoxelNormalToVector3(face.normal);
					float d = Dot(normals[i], vn);
					if(d <= 0.001f)
					{
						continue;
					}

					Vector3 coord = (c + normals[i] * 2.0f);

					coord.x += coord.x < 0 ? -1 : 0;
					coord.y += coord.y < 0 ? -1 : 0;
					coord.z += coord.z < 0 ? -1 : 0;

					ao += adj.CheckBlock(int32(coord.x), int32(coord.y), (int32)coord.z) ? 1 : 0;
				}

				face.ao_bits[ivert] = ao;
			}
		}
		void Meshizer::GenerateMesh(const ChunkKey& key, const ChunkData& chunk_data, const ChunkAdjacency& adj, const Coord& base_coord, ChunkMesh* pMesh)
		{
			std::vector<VoxelFace>			mesh;

			pMesh->Reset();

			if(0 == FacesGen(key, chunk_data, adj, mesh))
			{
				return;
			}

			Coord chunk_base = key.ToChunkOrigin();

			math::Vector3 vertex_offset( (float)base_coord.x, (float)base_coord.y, (float)base_coord.z);

			MakeMesh(vertex_offset, mesh, pMesh);
		}

		void Meshizer::AddVoxelMaterial(uint8 type, const VoxelMaterial& mat)
		{
			m_materialMap[type] = mat;
		}

		void Meshizer::GenerateMeshOpt(const ChunkKey& key, const ChunkData& chunk_data, const ChunkAdjacency& adj, const Coord& base_coord, ChunkMesh* pMesh)
		{
			std::vector<VoxelFace>			mesh;

			pMesh->Reset();

			if(0 == FacesGenOpt(key, chunk_data, adj, mesh))
			{
				return;
			}

			Coord chunk_base = key.ToChunkOrigin();

			math::Vector3 vertex_offset( (float)base_coord.x, (float)base_coord.y, (float)base_coord.z);

			//MakeMesh(vertex_offset, mesh, pMesh);
			MakeMeshIndexed(vertex_offset, mesh, pMesh);
		}
		uint32 Meshizer::FacesGen(const ChunkKey& key, const ChunkData& chunk_data, const ChunkAdjacency& adj, std::vector<VoxelFace>& faces)
		{
			faces.clear();
			faces.reserve(10000);

			uint32 lod = 0;

			float step = (float)pow(2, lod);

			if(step > 8)
			{
				return 0;
			}

			for(int32 x = 0; x < CHUNK_SIZE; x += step)
			{
				for(int32 y = 0; y < CHUNK_SIZE; y += step)
				{
					for(int32 z = 0; z < CHUNK_SIZE; z += step)
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
							assert(0);
							// no material
							continue;
						}

						const VoxelMaterial& mat = it->second;
						
						// -x
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::n_x) == false)
						{
							VoxelFace face;
							MakeFace(x, y, z, ChunkAdjacency::n_x, mat, face);
							FaceAO(key, adj, face);
							faces.push_back(face);
						}

						// +x
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::p_x) == false)
						{
							VoxelFace face;
							MakeFace(x, y, z, ChunkAdjacency::p_x, mat, face);
							FaceAO(key, adj, face);
							faces.push_back(face);
						}

						// -y
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::n_y) == false)
						{
							VoxelFace face;
							MakeFace(x, y, z, ChunkAdjacency::n_y, mat, face);
							FaceAO(key, adj, face);
							faces.push_back(face);
						}

						// +y
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::p_y) == false)
						{
							VoxelFace face;
							MakeFace(x, y, z, ChunkAdjacency::p_y, mat, face);
							FaceAO(key, adj, face);
							faces.push_back(face);
						}

						// -z
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::n_z) == false)
						{
							VoxelFace face;
							MakeFace(x, y, z, ChunkAdjacency::n_z, mat, face);
							FaceAO(key, adj, face);
							faces.push_back(face);
						}

						// +z
						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::p_z) == false)
						{
							VoxelFace face;
							MakeFace(x, y, z, ChunkAdjacency::p_z, mat, face);
							FaceAO(key, adj, face);
							faces.push_back(face);
						}
					}
				}
			}

			std::sort(faces.begin(), faces.end(), [](VoxelFace& a,VoxelFace& b){return a.material < b.material;});


			return (uint32)faces.size();
		}
		void Meshizer::MakeMeshIndexed(const math::Vector3& vertex_offset, const std::vector<VoxelFace>& mesh, ChunkMesh* pMesh)
		{
			ChunkMesh::Subset sub;
			sub.vertexCount				= 0;
			sub.vertexBuffer			= nullptr;
			sub.indexCount				= 0;
			sub.indexBuffer				= nullptr;

			sub.material_id				= mesh[0].material;
			pMesh->AllocVertexBuffer((uint32)mesh.size() * 4);

			pMesh->AllocIndexBuffer((uint32)mesh.size() * 6);

			ChunkMesh::VoxelVertex* pVBData = (ChunkMesh::VoxelVertex*)pMesh->GetVertexBuffer();
			sub.vertexBuffer	= pVBData;

			uint16*	pIBData					= (uint16*)pMesh->GetIndexBuffer();
			sub.indexBuffer		= pIBData;

		//	uint16 nBaseVert = 0;
			for(size_t i = 0; i < mesh.size(); ++i)
			{
				const VoxelFace& face = mesh[i];

				if(face.material != sub.material_id && sub.vertexCount != 0)
				{
					pMesh->AddSubset(sub);

					sub.material_id		= face.material;
					sub.vertexCount		= 0;
					sub.vertexBuffer	= pVBData;

					sub.indexBuffer		= pIBData;
					sub.indexCount		= 0;

				//	nBaseVert			= 0;
				}

				uint32 indices[6] = {0,1,3,1,2,3,};
				MakeTriangles(face, indices);

				for(int ii = 0; ii < 6; ++ii)
				{
					*pIBData = indices[ii] + sub.vertexCount;

					++pIBData;
					sub.indexCount++;
				}

				//nBaseVert += 4;

				for(int ii = 0; ii < 4; ++ii)
				{
					pVBData->pos = face.verts[ii] + vertex_offset;
					pVBData->normal = (uint32)face.normal;
					pVBData->uv = face.uv[ii];
					pVBData->tex_id = face.tex_id;

					pVBData->ao = ao_factor(face.ao_bits[ii]);
					++pVBData;
					sub.vertexCount++;
				}
			}
			pMesh->AddSubset(sub);

		}
		void Meshizer::MakeMesh(const math::Vector3& vertex_offset, const std::vector<VoxelFace>& mesh, ChunkMesh* pMesh)
		{
			ChunkMesh::Subset sub;
			sub.vertexCount				= 0;
			sub.vertexBuffer			= nullptr;

			sub.material_id				= mesh[0].material;
			pMesh->AllocVertexBuffer((uint32)mesh.size() * 6);

			ChunkMesh::VoxelVertex* pData = (ChunkMesh::VoxelVertex*)pMesh->GetVertexBuffer();

			sub.vertexBuffer = pData;

			for(size_t i = 0; i < mesh.size(); ++i)
			{
				const VoxelFace& face = mesh[i];

				if(face.material != sub.material_id && sub.vertexCount != 0)
				{
					pMesh->AddSubset(sub);

					sub.material_id		= face.material;
					sub.vertexCount		= 0;
					sub.vertexBuffer	= pData;
				}

				uint32 indices[6] = {0,1,3,1,2,3,};
				MakeTriangles(face, indices);

				for(int ii = 0; ii < 6; ++ii)
				{
					int ivert = indices[ii];

					pData->pos = face.verts[ivert] + vertex_offset;
					pData->normal = (uint32)face.normal;
					pData->uv = face.uv[ivert];
					pData->ao = ao_factor(face.ao_bits[ivert]);
					++pData;
					sub.vertexCount++;
				}
			}
			pMesh->AddSubset(sub);
		}
		float Meshizer::ao_factor(uint8 o)
		{
			float ao = 0;

			switch(o)
			{
			case 0:
				ao = 1.0f;
				break;
			case 1:
				ao = 0.65f;
				break;
			case 2:
				ao = 0.5;
				break;
			case 3:
				ao = 0.35f;
				break;
			default:

				ao = 1.0f;
				break;
			}

		//	ao += 0.3f;
			math::Clamp(ao, 0.0f, 1.0f);

			return ao;
		}
		void Meshizer::MakeFace(int32 x, int32 y, int32 z, uint32 v, const VoxelMaterial& mat, VoxelFace& face)
		{
			int32 i_mat_face = -1;
			switch(v)
			{
			case ChunkAdjacency::n_x:
				face				= m_Cube[0];
				i_mat_face			= (int)VoxelFaceNormal::normal_nx;
				break;

			case ChunkAdjacency::p_x:
				face				= m_Cube[1];
				i_mat_face			= (int)VoxelFaceNormal::normal_px;

				break;
			case ChunkAdjacency::n_y:
				face				= m_Cube[2];
				i_mat_face			= (int)VoxelFaceNormal::normal_ny;
				break;
			case ChunkAdjacency::p_y:
				face				= m_Cube[3];
				i_mat_face			= (int)VoxelFaceNormal::normal_py;
				break;
			case ChunkAdjacency::n_z:
				face				= m_Cube[4];
				i_mat_face			= (int)VoxelFaceNormal::normal_nz;
				break;
			case ChunkAdjacency::p_z:
				face				= m_Cube[5];
				i_mat_face			= (int)VoxelFaceNormal::normal_pz;
				break;

			default:
				assert(0);
				return;
			}

			face.material	= mat.materials[i_mat_face];
			face.tex_id		= mat.tex_index[i_mat_face];

			face.verts[0] += math::Vector3((float)x, (float)y, (float)z);
			face.verts[1] += math::Vector3((float)x, (float)y, (float)z);
			face.verts[2] += math::Vector3((float)x, (float)y, (float)z);
			face.verts[3] += math::Vector3((float)x, (float)y, (float)z);
			face.voxelCoord = Coord(x, y, z);

		}
		uint32 Meshizer::FacesGenOpt(const ChunkKey& key, const ChunkData& chunk_data, const ChunkAdjacency& adj, std::vector<VoxelFace>& faces)
		{
			faces.clear();
			faces.reserve(10000);

			
			// -x axis
			for(int x = 0; x < CHUNK_SIZE; ++x)
			{
				FaceInfo face_buffer[CHUNK_SIZE][CHUNK_SIZE];

				int count = 0;
				for(int y = 0; y < CHUNK_SIZE; ++y)
				{
					for(int z = 0; z < CHUNK_SIZE; ++z)
					{
						uint8 type = chunk_data.Get(x, y, z);

						if(type == VT_EMPTY)
						{
							continue;
						}
						
						std::map<uint8, VoxelMaterial>::iterator it = m_materialMap.find(type);
						if(it == m_materialMap.end())
						{
							assert(0);
							// no material
							continue;
						}

						const VoxelMaterial& mat = it->second;

						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::n_x) == false)
						{
							face_buffer[y][z].type = type;

							MakeFace(x, y, z, ChunkAdjacency::n_x, mat, face_buffer[y][z].face);
							FaceAO(key, adj, face_buffer[y][z].face);
							count++;
						}
					}
				}

				if(count == 0)
				{
					continue;
				}

				ReginFacesGen((FaceInfo*)face_buffer, ChunkAdjacency::n_x, x, faces);
			}

			

			// +x axis
			for(int x = 0; x < CHUNK_SIZE; ++x)
			{
				FaceInfo face_buffer[CHUNK_SIZE][CHUNK_SIZE];

				int count = 0;
				for(int y = 0; y < CHUNK_SIZE; ++y)
				{
					for(int z = 0; z < CHUNK_SIZE; ++z)
					{
						uint8 type = chunk_data.Get(x, y, z);

						if(type == VT_EMPTY)
						{
							continue;
						}
						
						std::map<uint8, VoxelMaterial>::iterator it = m_materialMap.find(type);
						if(it == m_materialMap.end())
						{
							assert(0);
							// no material
							continue;
						}

						const VoxelMaterial& mat = it->second;

						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::p_x) == false)
						{
							face_buffer[y][z].type = type;

							MakeFace(x, y, z, ChunkAdjacency::p_x, mat, face_buffer[y][z].face);
							FaceAO(key, adj, face_buffer[y][z].face);
							count++;
						}
					}
				}

				if(count == 0)
				{
					continue;
				}

				ReginFacesGen((FaceInfo*)face_buffer, ChunkAdjacency::p_x, x, faces);
			}

			
			// -y axis
			for(int y = 0; y < CHUNK_SIZE; ++y)
			{
				FaceInfo face_buffer[CHUNK_SIZE][CHUNK_SIZE];

				int count = 0;
				for(int x = 0; x < CHUNK_SIZE; ++x)
				{
					for(int z = 0; z < CHUNK_SIZE; ++z)
					{
						uint8 type = chunk_data.Get(x, y, z);

						if(type == VT_EMPTY)
						{
							continue;
						}
						
						std::map<uint8, VoxelMaterial>::iterator it = m_materialMap.find(type);
						if(it == m_materialMap.end())
						{
							assert(0);
							// no material
							continue;
						}

						const VoxelMaterial& mat = it->second;

						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::n_y) == false)
						{
							face_buffer[x][z].type = type;

							MakeFace(x, y, z, ChunkAdjacency::n_y, mat, face_buffer[x][z].face);
							FaceAO(key, adj, face_buffer[x][z].face);
							count++;
						}
					}
				}

				if(count == 0)
				{
					continue;
				}

				ReginFacesGen((FaceInfo*)face_buffer, ChunkAdjacency::n_y, y, faces);
			}

			

			// +y axis
			for(int y = 0; y < CHUNK_SIZE; ++y)
			{
				FaceInfo face_buffer[CHUNK_SIZE][CHUNK_SIZE];

				int count = 0;
				for(int x = 0; x < CHUNK_SIZE; ++x)
				{
					for(int z = 0; z < CHUNK_SIZE; ++z)
					{
						uint8 type = chunk_data.Get(x, y, z);

						if(type == VT_EMPTY)
						{
							continue;
						}
						
						std::map<uint8, VoxelMaterial>::iterator it = m_materialMap.find(type);
						if(it == m_materialMap.end())
						{
							assert(0);
							// no material
							continue;
						}

						const VoxelMaterial& mat = it->second;

						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::p_y) == false)
						{
							face_buffer[x][z].type = type;

							MakeFace(x, y, z, ChunkAdjacency::p_y, mat, face_buffer[x][z].face);
							FaceAO(key, adj, face_buffer[x][z].face);
							count++;
						}
					}
				}

				if(count == 0)
				{
					continue;
				}

				ReginFacesGen((FaceInfo*)face_buffer, ChunkAdjacency::p_y, y, faces);
			}

			// -z axis
			for(int z = 0; z < CHUNK_SIZE; ++z)
			{
				FaceInfo face_buffer[CHUNK_SIZE][CHUNK_SIZE];

				int count = 0;
				for(int x = 0; x < CHUNK_SIZE; ++x)
				{
					for(int y = 0; y < CHUNK_SIZE; ++y)
					{
						uint8 type = chunk_data.Get(x, y, z);

						if(type == VT_EMPTY)
						{
							continue;
						}
						
						std::map<uint8, VoxelMaterial>::iterator it = m_materialMap.find(type);
						if(it == m_materialMap.end())
						{
							assert(0);
							// no material
							continue;
						}

						const VoxelMaterial& mat = it->second;

						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::n_z) == false)
						{
							face_buffer[x][y].type = type;

							MakeFace(x, y, z, ChunkAdjacency::n_z, mat, face_buffer[x][y].face);
							FaceAO(key, adj, face_buffer[x][y].face);
							count++;
						}
					}
				}

				if(count == 0)
				{
					continue;
				}

				ReginFacesGen((FaceInfo*)face_buffer, ChunkAdjacency::n_z, z, faces);
			}

			// +z axis
			for(int z = 0; z < CHUNK_SIZE; ++z)
			{
				FaceInfo face_buffer[CHUNK_SIZE][CHUNK_SIZE];

				int count = 0;
				for(int x = 0; x < CHUNK_SIZE; ++x)
				{
					for(int y = 0; y < CHUNK_SIZE; ++y)
					{
						uint8 type = chunk_data.Get(x, y, z);

						if(type == VT_EMPTY)
						{
							continue;
						}
						
						std::map<uint8, VoxelMaterial>::iterator it = m_materialMap.find(type);
						if(it == m_materialMap.end())
						{
							assert(0);
							// no material
							continue;
						}

						const VoxelMaterial& mat = it->second;

						if(adj.CheckBlockAdjacency(x, y, z, ChunkAdjacency::p_z) == false)
						{
							face_buffer[x][y].type = type;

							MakeFace(x, y, z, ChunkAdjacency::p_z, mat, face_buffer[x][y].face);
							FaceAO(key, adj, face_buffer[x][y].face);
							count++;
						}
					}
				}

				if(count == 0)
				{
					continue;
				}

				ReginFacesGen((FaceInfo*)face_buffer, ChunkAdjacency::p_z, z, faces);
			}

			std::sort(faces.begin(), faces.end(), [](VoxelFace& a,VoxelFace& b){return a.material < b.material;});
			
			return (uint32)faces.size();
		}
		void Meshizer::ReginFacesGen(FaceInfo* face_buffer, uint32 v, int32 axis, std::vector<VoxelFace>& faces)
		{
			while(true)
			{
				FaceRegion r;
				if(false == FindMaxRegion((FaceInfo*)face_buffer, r))
				{
					break;
				}

				assert(r.x2 >= r.x1);
				assert(r.y2 >= r.y1);


				VoxelFace face = MergeFace((FaceInfo*)face_buffer, r, v, axis);
				faces.push_back(face);

				for(int x = r.x1; x <= r.x2; ++x)
				{
					for(int y = r.y1; y <= r.y2; ++y)
					{
						face_buffer[x * CHUNK_SIZE + y].type = VT_EMPTY;
					}
				}
			}
		}


		bool Meshizer::FindMaxRegion(FaceInfo* faces, FaceRegion& r)
		{
			struct Stride
			{
				int x, y;
				int len;
				FaceInfo face;
			};

			auto face_state_equal = [](const FaceInfo& f1, const FaceInfo& f2)->bool
			{
				if(f2.type == VT_EMPTY || f1.type == VT_EMPTY)
				{
					return false;
				}

				if(f1.face.material != f2.face.material)
				{
					return false;
				}
				if(f1.face.tex_id != f2.face.tex_id)
				{
					return false;
				}
				
				for(int i = 0; i < 4; ++i)
				{
					if(f1.face.ao_bits[i] != f2.face.ao_bits[i])
					{
						return false;
					}
				}

				return true;
			};

			Stride max_v_s;
			max_v_s.len = 0;

			for(int x = 0; x < CHUNK_SIZE; ++x)
			{
				Stride s;
				s.len = 0;
				for(int y = 0; y < CHUNK_SIZE; ++y)
				{
					FaceInfo& f = faces[x * CHUNK_SIZE + y];
					if(f.type != VT_EMPTY)
					{
						s.x = x;
						s.y = y;
						s.face = f;
						s.len = 1;
						break;
					}
				}

				if(s.len == 0)
				{
					continue;
				}

				for(int y = s.y + 1; y < CHUNK_SIZE;++y)
				{
					FaceInfo& f = faces[x * CHUNK_SIZE + y];
					if(face_state_equal(f, s.face) == false)
					{
						break;
					}
					s.len++;
				}

				if(max_v_s.len < s.len)
				{
					max_v_s = s;
				}
			}

			if(max_v_s.len == 0)
			{
				return false;
			}


			std::vector<Stride> h_strides;
			Stride max_h_stride;
			max_h_stride.len = 0;


			for(int y = max_v_s.y; y < max_v_s.y + max_v_s.len; ++y)
			{
				Stride s;
				s.len = 0;
				s.y = y;
				s.face = max_v_s.face;

				for(int x = max_v_s.x; x < CHUNK_SIZE; ++x)
				{
					FaceInfo& f = faces[x * CHUNK_SIZE + y];
					if(face_state_equal(f, s.face) == false)
					{
						break;
					}

					s.len ++;
				}

				s.x = max_v_s.x;

				for(int x = max_v_s.x - 1; x >= 0; --x)
				{
					FaceInfo& f = faces[x * CHUNK_SIZE + y];
					if(face_state_equal(f, s.face) == false)
					{
						break;
					}

					s.len ++;
					s.x = x;
				}

				h_strides.push_back(s);

				if(max_h_stride.len < s.len)
				{
					max_h_stride = s;
				}
			}

			int max_area = 0;

			for(int i = 0; i < h_strides.size(); ++i)
			{
				FaceRegion region;
				Stride s = h_strides[i];

				region.x1 = s.x;
				region.y1 = s.y;
				region.face = s.face;
				int v_len = 1;

				for(int ii = i + 1; ii < h_strides.size(); ++ii)
				{
					if(s.x < h_strides[ii].x || (s.x + s.len - 1) > (h_strides[ii].x + h_strides[ii].len - 1))
					{
						break;
					}

					v_len ++;
				}

				for(int ii = i - 1; ii >= 0; --ii)
				{
					if(s.x < h_strides[ii].x || (s.x + s.len - 1) > (h_strides[ii].x + h_strides[ii].len - 1))
					{
						break;
					}

					v_len ++;
					region.y1--;
				}

				region.x2 = region.x1 + s.len - 1;
				region.y2 = region.y1 + v_len - 1;
				int area = v_len * s.len;
				if(max_area < area)
				{
					max_area = area;
					r = region;
				}
			}
			return true;
		}
		Meshizer::VoxelFace Meshizer::MergeFace(FaceInfo* faces, const FaceRegion& r, uint32 v, int32 axis)
		{
			VoxelFace f = r.face.face;
			
			math::Vector2 uv_scale;
			uv_scale.x = r.y2 + 1 - r.y1;
			uv_scale.y = r.x2 + 1 - r.x1;

			switch(v)
			{
			case ChunkAdjacency::n_x:

				axis = r.face.face.verts[0].x;

				f.verts[0] = math::Vector3(axis, r.x1, r.y1);
				f.verts[1] = math::Vector3(axis, r.x1, r.y2 + 1);
				f.verts[2] = math::Vector3(axis, r.x2 + 1, r.y2 + 1);
				f.verts[3] = math::Vector3(axis, r.x2 + 1, r.y1);

				for(int i = 0; i < 4; ++i)
				{
					f.uv[i].x *= uv_scale.x;
					f.uv[i].y *= uv_scale.y;
				}

				break;
			case ChunkAdjacency::p_x: 
				axis = r.face.face.verts[0].x;
				f.verts[0] = math::Vector3(axis, r.x1, r.y1);
				f.verts[1] = math::Vector3(axis, r.x2 + 1, r.y1);
				f.verts[2] = math::Vector3(axis, r.x2 + 1, r.y2 + 1);
				f.verts[3] = math::Vector3(axis, r.x1, r.y2 + 1);
				
				for(int i = 0; i < 4; ++i)
				{
					f.uv[i].x *= uv_scale.x;
					f.uv[i].y *= uv_scale.y;
				}

				break;
			case ChunkAdjacency::n_y:
			
				axis = r.face.face.verts[0].y;
				f.verts[0] = math::Vector3(r.x1,		axis, r.y1);
				f.verts[1] = math::Vector3(r.x2 + 1,	axis, r.y1);
				f.verts[2] = math::Vector3(r.x2 + 1,	axis, r.y2 + 1);
				f.verts[3] = math::Vector3(r.x1,		axis, r.y2 + 1);


				for(int i = 0; i < 4; ++i)
				{
					f.uv[i].x *= uv_scale.y;
					f.uv[i].y *= uv_scale.x;
				}


				break;
			case ChunkAdjacency::p_y:
				axis = r.face.face.verts[0].y;
				f.verts[0] = math::Vector3(r.x1,		axis, r.y1);
				f.verts[1] = math::Vector3(r.x1,		axis, r.y2 + 1);
				f.verts[2] = math::Vector3(r.x2 + 1,	axis, r.y2 + 1);
				f.verts[3] = math::Vector3(r.x2 + 1,	axis, r.y1);

				for(int i = 0; i < 4; ++i)
				{
					f.uv[i].x *= uv_scale.y;
					f.uv[i].y *= uv_scale.x;
				}

				break;
			case ChunkAdjacency::n_z:
			
				axis = r.face.face.verts[0].z;
				f.verts[0] = math::Vector3(r.x1, r.y1,			axis);
				f.verts[1] = math::Vector3(r.x1, r.y2 + 1,		axis);
				f.verts[2] = math::Vector3(r.x2 + 1, r.y2 + 1,	axis);
				f.verts[3] = math::Vector3(r.x2 + 1, r.y1,		axis);

				for(int i = 0; i < 4; ++i)
				{
					f.uv[i].x *= uv_scale.y;
					f.uv[i].y *= uv_scale.x;
				}


				break;
			case ChunkAdjacency::p_z:
				axis = r.face.face.verts[0].z;

				f.verts[0] = math::Vector3(r.x1,		r.y1,		axis);
				f.verts[1] = math::Vector3(r.x2 + 1,	r.y1,		axis);
				f.verts[2] = math::Vector3(r.x2 + 1,	r.y2 + 1,	axis);
				f.verts[3] = math::Vector3(r.x1,		r.y2 + 1,	axis);


				for(int i = 0; i < 4; ++i)
				{
					f.uv[i].x *= uv_scale.y;
					f.uv[i].y *= uv_scale.x;
				}

				
				break;
			default:
				assert(0);
				break;
			}

			return f;
		}

		void Meshizer::MakeTriangles(const VoxelFace& face, uint32 indices[6])
		{
			int i_max = -1;
			int ao_max = -1;

			for(int i = 0; i < 4; ++i)
			{
				if((int)face.ao_bits[i] > ao_max)
				{
					i_max = i;
					ao_max = face.ao_bits[i];
				}
			}

			indices[0] = i_max % 4;
			indices[1] = (i_max + 1) % 4;
			indices[2] = (i_max + 3) % 4;

			indices[3] = (i_max + 1) % 4;
			indices[4] = (i_max + 2) % 4;
			indices[5] = (i_max + 3) % 4;
		}
	}
}
