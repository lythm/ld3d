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

			voxel::ChunkMeshizerPtr pMeshizer = std::make_shared<voxel::ChunkMeshizer>();

			



			m_pCore = pCore;
			pCore->GetCursor()->ConfineCursor(true);
			pCore->GetCursor()->ShowCursor(false);

			pCore->AddEventHandler(EV_KEYBOARD_STATE, boost::bind(&VoxelEditor::_on_key_state, this, _1));
			pCore->AddEventHandler(EV_RESIZE_FRAMEBUFFER, boost::bind(&VoxelEditor::_on_resize, this, _1));


			WorldPtr pWorld = std::make_shared<World>();

			pWorld->Initialize(nullptr);

			m_pGrid = pCore->CreateGameObject("Grid");

			GridRendererPtr pGridRenderer = std::dynamic_pointer_cast<GridRenderer>(pCore->CreateGameObjectComponent("GridRenderer"));

			pGridRenderer->SetSize(200);
			pGridRenderer->SetGridSize(8);

			m_pGrid->AddComponent(pGridRenderer);
			
			m_pCamera= pCore->CreateGameObject("Camera");

			CameraDataPtr pMD = std::dynamic_pointer_cast<CameraData>(pCore->CreateGameObjectComponent("Camera"));
			m_pCamera->AddComponent(pMD);

			CameraController_FreePtr pController = std::dynamic_pointer_cast<CameraController_Free>(pCore->CreateGameObjectComponent("CameraFreeController"));
			pController->SetSpeed(50);
			//	pController->Enable(false);
			m_pCamera->AddComponent(pController);

			GameObjectComponentPtr pSkyBox = pCore->CreateGameObjectComponent("SkyBox");
			m_pCamera->AddComponent(pSkyBox);


			m_pCamera->SetTranslation(0, 20, 0);

			m_pWorld = std::make_shared<World>();
			m_pWorld->Initialize(nullptr);


			GameObjectPtr pObj = pCore->CreateGameObject("Box");
			AABBoxRendererPtr pRenderer = std::dynamic_pointer_cast<AABBoxRenderer>(pCore->CreateGameObjectComponent("AABBoxRenderer"));
			pObj->AddComponent(pRenderer);

			pRenderer->SetAABBox(math::AABBox(math::Vector3(-10, -10, -10), math::Vector3(10, 10, 10)));



			m_pWorldVP = std::make_shared<WorldViewport>();

			m_pWorldVP->Open(m_pWorld, Coord(), REGION_SIZE * 3 - 1);

			return true;
		}
		void VoxelEditor::Release()
		{
			m_pWorldVP->Close();

			m_pWorld->Release();
		}
		bool VoxelEditor::Update(float dt)
		{
			m_pWorld->Update(dt);

			m_pWorldVP->Update();
			return true;
		}
		void VoxelEditor::_on_key_state(ld3d::EventPtr pEvent)
		{
			using namespace ld3d;
			Event_KeyboardState* pState = (Event_KeyboardState*)pEvent.get();

			if(pState->key_code == key_escape && pState->IsKeyUp())
			{
				m_pCore->QuitApp();
			}
			if(pState->key_code == key_return && pState->IsKeyUp())
			{
				if(pState->keyboard_state->KeyDown(key_lalt))
				{
					m_pCore->GetScreen()->SetWindowed(!m_pCore->GetScreen()->IsWindowed());
				}
			}

			return;
		}
		void VoxelEditor::_on_resize(ld3d::EventPtr pEvent)
		{
			Event_ResizeFrameBuffer* pResize = (Event_ResizeFrameBuffer*)pEvent.get();
		}
	}
}
