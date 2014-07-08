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
				math::Vector2			uv[4];
				uint32					tex_id;
				uint32					material;
				uint8					ao_bits[4];
				Coord					voxelCoord;
			};

		public:

			struct VoxelMaterial
			{
				VoxelMaterial()
				{
					type			= VT_EMPTY;

					materials[(int)VoxelFaceNormal::normal_nx]	= -1;
					materials[(int)VoxelFaceNormal::normal_px]	= -1;
					materials[(int)VoxelFaceNormal::normal_ny]	= -1;
					materials[(int)VoxelFaceNormal::normal_py]	= -1;
					materials[(int)VoxelFaceNormal::normal_nz]	= -1;
					materials[(int)VoxelFaceNormal::normal_pz]	= -1;

					tex_index[(int)VoxelFaceNormal::normal_nx]	= -1;
					tex_index[(int)VoxelFaceNormal::normal_px]	= -1;
					tex_index[(int)VoxelFaceNormal::normal_ny]	= -1;
					tex_index[(int)VoxelFaceNormal::normal_py]	= -1;
					tex_index[(int)VoxelFaceNormal::normal_nz]	= -1;
					tex_index[(int)VoxelFaceNormal::normal_pz]	= -1;
				}
				uint8									type;
				uint32									materials[6];
				uint32									tex_index[6];
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
