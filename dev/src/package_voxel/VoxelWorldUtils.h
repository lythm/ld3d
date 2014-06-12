#pragma once

namespace ld3d
{
	class VoxelWorldMesh;
	class VoxelWorldChunk;

	class VoxelWorldUtils
	{
	public:
		struct VoxelFace
		{
			math::Vector3			verts[4];
			math::Vector3			normal;
			math::Vector2			uv[4];
			uint8					type;
			math::Vector4			ao[4];
		};
		struct FaceRegion
		{
			int x1, y1;
			int x2, y2;
			int type;
		};
		struct BlockMaterial
		{
			uint32											type;
			TexturePtr										pTex;
		};


		static void											GenChunkMesh(VoxelWorldChunk* pChunk);


		static std::vector<FaceRegion>						ExtractRegion(uint8 faces[VOXEL_WORLD_CHUNK_SIZE][VOXEL_WORLD_CHUNK_SIZE]);
		static bool											FindMaxRegion(uint8 faces[VOXEL_WORLD_CHUNK_SIZE][VOXEL_WORLD_CHUNK_SIZE], FaceRegion& r);
	

		/*static void										_voxel_index_to_region(uint32 chunk_key, uint32 index, uint32& x, uint32& y, uint32& z);
		static uint32										_voxel_region_to_index(uint32 x, uint32 y, uint32 z);

		static uint32										_chunk_key(uint32 x, uint32 y, uint32 z);
		
		static uint32										_voxel_local_to_index(uint32 x, uint32 y, uint32 z);

		
		static void											_voxel_index_to_local(uint32 index, uint32& x, uint32& y, uint32& z);
		static void											_chunk_key_to_region(uint32 key, uint32& x, uint32& y, uint32 &z);*/


		static uint32										chunk_local_to_index(uint32 x, uint32 y, uint32 z);
	private:

		static void											GenFaceAO(VoxelWorldChunk* pChunk, VoxelFace& face);


	private:

		VoxelWorldUtils(void){}
		virtual ~VoxelWorldUtils(void){}
	};
}
