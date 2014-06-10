#include "voxel_pch.h"
#include "voxel/voxel_ChunkMeshizer.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_ChunkManager.h"

namespace ld3d
{
	namespace voxel
	{
		ChunkMeshizer::VoxelFace ChunkMeshizer::s_Cube[6];


		// index : 0 - 1 - 2, 1 - 2 - 3
		void ChunkMeshizer::InitializeCubeVertex(uint32 size)
		{
			// -x
			s_Cube[0].verts[0] = math::Vector3(0, 0, 0);
			s_Cube[0].verts[1] = math::Vector3(0, 0, 1);
			s_Cube[0].verts[2] = math::Vector3(0, 1, 0);
			s_Cube[0].verts[3] = math::Vector3(0, 1, 1);

			s_Cube[0].normal = math::Vector3(-1, 0, 0);

			// +x
			s_Cube[1].verts[0] = math::Vector3(1, 0, 0);
			s_Cube[1].verts[1] = math::Vector3(1, 1, 0);
			s_Cube[1].verts[2] = math::Vector3(1, 0, 1);
			s_Cube[1].verts[3] = math::Vector3(1, 1, 1);

			s_Cube[1].normal = math::Vector3(1, 0, 0);

			// -y
			s_Cube[2].verts[0] = math::Vector3(0, 0, 0);
			s_Cube[2].verts[1] = math::Vector3(1, 0, 0);
			s_Cube[2].verts[2] = math::Vector3(0, 0, 1);
			s_Cube[2].verts[3] = math::Vector3(1, 0, 1);

			s_Cube[2].normal = math::Vector3(0, -1, 0);

			// +y
			s_Cube[3].verts[0] = math::Vector3(0, 1, 0);
			s_Cube[3].verts[1] = math::Vector3(0, 1, 1);
			s_Cube[3].verts[2] = math::Vector3(1, 1, 0);
			s_Cube[3].verts[3] = math::Vector3(1, 1, 1);

			s_Cube[3].normal = math::Vector3(0, 1, 0);


			// -z
			s_Cube[4].verts[0] = math::Vector3(0, 0, 0);
			s_Cube[4].verts[1] = math::Vector3(0, 1, 0);
			s_Cube[4].verts[2] = math::Vector3(1, 0, 0);
			s_Cube[4].verts[3] = math::Vector3(1, 1, 0);

			s_Cube[4].normal = math::Vector3(0, 0, -1);

			// +z
			s_Cube[5].verts[0] = math::Vector3(0, 0, 1);
			s_Cube[5].verts[1] = math::Vector3(1, 0, 1);
			s_Cube[5].verts[2] = math::Vector3(0, 1, 1);
			s_Cube[5].verts[3] = math::Vector3(1, 1, 1);

			s_Cube[5].normal = math::Vector3(0, 0, 1);


			for(int i = 0; i < 5; ++i)
			{
				s_Cube[i].verts[0] *= size;
				s_Cube[i].verts[1] *= size;
				s_Cube[i].verts[2] *= size;
				s_Cube[i].verts[3] *= size;
			}
		}

		ChunkMeshizer::ChunkMeshizer(void)
		{
			InitializeCubeVertex(BLOCK_SIZE);
		}


		ChunkMeshizer::~ChunkMeshizer(void)
		{

		}
		void ChunkMeshizer::GenerateMesh(ChunkPtr pChunk, const Coord& base_coord, std::vector<VoxelMesh>& result)
		{
			ChunkManagerPtr pChunkManager = pChunk->GetChunkManager();

			if(pChunk->IsEmpty())
			{
				return;
			}

			Coord chunk_base = pChunk->GetKey().ToChunkOrigin();

			math::Vector3 vertex_offset( base_coord.x, base_coord.y, base_coord.z);

			std::vector<VoxelFace, std_allocator_adapter<VoxelFace>>			mesh(GetAllocator());

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

						const VoxelMaterial& mat = it->second;

						if(type == VT_EMPTY)
						{
							continue;
						}



						// -x
						if(pChunkManager->IsEmpty(Coord(x - 1, y, z) + chunk_base))
						{
							VoxelFace face = s_Cube[0];
							
							face.uv[0] = mat.uv[VoxelMaterial::n_x][0];
							face.uv[1] = mat.uv[VoxelMaterial::n_x][1];
							face.uv[2] = mat.uv[VoxelMaterial::n_x][2];
							face.uv[3] = mat.uv[VoxelMaterial::n_x][3];


							face.material = mat.materials[VoxelMaterial::n_x];
							face.type = type;
							
							mesh.push_back(face);
						}

						// +x
						if(pChunkManager->IsEmpty(Coord(x + 1, y, z) + chunk_base))
						{
							VoxelFace face = s_Cube[1];
							
							face.uv[0] = mat.uv[VoxelMaterial::p_x][0];
							face.uv[1] = mat.uv[VoxelMaterial::p_x][1];
							face.uv[2] = mat.uv[VoxelMaterial::p_x][2];
							face.uv[3] = mat.uv[VoxelMaterial::p_x][3];


							face.material = mat.materials[VoxelMaterial::p_x];
							face.type = type;
							
							mesh.push_back(face);
						}

						// -y
						if(pChunkManager->IsEmpty(Coord(x , y - 1, z) + chunk_base))
						{
							VoxelFace face = s_Cube[2];
							
							face.uv[0] = mat.uv[VoxelMaterial::n_y][0];
							face.uv[1] = mat.uv[VoxelMaterial::n_y][1];
							face.uv[2] = mat.uv[VoxelMaterial::n_y][2];
							face.uv[3] = mat.uv[VoxelMaterial::n_y][3];


							face.material = mat.materials[VoxelMaterial::n_y];
							face.type = type;
							
							mesh.push_back(face);
						}

						// +y
						if(pChunkManager->IsEmpty(Coord(x, y + 1, z) + chunk_base))
						{
							VoxelFace face = s_Cube[3];
							
							face.uv[0] = mat.uv[VoxelMaterial::p_y][0];
							face.uv[1] = mat.uv[VoxelMaterial::p_y][1];
							face.uv[2] = mat.uv[VoxelMaterial::p_y][2];
							face.uv[3] = mat.uv[VoxelMaterial::p_y][3];


							face.material = mat.materials[VoxelMaterial::p_y];
							face.type = type;
							
							mesh.push_back(face);
						}

						// -z
						if(pChunkManager->IsEmpty(Coord(x, y, z - 1) + chunk_base))
						{
							VoxelFace face = s_Cube[4];
							
							face.uv[0] = mat.uv[VoxelMaterial::n_z][0];
							face.uv[1] = mat.uv[VoxelMaterial::n_z][1];
							face.uv[2] = mat.uv[VoxelMaterial::n_z][2];
							face.uv[3] = mat.uv[VoxelMaterial::n_z][3];


							face.material = mat.materials[VoxelMaterial::n_z];
							face.type = type;
							
							mesh.push_back(face);
						}

						// +z
						if(pChunkManager->IsEmpty(Coord(x, y, z + 1) + chunk_base))
						{
							VoxelFace face = s_Cube[5];
							
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

			result.clear();

			if(mesh.size() == 0)
			{
				return;
			}
			

			VoxelMesh sub;
			sub.vertex_buffer.resize(mesh.size() * 6);

			sub.material_id		= mesh[0].material;
			sub.type			= mesh[0].type;

			int vert_index		= 0;

			for(size_t i = 0; i < mesh.size(); ++i)
			{
				const VoxelFace& face = mesh[i];

				if(face.material != sub.material_id && sub.vertex_buffer.size() != 0)
				{
					result.push_back(sub);

					sub.type			= face.type;
					sub.material_id		= face.material;
					vert_index			= 0;

					sub.vertex_buffer.clear();
				}

				VoxelMesh::Vertex v;

				v.pos			= face.verts[0] + vertex_offset;
				v.normal		= face.normal;
				v.uv			= face.uv[0];
				v.color			= face.ao[0];

				sub.vertex_buffer.push_back(v);

				v.pos			= face.verts[1] + vertex_offset;
				v.normal		= face.normal;
				v.uv			= face.uv[1];
				v.color			= face.ao[1];

				sub.vertex_buffer.push_back(v);

				v.pos			= face.verts[2] + vertex_offset;
				v.normal		= face.normal;
				v.uv			= face.uv[2];
				v.color			= face.ao[2];

				sub.vertex_buffer.push_back(v);


				v.pos			= face.verts[1] + vertex_offset;
				v.normal		= face.normal;
				v.uv			= face.uv[1];
				v.color			= face.ao[1];

				sub.vertex_buffer.push_back(v);
				

				v.pos			= face.verts[3] + vertex_offset;
				v.normal		= face.normal;
				v.uv			= face.uv[3];
				v.color			= face.ao[3];

				sub.vertex_buffer.push_back(v);

				v.pos			= face.verts[2] + vertex_offset;
				v.normal		= face.normal;
				v.uv			= face.uv[2];
				v.color			= face.ao[2];

				sub.vertex_buffer.push_back(v);

			}

			result.push_back(sub);

		}
		void ChunkMeshizer::AddVoxelMaterial(uint8 type, const VoxelMaterial& mat)
		{
			m_materialMap[type] = mat;
		}
	}
}
