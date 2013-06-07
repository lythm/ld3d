#pragma once


namespace ld3d
{
	struct VoxelWorldChunk;
	class VoxelWorldRegion
	{
	public:
		VoxelWorldRegion(void);
		virtual ~VoxelWorldRegion(void);

		bool													Initialize();
		void													Release();
		void													Update();
		void													UpdateMesh();
		bool													Empty(uint32 x, uint32 y, uint32 z);
		bool													AddBlock(uint8 vt, uint32 x, uint32 y, uint32 z);
		uint8													GetBlock(uint32 x, uint32 y, uint32 z);
		void													RemoveBlock(uint32 x, uint32 y, uint32 z);
		void													ConvertBlock(uint8 vt, uint32 x, uint32 y, uint32 z);

		bool													InRegion(uint32 x, uint32 y, uint32 z);

		void													FrustumCull(const ViewFrustum& vf);

		VoxelWorldChunk*										GetRenderList();

		uint32													GetFaceCount();

	private:
		bool													MergeWith(VoxelFace& f1, VoxelFace& f2);
		std::vector<VoxelFace>									CombineFace(std::list<VoxelFace>& faces);
		void													AddChunkToRenderList(VoxelWorldChunk* pChunk);
		void													AddChunkToDirtyList(VoxelWorldChunk* pChunk);

		void													GenerateChunkMesh(VoxelWorldChunk* pChunk);
		void													GenChunkMesh(VoxelWorldChunk* pChunk);
		VoxelWorldChunk*										_get_chunk(uint32 x, uint32 y, uint32 z);
		uint8													_get_voxel(uint32 x, uint32 y, uint32 z);
		VoxelWorldChunk*										_add_chunk(uint32 x, uint32 y, uint32 z);

		uint32													_chunk_key(uint32 x, uint32 y, uint32 z);
		uint32													_voxel_region_to_index(uint32 x, uint32 y, uint32 z);
		uint32													_voxel_local_to_index(uint32 x, uint32 y, uint32 z);

		void													_voxel_index_to_region(uint32 chunk_key, uint32 index, uint32& x, uint32& y, uint32& z);
		void													_voxel_index_to_local(uint32 index, uint32& x, uint32& y, uint32& z);
		void													_chunk_key_to_region(uint32 key, uint32& x, uint32& y, uint32 &z);
	private:
		VoxelWorldChunk**										m_pChunkMap;
		VoxelPoolPtr											m_pPool;

		VoxelWorldChunk*										m_pDirtyList;

		VoxelWorldChunk*										m_pRenderList;

		uint32													m_faceCount;

		VoxelWorldOctTreePtr									m_pRoot;
	};
}
