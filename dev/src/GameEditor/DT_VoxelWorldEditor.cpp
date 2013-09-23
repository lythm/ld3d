#include "stdafx.h"
#include "DT_VoxelWorldEditor.h"

namespace dt
{
	ld3d::ExtPackage::ComponentClass							DT_VoxelWorldEditor::s_class(L"DT_VoxelWorldEditor",
																						L"DT",
																						L"Voxel World Editor",

																						&ld3d::Create_Component<DT_VoxelWorldEditor>);
	DT_VoxelWorldEditor::DT_VoxelWorldEditor(ld3d::GameObjectManagerPtr pManager) : GameObjectComponent(L"DT_VoxelWorldEditor", pManager)
	{
		SetVersion(ld3d::Version(0, 0, 0, 1));
	}


	DT_VoxelWorldEditor::~DT_VoxelWorldEditor(void)
	{
	}
	ld3d::ExtPackage::ComponentClass* DT_VoxelWorldEditor::GetClass()
	{
		return &s_class;
	}
}