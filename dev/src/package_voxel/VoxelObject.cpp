#include "voxel_pch.h"
#include "ext_voxel/VoxelObject.h"

namespace ld3d
{
	VoxelObject::VoxelObject(GameObjectManagerPtr pManager) : GameObjectComponent(L"VoxelObject", pManager)
	{
	}


	VoxelObject::~VoxelObject(void)
	{
	}
	const Version& VoxelObject::GetVersion() const
	{
		return g_packageVersion;
	}
	bool VoxelObject::OnAttach()
	{
		PropertyManagerPtr pPM = std::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"VoxelObject");
		{
			
		}
		pPM->End();
		
		return true;
	}
	void VoxelObject::OnDetach()
	{
	}
}
