#pragma once

namespace ld3d
{
	class VoxelWorldChunk;

	class VoxelWorldRegion;

	class VoxelWorldDataSet
	{
	public:
		VoxelWorldDataSet(void);
		virtual ~VoxelWorldDataSet(void);

		bool													Initialize(int sx, int sy, int sz, float voxelSize = 1.0f);
		void													Release();

		void													Update();

		uint8													GetVoxelType(uint32 x, uint32 y, uint32 z);
		bool													Empty(uint32 x, uint32 y, uint32 z);

		void													ConvertVoxel(uint8 t, uint32 x, uint32 y, uint32 z);
		bool													AddVoxel(uint8 type, uint32 x, uint32 y, uint32 z);
		void													RemoveVoxel(uint32 x, uint32 y, uint32 z);

		void													UpdateMesh();

		VoxelWorldChunk*										FrustumCull(const ViewFrustum& vf);

		uint32													GetFaceCount();

		bool													Serialize(DataStream* pStream);
		bool													UnSerialize(DataStream* pStream);

		const int&												GetWorldSizeY();
		const int&												GetWorldSizeX();
		const int&												GetWorldSizeZ();
		
		bool													Intersect(const math::Ray& r, math::Vector3& pt, math::Vector3& normal);
		bool													Intersect(const math::AABBox& box, math::AABBox& closest_overlap, math::Vector3& penetration);
	private:
		
	private:
		int														m_worldSizeX;
		int														m_worldSizeY;
		int														m_worldSizeZ;

		VoxelWorldRegion*										m_pRegion;
	};
}
