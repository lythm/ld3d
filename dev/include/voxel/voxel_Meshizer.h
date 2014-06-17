#pragma once

#include "voxel/voxel_Coord.h"

namespace ld3d
{
	namespace voxel
	{
		class _DLL_CLASS Meshizer
		{
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

			virtual void								GenerateMesh(ChunkPtr pChunk, const Coord& base_coord, ChunkMeshPtr pMesh);
			void										AddVoxelMaterial(uint8 type, const VoxelMaterial& mat);
		private:
			static void									InitializeCubeVertex(uint32 size);

		private:

			struct VoxelFace
			{
				math::Vector3			verts[4];
				math::Vector3			normal;
				math::Vector3			uv[4];
				uint8					type;
				uint32					material;
				math::Vector4			ao[4];
			};

			std::map<uint8, VoxelMaterial>				m_materialMap;

			std::map<uint8, VoxelTemplate>				m_templates;


			static VoxelFace							s_Cube[6];
		};
	}
}
