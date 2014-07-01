#pragma once

#include "voxel/voxel_Coord.h"
#include "voxel/voxel_ChunkAdjacency.h"
#include "voxel/voxel_ChunkData.h"

namespace ld3d
{
	namespace voxel
	{
		class _DLL_CLASS Meshizer
		{
			struct VoxelFace
			{
				math::Vector3			verts[4];
				math::Vector3			normal;
				math::Vector3			uv[4];
				uint8					type;
				uint32					material;
				float					ao[4];
				Coord					voxelCoord;
			};

		public:

			struct VoxelMaterial
			{
				enum
				{
					n_x,
					p_x,

					n_y,
					p_y,

					n_z,
					p_z,

					face_count,
				};

				VoxelMaterial()
				{
					type			= VT_EMPTY;
					
					uv[n_x][0]		= math::Vector3(1, 0, 0);
					uv[n_x][1]		= math::Vector3(0, 0, 0);
					uv[n_x][2]		= math::Vector3(1, 1, 0);
					uv[n_x][3]		= math::Vector3(0, 1, 0);

					uv[p_x][0]		= math::Vector3(0, 0, 0);
					uv[p_x][1]		= math::Vector3(0, 1, 0);
					uv[p_x][2]		= math::Vector3(1, 0, 0);
					uv[p_x][3]		= math::Vector3(1, 1, 0);

					uv[n_y][0]		= math::Vector3(0, 1, 0);
					uv[n_y][1]		= math::Vector3(1, 1, 0);
					uv[n_y][2]		= math::Vector3(0, 0, 0);
					uv[n_y][3]		= math::Vector3(1, 0, 0);

					uv[p_y][0]		= math::Vector3(0, 0, 0);
					uv[p_y][1]		= math::Vector3(0, 1, 0);
					uv[p_y][2]		= math::Vector3(1, 0, 0);
					uv[p_y][3]		= math::Vector3(1, 1, 0);

					uv[n_z][0]		= math::Vector3(0, 0, 0);
					uv[n_z][1]		= math::Vector3(0, 1, 0);
					uv[n_z][2]		= math::Vector3(1, 0, 0);
					uv[n_z][3]		= math::Vector3(1, 1, 0);
					
					uv[p_z][0]		= math::Vector3(0, 0, 0);
					uv[p_z][1]		= math::Vector3(1, 0, 0);
					uv[p_z][2]		= math::Vector3(0, 1, 0);
					uv[p_z][3]		= math::Vector3(1, 1, 0);

					materials[n_x]	= -1;
					materials[p_x]	= -1;
					materials[n_y]	= -1;
					materials[p_y]	= -1;
					materials[n_z]	= -1;
					materials[p_z]	= -1;
				}
				uint8									type;
				uint32									materials[face_count];

				// 3 ----- 2
				// |       |
				// |       |
				// 1 ----- 0
				math::Vector3							uv[face_count][4];
			};


			struct VoxelTemplate
			{

			};

			Meshizer(void);
			virtual ~Meshizer(void);

			void										GenerateMesh(const ChunkKey& key, const ChunkData& chunk_data, const ChunkAdjacency& adj, const Coord& base_coord, ChunkMesh* pMesh);
			void										AddVoxelMaterial(uint8 type, const VoxelMaterial& mat);

		private:
			void										InitializeCubeVertex(uint32 size);
			void										GenerateFaceAO(const ChunkKey& key, const ChunkAdjacency& adj, VoxelFace& face);
		private:

			std::map<uint8, VoxelMaterial>				m_materialMap;
	
			VoxelFace									m_Cube[6];
		};
	}
}
