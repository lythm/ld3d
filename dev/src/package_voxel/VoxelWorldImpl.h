#pragma once

#include "packages/voxel/VoxelWorld.h"

namespace ld3d
{
	class VoxelWorldChunk;
	
	class VoxelWorldImpl : public VoxelWorld
	{
	public:

		VoxelWorldImpl(GameObjectManagerPtr pManager);
		virtual ~VoxelWorldImpl(void);

		void										Update(float dt);
		
		const int&									GetVoxelSize();
		void										SetVoxelSize(const int& size);

		const int&									GetWorldSizeY();
		void										SetWorldSizeY(const int& y);

		const int&									GetWorldSizeX();
		void										SetWorldSizeX(const int& x);

		const int&									GetWorldSizeZ();
		void										SetWorldSizeZ(const int& z);

		VoxelWorldChunk*							FrustumCull(ViewFrustum* pVF);

		VoxelWorldDataSetPtr						GetDataSet();
		void										SetDataSet(VoxelWorldDataSetPtr pDataSet);

		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version);

		const math::Matrix44&						GetWorldTransform();
		
		IntersectionResult							Intersect(const math::Ray& r);
	private:

		bool										OnAttach();
		void										OnDetach();

	private:
		int											m_voxelSize;
		int											m_worldSizeX;
		int											m_worldSizeY;
		int											m_worldSizeZ;

		VoxelWorldDataSetPtr						m_pDataSet;

		
	};
}