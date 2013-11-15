#include "voxel_pch.h"
#include "VoxelWorldBound.h"
#include "VoxelWorldDataSet.h"
#include "VoxelWorldImpl.h"

namespace ld3d
{
	VoxelWorldBound::VoxelWorldBound(void) : Bound(bt_complex)
	{
	}
	
	VoxelWorldBound::~VoxelWorldBound(void)
	{
	}
	IntersectionResult VoxelWorldBound::Intersect(BoundPtr other)
	{
		return IntersectionResult();
	}
	IntersectionResult VoxelWorldBound::Intersect(const math::Ray& r)
	{
		IntersectionResult ret;

		if(m_pWorld == nullptr)
		{
			return ret;
		}

		

		return m_pWorld->Intersect(r);

	}
	void VoxelWorldBound::SetWorld(VoxelWorldImplPtr pWorld)
	{
		m_pWorld = pWorld;
	}
}
