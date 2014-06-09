#pragma once

#include "voxel/voxel_Coord.h"

namespace ld3d
{
	namespace voxel
	{
		class _DLL_CLASS ChunkMeshizer
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

				uint8									type;
				uint32									materials[face_count];
				math::Vector3							uv[face_count];
			};


			struct VoxelTemplate
			{

			};


			struct VoxelMesh
			{
				//
				// vector3 pos
				// vector3 normal
				// vector3 uv
				// vector4 color(ao);
				//

				void*									vertexBuffer;
				uint32									vertex_count;
				uint8									type;
				uint32									material_id;
			};

			ChunkMeshizer(void);
			virtual ~ChunkMeshizer(void);

			void										GenerateMesh(ChunkPtr pChunk, const Coord& base_coord, std::vector<VoxelMesh>& result);
			void										AddVoxelMaterial(uint8 type, const VoxelMaterial& mat);
		private:

		private:

			struct VoxelFace
			{
				math::Vector3			verts[4];
				math::Vector3			normal;
				math::Vector2			uv[4];
				uint8					type;
				uint32					material;
				math::Color4			ao[4];
			};

			std::map<uint8, VoxelMaterial>				m_materialMap;

			std::map<uint8, VoxelTemplate>				m_templates;
		};
	}
}
