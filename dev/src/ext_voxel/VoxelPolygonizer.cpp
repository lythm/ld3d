#include "voxel_pch.h"
#include "VoxelPolygonizer.h"

namespace ld3d
{
	VoxelPolygonizer::VoxelPolygonizer(void)
	{
	}


	VoxelPolygonizer::~VoxelPolygonizer(void)
	{
	}
	
	void VoxelPolygonizer::Reset()
	{

	}
	void VoxelPolygonizer::Process(VoxelWorldPtr pWorld)
	{

	}
	const std::vector<VoxelPolygonizer::Face>& VoxelPolygonizer::GetFaces()
	{
		return m_faces;
	}
}
