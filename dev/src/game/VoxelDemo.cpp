#include "game_pch.h"
#include "VoxelDemo.h"

#include <windowsx.h>

#include "packages/voxel/voxel_ptr.h"
#include "packages/voxel/VoxelWorldGenerator.h"
#include "packages/voxel/VoxelWorld.h"


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

	
	m_pCore->AddEventHandler(EV_KEYBOARD_STATE, boost::bind(&VoxelDemo::_on_key_state, this, _1));

	m_pCore->GetRenderManager()->SetGlobalAmbient(math::Color4(0.4, 0.4f, 0.4f, 1.0f));
	m_pCore->GetRenderManager()->SetClearColor(math::Color4(0.1f, 0.2f, 0.3f, 1));

	
	/*DataStream_File file;
	if(false == file.OpenStream("./projects/2/2.scene"))
	{
	return false;
	}

	if(false == m_pCore->GetScene()->UnSerialize(&file))
	{
	return false;
	}
*/
	
	m_pCamera = m_pCore->CreatGameObjectFromTemplate("Camera", "Camera01");

	m_pCamera->SetTranslation(5, 5, -5);
	m_pCamera->LookAt(math::Vector3(0, 0, 0));

	//m_pCore->CreatGameObjectFromTemplate("Plane", "Plane");

	//GameObjectPtr pSphere = m_pCore->CreatGameObjectFromTemplate("Sphere", "Sphere");

	//pSphere->Translate(0, 2, 0);

	//GameObjectPtr pCube = m_pCore->CreatGameObjectFromTemplate("Cube", "Cube");
	//pCube->SetScale(1, 10, 1);
	//pCube->Translate(0, 5, 0);

	
	//GameObjectPtr pLight = m_pCore->CreatGameObjectFromTemplate("DirectionalLight", "light");

	//pLight->SetTranslation(5, 5, 5);
	//pLight->LookAt(math::Vector3(0, 0, 0));


	m_pWorld = m_pCore->CreatGameObjectFromTemplate("VoxelWorld", "world");

	VoxelWorldPtr pWorld = std::dynamic_pointer_cast<VoxelWorld>(m_pWorld->GetComponent("VoxelWorld"));
	pWorld->SetWorldSizeX(100);
	pWorld->SetWorldSizeY(100);
	pWorld->SetWorldSizeZ(100);

	VoxelWorldGeneratorPtr pGenerator = std::dynamic_pointer_cast<VoxelWorldGenerator>(m_pWorld->GetComponent("VoxelWorldGenerator"));

	pGenerator->RebuildWorld();

	m_pWorld->SetTranslation(-50, 0, -50);

	GameObjectPtr pLight = m_pCore->CreatGameObjectFromTemplate("SkyLight", "light");

	pLight->SetTranslation(-20, 60, 30);
	pLight->LookAt(math::Vector3(0, 0, 0));
	
	
	/*int count = 1;
	for(int x = -count; x <= count; ++x)
	{
		for(int y = -count ; y <= count; ++y)
		{
			if(x == 0 && y == 0)
			{
				continue;
			}
			GameObjectPtr pLight = m_pCore->CreatGameObjectFromTemplate("PointLight", "pl");
			pLight->SetTranslation(10 * x, 3, 10 * y);
		}
	}*/

	/*for(int i = -count; i <= count; ++i)
	{
		if(i == 0)
		{
			continue;
		}

		GameObjectPtr pLight = m_pCore->CreatGameObjectFromTemplate("PointLight", "pl");
		pLight->SetTranslation(0, 3, 10 * i);
	}*/


	//pLight = m_pCore->CreatGameObjectFromTemplate("SpotLight", "pl");
	//pLight->SetTranslation(4, 5, 0);
	//pLight->LookAt(math::Vector3(0, 0, 0));


	//GameObjectPtr pLight = m_pCore->CreatGameObjectFromTemplate("PointLight", "pl");
	//pLight->SetTranslation(0, 3, 0);

//	m_pCore->GetSysInput()->ShowCursor(false);
	return true;
}
void VoxelDemo::Release()
{
	m_pWorld.reset();
}
void VoxelDemo::Update()
{
	math::Vector3 eye = m_pCamera->GetTranslation();

	math::Ray r(math::Vector3(eye.x, 10000, eye.z), math::Vector3(0, -1, 0));

	using namespace ld3d;

	PhysicsManagerPtr pPhy = m_pCore->GetPhysicsManager();

	IntersectionResult ret = pPhy->RayIntersect(r);

	m_pCamera->SetTranslation(eye.x, ret.contact_point.y, eye.z);

}

void VoxelDemo::_on_key_state(ld3d::EventPtr pEvent)
{
	using namespace ld3d;
	Event_KeyboardState* pState = (Event_KeyboardState*)pEvent.get();

	
	if(pState->keyboard_state->KeyDown(key_2) && pState->keyboard_state->KeyDown(key_1))
	{
		return;
	}
	

	if(pState->key_code == key_r && pState->keyboard_state->KeyDown(key_r) == false)
	{

		VoxelWorldGeneratorPtr pGenerator = std::dynamic_pointer_cast<VoxelWorldGenerator>(m_pWorld->GetComponent("VoxelWorldGenerator"));

		pGenerator->RebuildWorld();
		
	}
	return;
}
