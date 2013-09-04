#include "game_pch.h"
#include "VoxelDemo.h"

#include <windowsx.h>

VoxelDemo::VoxelDemo(void)
{
	
}


VoxelDemo::~VoxelDemo(void)
{
}
bool VoxelDemo::Init(ld3d::CoreApiPtr pCore)
{
	using namespace ld3d;

	m_pCore = pCore;
		
	m_hEvHandler = m_pCore->AddEventHandler(EV_WINMSG, boost::bind(&VoxelDemo::OnMsg, this, _1));

	m_pCore->GetRenderManager()->SetGlobalAmbient(math::Color4(0, 0.1f, 0.2f, 1.0f));
	m_pCore->GetRenderManager()->SetClearColor(math::Color4(0.3f, 0.2f, 0.3f, 1));

	m_pCamera = m_pCore->GetGameObjectManager()->alloc_object<ld3d::Camera>();
	m_pCamera->PerspectiveFovLH(0.25f * 3.14f, 4.0f / 3.0f, 0.01f, 10000);
	m_pCamera->LookAtLH(math::Vector3(0, 2, -2), math::Vector3(0, 0, 0), math::Vector3(0, 1, 0));

	m_pCore->AddCamera(m_pCamera);

	/*DataStream_File file;
	if(false == file.OpenStream("./projects/2/2.scene"))
	{
		return false;
	}

	if(false == m_pCore->GetScene()->UnSerialize(&file))
	{
		return false;
	}

	m_pCore->CreateGameObjectComponent("VoxelWorld");*/
	
	
	
	
	//m_pCore->CreatGameObjectFromTemplate("Plane", "Plane");


	GameObjectPtr pCube = m_pCore->CreatGameObjectFromTemplate("Cube", "Cube");

	pCube->Translate(0, 0, 0);
	GameObjectPtr pLight = m_pCore->CreatGameObjectFromTemplate("DirectionalLight", "light");

	pLight->SetTranslation(0, 5, -5);
	pLight->LookAt(pCube);

	//
	//pLight = m_pCore->CreatGameObjectFromTemplate("PointLight", "pl");
	//pLight->SetTranslation(0, 5, 0);


	//pLight = m_pCore->CreatGameObjectFromTemplate("SpotLight", "pl");
	//pLight->SetTranslation(5, 5, -5);

	//pLight->LookAt(pCube);


	return true;
}
void VoxelDemo::Release()
{
	m_pCore->RemoveEventHandler(m_hEvHandler);
}
void VoxelDemo::Update()
{
	m_pCore->Render(m_pCamera);
	m_pCore->ClearRenderQueue();

	m_pCore->Present();
}
void VoxelDemo::OnMsg(ld3d::EventPtr pEvent)
{
	using namespace ld3d;
	using namespace math;

	std::shared_ptr<Event_WindowMessage> pMsg = std::dynamic_pointer_cast<Event_WindowMessage>(pEvent);

	switch(pMsg->msg.message)
	{
	case WM_MOUSEMOVE:
		{
			int x =  GET_X_LPARAM(pMsg->msg.lParam);
			int y =  GET_Y_LPARAM(pMsg->msg.lParam); ;
			static int lastx = x;
			static int lasty = y;

			int dx = x - lastx;
			int dy = y - lasty;

			if(pMsg->msg.wParam & MK_LBUTTON)
			{
				Matrix44 view = m_pCamera->GetViewMatrix();
				Vector3 axis_x = m_pCamera->GetAxisX();

				m_pCamera->SetViewMatrix(MatrixRotationAxisY(-dx * 0.01f) * MatrixRotationAxis(-axis_x, dy * 0.01f) * view);
			}

			lastx = x;
			lasty = y;
		}
		break;

	case WM_MOUSEWHEEL:
		{
			int zDelta = -GET_WHEEL_DELTA_WPARAM(pMsg->msg.wParam);

			using namespace math;

			Matrix44 view = m_pCamera->GetViewMatrix();
			Vector3 axis_z = m_pCamera->GetAxisZ();

			m_pCamera->SetViewMatrix( MatrixTranslation(0.01f * zDelta * axis_z) * view);

			view = m_pCamera->GetViewMatrix();
			math::Vector3 eye(0, 0, 0);
			math::Vector3 up = m_pCamera->GetAxisY();
			math::Vector3 forward = m_pCamera->GetAxisZ();
			
			view.Invert();
			math::TransformCoord(eye, view);

			m_pCore->GetSysSound()->SetListenerAttr(eye, math::Vector3(), forward, up);

		}
		break;

	default:
		break;
	}
}
