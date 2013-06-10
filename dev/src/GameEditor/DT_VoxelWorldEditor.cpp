#include "stdafx.h"
#include "DT_VoxelWorldEditor.h"

namespace dt
{
	ld3d::ExtPackage::ComponentClass							DT_VoxelWorldEditor::s_class(L"DT_VoxelWorldEditor",
																						L"DT",
																						L"Voxel World Editor",

																						&DT_VoxelWorldEditor::Create);
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
	ld3d::GameObjectComponentPtr DT_VoxelWorldEditor::Create(ld3d::GameObjectManagerPtr pManager)
	{
		using namespace ld3d;

		return GameObjectComponentPtr(new DT_VoxelWorldEditor(pManager));
	}
	
}