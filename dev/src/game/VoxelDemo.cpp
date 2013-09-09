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

	m_pCore->AddEventHandler(EV_MOUSE_WHEEL, boost::bind(&VoxelDemo::_on_mouse_wheel, this, _1));
	m_pCore->AddEventHandler(EV_MOUSE_MOVE, boost::bind(&VoxelDemo::_on_mouse_move, this, _1));
	m_pCore->AddEventHandler(EV_MOUSE_BUTTON, boost::bind(&VoxelDemo::_on_mouse_button, this, _1));

	m_pCore->GetRenderManager()->SetGlobalAmbient(math::Color4(0, 0.1f, 0.2f, 1.0f));
	m_pCore->GetRenderManager()->SetClearColor(math::Color4(0.3f, 0.2f, 0.3f, 1));

	m_pCamera = m_pCore->GetGameObjectManager()->alloc_object<ld3d::Camera>();
	m_pCamera->PerspectiveFovLH(0.25f * 3.14f, 4.0f / 3.0f, 0.01f, 10000);
	m_pCamera->LookAtLH(math::Vector3(0, 0, -1), math::Vector3(0, 0, 0), math::Vector3(0, 1, 0));

	m_pCore->AddCamera(m_pCamera);

	m_pRD = std::make_shared<RenderData>();

	m_pRD->geometry = m_pCore->GetRenderManager()->CreateGeometryData();

	struct vertex
	{
		math::Vector3	pos;
		//math::Vector3	normal;
	};


	/*vertex verts[] = 
	{
		{math::Vector3(0, 0, 0), math::Vector3(0, 0, -1), },
		{math::Vector3(1, 0, 0), math::Vector3(0, 0, -1), },
		{math::Vector3(1, 1, 0), math::Vector3(0, 0, -1), },
	};*/

	vertex verts[] = 
	{
		math::Vector3(0, 0, 0), 
		math::Vector3(1, 0, 0), 
		math::Vector3(1, 1, 0), 
	};


	VertexLayout layout;
	layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
	//layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
	m_pRD->geometry->BeginGeometry(PT_TRIANGLE_LIST);
	{
		m_pRD->geometry->AllocVertexBuffer(sizeof(vertex) * 3, verts, false, layout);
	}
	m_pRD->geometry->EndGeometry();


	m_pRD->material = m_pCore->GetRenderManager()->CreateMaterialFromFile("./assets/standard/material/editor_grid.material");

	m_pRD->base_vertex = 0;
	m_pRD->index_count = 0;
	m_pRD->start_index = 0;
	m_pRD->vertex_count = 3;
	m_pRD->world_matrix = math::MatrixIdentity();
	m_pRD->dr = true;




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




	m_pCore->CreatGameObjectFromTemplate("Plane", "Plane");


	GameObjectPtr pSphere = m_pCore->CreatGameObjectFromTemplate("Sphere", "Sphere");

	pSphere->Translate(0, 0, 0);
	pSphere->SetScale(0.7, 0.7, 0.7);


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

}
void VoxelDemo::Update()
{
	//m_pCore->AddRenderData(m_pRD);

	//m_pCore->GetRenderManager()->RenderTest(m_pCamera);
	m_pCore->Render(m_pCamera);
	m_pCore->ClearRenderQueue();

	m_pCore->Present();
}

void VoxelDemo::_on_mouse_move(ld3d::EventPtr pEvent)
{
	using namespace ld3d;
	using namespace math;

	Event_MouseState* pState = (Event_MouseState*)pEvent.get();

	int x =  pState->mouse_state->x;
	int y =  pState->mouse_state->y;
	static int lastx = x;
	static int lasty = y;

	int dx = x - lastx;
	int dy = y - lasty;

	if(pState->mouse_state->LButtonDown())
	{
		Matrix44 view = m_pCamera->GetViewMatrix();
		Vector3 axis_x = m_pCamera->GetAxisX();

		m_pCamera->SetViewMatrix(MatrixRotationAxisY(-dx * 0.01f) * MatrixRotationAxis(-axis_x, dy * 0.01f) * view);
	}

	lastx = x;
	lasty = y;

}

void VoxelDemo::_on_mouse_wheel(ld3d::EventPtr pEvent)
{
	using namespace ld3d;
	using namespace math;

	Event_MouseState* pState = (Event_MouseState*)pEvent.get();


	int zDelta = pState->mouse_state->wheel;

	
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
void VoxelDemo::_on_mouse_button(ld3d::EventPtr pEvent)
{
	using namespace ld3d;
	Event_MouseState* pState = (Event_MouseState*)pEvent.get();
		
}
