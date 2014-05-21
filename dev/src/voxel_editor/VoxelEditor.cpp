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

			pWorld->Initialize(nullptr);

			m_pGrid = pCore->CreateGameObject("Grid");

			GridRendererPtr pGridRenderer = std::dynamic_pointer_cast<GridRenderer>(pCore->CreateGameObjectComponent("GridRenderer"));

			pGridRenderer->SetSize(200);
			pGridRenderer->SetGridSize(1);

			m_pGrid->AddComponent(pGridRenderer);

			

			m_pCamera= pCore->CreateGameObject("Camera");

			GameObjectComponentPtr pMD = pCore->CreateGameObjectComponent("Camera");

			m_pCamera->AddComponent(pMD);

			GameObjectComponentPtr pController = pCore->CreateGameObjectComponent("CameraFirstPersonController");
			m_pCamera->AddComponent(pController);

			GameObjectComponentPtr pSkyBox = pCore->CreateGameObjectComponent("SkyBox");
			m_pCamera->AddComponent(pSkyBox);


			m_pCamera->SetTranslation(0, 20, 0);
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
