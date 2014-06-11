#include "voxel_pch.h"
#include "VoxelWorldRendererImpl2.h"


namespace ld3d
{

	VoxelWorldRendererImpl2::VoxelWorldRendererImpl2(GameObjectManagerPtr pManager) : VoxelWorldRenderer(pManager)
	{
		m_bShowBound = false;

		m_bShowBound = false;
		SetVersion(g_packageVersion);

		
	}


	VoxelWorldRendererImpl2::~VoxelWorldRendererImpl2(void)
	{
	}
	const bool&	VoxelWorldRendererImpl2::GetShowBound()
	{
		return m_bShowBound;
	}
	void VoxelWorldRendererImpl2::SetShowBound(const bool& show)
	{
		m_bShowBound = show;
	}
	bool VoxelWorldRendererImpl2::OnAttach()
	{
		
		RegisterProperty<bool, VoxelWorldRendererImpl2>(this,
				"Show Bound",
				&VoxelWorldRendererImpl2::GetShowBound,
				&VoxelWorldRendererImpl2::SetShowBound);
				
		
		
		return true;
	}
	void VoxelWorldRendererImpl2::OnDetach()
	{
		
	
	}
	void VoxelWorldRendererImpl2::Update(float dt)
	{

	}
	void VoxelWorldRendererImpl2::BindWorldViewPort(GameObjectPtr pNode)
	{
		m_pViewPortRoot = pNode;
	}
	void VoxelWorldRendererImpl2::MoveViewPortTo(uint32 x, uint32 y, uint32 z)
	{

	}
}
