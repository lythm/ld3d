#include "voxel_editor_pch.h"
#include "VoxelEditor.h"

#include <unordered_map>
extern "C" 
{
#include "sigar/sigar.h"
#include "sigar/sigar_format.h"
}


sigar_t* sig;

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
			sigar_open(&sig);
		}


		VoxelEditor::~VoxelEditor(void)
		{
			sigar_close(sig);
		}
		bool VoxelEditor::Initialize(CoreApiPtr pCore)
		{

			voxel::MeshizerPtr pMeshizer = std::make_shared<voxel::Meshizer>();


			m_pCore = pCore;

			m_pCore->GetRenderManager()->SetGlobalAmbient(math::Color4(0.4f, 0.4f, 0.4f, 1.0f));
			m_pCore->GetRenderManager()->SetClearColor(math::Color4(0.1f, 0.2f, 0.3f, 1));


			pCore->GetCursor()->ConfineCursor(true);
			pCore->GetCursor()->ShowCursor(false);

			pCore->AddEventHandler(EV_KEYBOARD_STATE, boost::bind(&VoxelEditor::_on_key_state, this, _1));
			pCore->AddEventHandler(EV_RESIZE_FRAMEBUFFER, boost::bind(&VoxelEditor::_on_resize, this, _1));


			/*m_pGrid = pCore->CreateGameObject("Grid");

			GridRendererPtr pGridRenderer = std::dynamic_pointer_cast<GridRenderer>(pCore->CreateGameObjectComponent("GridRenderer"));

			pGridRenderer->SetSize(2048);
			pGridRenderer->SetGridSize(16);

			m_pGrid->AddComponent(pGridRenderer);*/

			m_pCamera= pCore->CreateGameObject("Camera");

			CameraDataPtr pMD = std::dynamic_pointer_cast<CameraData>(pCore->CreateGameObjectComponent("Camera"));
			m_pCamera->AddComponent(pMD);
			pMD->SetFarPlane(1024);
			GameObjectComponentPtr pSkyBox = pCore->CreateGameObjectComponent("SkyBox");
			m_pCamera->AddComponent(pSkyBox);

			CameraController_FreePtr pController = std::dynamic_pointer_cast<CameraController_Free>(pCore->CreateGameObjectComponent("CameraFreeController"));
			pController->SetSpeed(10);
			//	pController->Enable(false);
			m_pCamera->AddComponent(pController);

			m_pCamera->SetTranslation(0, 20, 0);


			GameObjectPtr pLight = m_pCore->CreatGameObjectFromTemplate("SkyLight", "light");

			pLight->SetTranslation(-100, 100, 100);
			pLight->LookAt(math::Vector3(0, 0, 0));

			Light_SkyPtr pSkyLight = std::dynamic_pointer_cast<Light_Sky>(pLight->GetComponent("SkyLight"));
		//	pSkyLight->EnableShadow(true);


			m_pWorld = m_pCore->CreatGameObjectFromTemplate("VoxelWorld", "world001");

			VoxelWorldRendererPtr pWorldRenderer = std::dynamic_pointer_cast<VoxelWorldRenderer>(m_pWorld->GetComponent("VoxelWorldRenderer"));
			pWorldRenderer->BindWorldViewPort(m_pCamera);


			GameObjectPtr pObj = pCore->CreateGameObject("Box");
			AABBoxRendererPtr pRenderer = std::dynamic_pointer_cast<AABBoxRenderer>(pCore->CreateGameObjectComponent("AABBoxRenderer"));
			pObj->AddComponent(pRenderer);

			pRenderer->SetAABBox(math::AABBox(math::Vector3(0, 0, 0), math::Vector3(16, 1.5, 2)));

			m_debugInfo = m_pCore->GetDebugPanel()->AddLine();

			*m_debugInfo = "hello";

			m_pCore->RegisterConsoleCommand("set_camera_speed", std::bind(&VoxelEditor::_on_cmd_set_camera_speed, this, std::placeholders::_1, std::placeholders::_2));
			m_pCore->RegisterConsoleCommand("move_to", std::bind(&VoxelEditor::_on_cmd_move_to, this, std::placeholders::_1, std::placeholders::_2));
			m_pCore->RegisterConsoleCommand("regen_mesh", std::bind(&VoxelEditor::_on_cmd_regen_mesh, this, std::placeholders::_1, std::placeholders::_2));

			return true;
		}
		void VoxelEditor::Release()
		{
			m_pCore->RemoveConsoleCommand("set_camera_speed");		
			m_pCore->RemoveConsoleCommand("move_to");		
			m_pCore->RemoveConsoleCommand("regen_mesh");	

			m_pWorld = nullptr;
		}
		bool VoxelEditor::Update(float dt)
		{
			sigar_pid_t pid = sigar_pid_get(sig);
			sigar_proc_mem_t mem;
			int status;

			status = sigar_proc_mem_get(sig, pid, &mem);

			
			math::Vector3 pos = m_pCamera->GetTranslation();

			CameraDataPtr pMD = std::dynamic_pointer_cast<CameraData>(m_pCamera->GetComponent("Camera"));
			CameraPtr pCD = pMD->GetCamera();
			math::Vector3 axis_z = pCD->GetAxisZ();

			std::stringstream s;
			s.precision(3);
			s.setf( std::ios::fixed, std:: ios::floatfield );
			s << "<font style=\"color:#ff9999;\">[camera] " << 
				"pos: " << pos.x << "," << pos.y << "," << pos.z <<
				"dir: " << axis_z.x << "," << axis_z.y << "," << axis_z.z <<"</font><br>";


			VoxelWorldPtr pWorld = std::dynamic_pointer_cast<VoxelWorld>(m_pWorld->GetComponent("VoxelWorld"));
			VoxelWorldRendererPtr pRenderer = std::dynamic_pointer_cast<VoxelWorldRenderer>(m_pWorld->GetComponent("VoxelWorldRenderer"));
			s << "[chunk loader] pending chunk: " << pWorld->GetLoadingQueueSize() 
				<< " chunks: " << pWorld->GetChunkCount()
				<< " faces: " << pWorld->GetFaceCount()
				<< "<br>";
			s << "[world renderer] "<< " faces: " << pRenderer->GetRenderedFaceCount()
				<< " vertex count: " << pRenderer->GetRenderedVertexCount()
				<< " vertex bytes: " << pRenderer->GetRenderedVertexBytes() / 1024.0f / 1024.0f << "M"
				<< "<br>";
				s << "[mem]: " << double(mem.resident) / 1024.0 / 1024.0 << "M";
			*m_debugInfo = s.str();
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
		void VoxelEditor::_on_cmd_set_camera_speed(const ld3d::CommandLine& cl, std::function<void (const std::string&)> writeln)
		{
			if(cl.GetParamCount() != 1)
			{
				writeln("invalid parameter count");
				return;
			}

			float speed = 0;
			try
			{
				speed = boost::lexical_cast<float>(cl.GetParam(0));
			}
			catch(...)
			{
				writeln("invalid parameter");
				return;
			}

			CameraController_FreePtr pController = std::dynamic_pointer_cast<CameraController_Free>(m_pCamera->GetComponent("CameraFreeController"));
			pController->SetSpeed(speed);

			writeln("camera speed: " + cl.GetParam(0));
		}

		void VoxelEditor::_on_cmd_move_to(const ld3d::CommandLine& cl, std::function<void (const std::string&)> writeln)
		{
			if(cl.GetParamCount() != 3)
			{
				writeln("invalid parameter count");
				return;
			}

			int32 x = 0;
			int32 y = 0;
			int32 z = 0;
			try
			{
				x = boost::lexical_cast<int32>(cl.GetParam(0));
				y = boost::lexical_cast<int32>(cl.GetParam(1));
				z = boost::lexical_cast<int32>(cl.GetParam(2));
			}
			catch(...)
			{
				writeln("invalid parameter");
				return;
			}
			m_pCamera->SetTranslation(x, y, z);

		}
		void VoxelEditor::_on_cmd_regen_mesh(const ld3d::CommandLine& cl, std::function<void (const std::string&)> writeln)
		{
			VoxelWorldRendererPtr pRenderer = std::dynamic_pointer_cast<VoxelWorldRenderer>(m_pWorld->GetComponent("VoxelWorldRenderer"));
			pRenderer->RefreshMesh();
		}
	}
}

