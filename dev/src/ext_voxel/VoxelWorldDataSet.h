#pragma once

namespace ld3d
{
	struct VoxelWorldChunk;

	class VoxelWorldRegion;

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

		void													GenerateMesh();	


		const std::vector<VoxelFace>&							GetMeshData();
	private:
		
	private:

		VoxelWorldRegion*										m_pRegion;
	};
}
