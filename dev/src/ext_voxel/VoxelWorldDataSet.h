#pragma once

namespace ld3d
{
	struct VoxelChunk;
	class VoxelWorldDataSet
	{
	public:
		VoxelWorldDataSet(void);
		virtual ~VoxelWorldDataSet(void);

		bool													Initialize(float voxelSize = 1.0f);
		void													Release();

		void													Update();

		uint8													GetVoxelType(uint32 x, uint32 y, uint32 z);

		bool													AddVoxel(uint8 type, uint32 x, uint32 y, uint32 z);
		void													RemoveVoxel(uint32 x, uint32 y, uint32 z);
		bool													Exist(uint32 x, uint32 y, uint32 z);

		uint8													Pick(const math::Ray& r);

		std::vector<VoxelFace>									GenerateMesh();	

	private:
		uint32													_chunk_key(uint32 x, uint32 y, uint32 z);
		uint32													_voxel_index(uint32 x, uint32 y, uint32 z);

		void													_voxel_index_to_world(VoxelChunk* pChunk, uint32 index, int32& x, int32& y, int32& z);
		void													_voxel_index_to_local(uint32 index, int32& x, int32& y, int32& z);
		void													_chunk_key_to_world(uint32 key, int32& x, int32& y, int32 &z);
	private:

		VoxelChunk**											m_pChunks;

		VoxelPoolPtr											m_pPool;

		int														m_nChunks;

		float													m_voxelSize;
	};
}
