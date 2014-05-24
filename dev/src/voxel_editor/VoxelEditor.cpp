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
			m_pCore = pCore;
			pCore->GetCursor()->ConfineCursor(true);


			pCore->AddEventHandler(EV_KEYBOARD_STATE, boost::bind(&VoxelEditor::_on_key_state, this, _1));


			WorldPtr pWorld = std::make_shared<World>();

			pWorld->Initialize(nullptr);

			m_pGrid = pCore->CreateGameObject("Grid");

			GridRendererPtr pGridRenderer = std::dynamic_pointer_cast<GridRenderer>(pCore->CreateGameObjectComponent("GridRenderer"));

			pGridRenderer->SetSize(2000);
			pGridRenderer->SetGridSize(8);

			m_pGrid->AddComponent(pGridRenderer);



			m_pCamera= pCore->CreateGameObject("Camera");

			GameObjectComponentPtr pMD = pCore->CreateGameObjectComponent("Camera");

			m_pCamera->AddComponent(pMD);

			GameObjectComponentPtr pController = pCore->CreateGameObjectComponent("CameraFirstPersonController");
			m_pCamera->AddComponent(pController);

			GameObjectComponentPtr pSkyBox = pCore->CreateGameObjectComponent("SkyBox");
			m_pCamera->AddComponent(pSkyBox);


			m_pCamera->SetTranslation(0, 20, 0);



			m_pWorld = std::make_shared<World>();
			m_pWorld->Initialize(nullptr);

			return true;
		}
		void VoxelEditor::Release()
		{
			m_pWorld->Release();
		}
		bool VoxelEditor::Update(float dt)
		{
			m_pWorld->Update(dt);
			return true;
		}
		void VoxelEditor::_on_key_state(ld3d::EventPtr pEvent)
		{
			using namespace ld3d;
			Event_KeyboardState* pState = (Event_KeyboardState*)pEvent.get();

			if(pState->key_code == key_escape && pState->keyboard_state->KeyDown(key_escape) == false)
			{
				m_pCore->QuitApp();
			}
			return;
		}
	}
}
