#include "voxel_pch.h"
#include "VoxelWorldRenderData.h"

namespace ld3d
{
	VoxelWorldRenderData::VoxelWorldRenderData(void)
	{
	}


	VoxelWorldRenderData::~VoxelWorldRenderData(void)
	{
	}
	bool VoxelWorldRenderData::Initialize(MaterialPtr pMaterial)
	{
		m_pMaterial = pMaterial;
		return true;
	}
	void VoxelWorldRenderData::Release()
	{
	}
	void VoxelWorldRenderData::Render_Depth(Sys_GraphicsPtr pSysGraphics)
	{
	}
	void VoxelWorldRenderData::Render(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial)
	{
	}
	MaterialPtr VoxelWorldRenderData::GetMaterial()
	{
		return m_pMaterial;
	}
	math::Matrix44 VoxelWorldRenderData::GetWorldMatrix()
	{
		return math::MatrixIdentity();
	}
	bool VoxelWorldRenderData::IsDeferred()
	{
		return true;
	}
}