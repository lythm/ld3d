#include "voxel_editor_pch.h"
#include "VoxelEditor.h"

#include <unordered_map>


_DLL_API ld3d::GameInterface* CreateGame()
{
	return new ld3d::voxel::VoxelEditor;
}

_DLL_API void DestroyGame(ld3d::GameInterface* pMod)
{
	delete (ld3d::voxel::VoxelEditor*)pMod;
}

namespace ld3d
{
	namespace voxel
	{
		VoxelEditor::VoxelEditor(void)
		{
		}


		VoxelEditor::~VoxelEditor(void)
		{
		}
		bool VoxelEditor::Initialize(CoreApiPtr pCore)
		{
			WorldPtr pWorld = std::make_shared<World>();

			std::unordered_map<uint32, uint32> map;

			map[0] = 0;


			return true;
		}
		void VoxelEditor::Release()
		{
		}
		bool VoxelEditor::Update(float dt)
		{
			return true;
		}
	}
}