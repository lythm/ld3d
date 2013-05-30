#pragma once

namespace ld3d
{
	class VoxelWorldDataSet
	{
	public:
		VoxelWorldDataSet(void);
		virtual ~VoxelWorldDataSet(void);

		bool													Initialize();
		void													Release();

		void													Update();

		uint8													GetVoxelType(uint32 x, uint32 y, uint32 z);

		bool													AddVoxel(uint8 type, uint32 x, uint32 y, uint32 z);
		void													RemoveVoxel(uint32 x, uint32 y, uint32 z);
		bool													Exist(uint32 x, uint32 y, uint32 z);

		uint8													Pick(const math::Ray& r);
	private:
		uint32													_chunk_key(uint32 x, uint32 y, uint32 z);
		uint32													_voxel_index(uint32 x, uint32 y, uint32 z);
	private:

		struct VoxelChunk
		{
			uint32												key;
			uint8												data[64];
			VoxelChunk*											next;
		};

		VoxelChunk**											m_pChunks;
	};
}
