#include "voxel_pch.h"
#include "..\..\include\ext_voxel\VoxelObjectRenderer.h"


namespace ld3d
{
	VoxelObjectRenderer::VoxelObjectRenderer(GameObjectManagerPtr pManager) : GameObjectComponent(L"VoxelObjectRenderer", pManager)
	{
		SetVersion(g_packageVersion);
	}


	VoxelObjectRenderer::~VoxelObjectRenderer(void)
	{
	}
	void VoxelObjectRenderer::Update(float dt)
	{
		
	}
			
	bool VoxelObjectRenderer::OnAttach()
	{
		PropertyManagerPtr pPM = std::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"VoxelObjectRenderer");
		{
			
		}
		pPM->End();

		return true;
	}
	void VoxelObjectRenderer::OnDetach()
	{
		
	}
}
