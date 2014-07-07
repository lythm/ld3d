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
				VoxelFaceNormal			normal;
				//math::Vector3			normal;
				math::Vector3			uv[4];
				uint32					material;
				uint8					ao_bits[4];
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
					uv[n_x][2]		= math::Vector3(0, 1, 0);
					uv[n_x][3]		= math::Vector3(1, 1, 0);

					uv[p_x][0]		= math::Vector3(0, 0, 0);
					uv[p_x][1]		= math::Vector3(0, 1, 0);
					uv[p_x][2]		= math::Vector3(1, 1, 0);
					uv[p_x][3]		= math::Vector3(1, 0, 0);

					uv[n_y][0]		= math::Vector3(0, 1, 0);
					uv[n_y][1]		= math::Vector3(1, 1, 0);
					uv[n_y][2]		= math::Vector3(1, 0, 0);
					uv[n_y][3]		= math::Vector3(0, 0, 0);

					uv[p_y][0]		= math::Vector3(0, 0, 0);
					uv[p_y][1]		= math::Vector3(0, 1, 0);
					uv[p_y][2]		= math::Vector3(1, 1, 0);
					uv[p_y][3]		= math::Vector3(1, 0, 0);

					uv[n_z][0]		= math::Vector3(0, 0, 0);
					uv[n_z][1]		= math::Vector3(0, 1, 0);
					uv[n_z][2]		= math::Vector3(1, 1, 0);
					uv[n_z][3]		= math::Vector3(1, 0, 0);

					uv[p_z][0]		= math::Vector3(0, 0, 0);
					uv[p_z][1]		= math::Vector3(1, 0, 0);
					uv[p_z][2]		= math::Vector3(1, 1, 0);
					uv[p_z][3]		= math::Vector3(0, 1, 0);

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

			struct FaceInfo
			{
				FaceInfo()
				{
					type		= VT_EMPTY;
				}
				uint8									type;
				VoxelFace								face;
			};
			struct FaceRegion
			{
				int x1, y1;
				int x2, y2;
				FaceInfo								face;
			};
			struct VoxelTemplate
			{

			};

			Meshizer(void);
			virtual ~Meshizer(void);

			void										GenerateMesh(const ChunkKey& key, const ChunkData& chunk_data, const ChunkAdjacency& adj, const Coord& base_coord, ChunkMesh* pMesh);
			void										AddVoxelMaterial(uint8 type, const VoxelMaterial& mat);

			void										GenerateMeshOpt(const ChunkKey& key, const ChunkData& chunk_data, const ChunkAdjacency& adj, const Coord& base_coord, ChunkMesh* pMesh);

			math::Vector3								VoxelNormalToVector3(VoxelFaceNormal n);
		private:
			uint32										FacesGenOpt(const ChunkKey& key, const ChunkData& chunk_data, const ChunkAdjacency& adj, std::vector<VoxelFace>& faces);
			uint32										FacesGen(const ChunkKey& key, const ChunkData& chunk_data, const ChunkAdjacency& adj, std::vector<VoxelFace>& faces);
			void										MakeFace(int32 x, int32 y, int32 z, uint32 v, const VoxelMaterial& mat, VoxelFace& face);
			void										InitializeCubeVertex(uint32 size);
			void										FaceAO(const ChunkKey& key, const ChunkAdjacency& adj, VoxelFace& face);
			void										MakeMesh(const math::Vector3& vertex_offset, const std::vector<VoxelFace>& mesh, ChunkMesh* pMesh);
			void										MakeMeshIndexed(const math::Vector3& vertex_offset, const std::vector<VoxelFace>& mesh, ChunkMesh* pMesh);

			float										ao_factor(uint8 o);

			bool										FindMaxRegion(FaceInfo* faces, FaceRegion& r);

			void										ReginFacesGen(FaceInfo* face_buffer, uint32 v, int32 axis, std::vector<VoxelFace>& faces);
			VoxelFace									MergeFace(FaceInfo* faces, const FaceRegion& r, uint32 v, int32 axis);

			void										MakeTriangles(const VoxelFace& face, uint32 indices[6]);
		private:


			std::map<uint8, VoxelMaterial>				m_materialMap;

			VoxelFace									m_Cube[6];
		};
	}
}
