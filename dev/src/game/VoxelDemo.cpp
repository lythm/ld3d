#include "game_pch.h"
#include "VoxelDemo.h"

#include <windowsx.h>

#include "packages/core/core_ext_all.h"
#include "packages/voxel/voxel_all.h"

#include "PlayerController.h"

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

	m_pCore->RegisterConsoleCommand("rebuild_world", std::bind(&VoxelDemo::_on_cmd_rebuild, this, std::placeholders::_1, std::placeholders::_2));
	

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
	m_pPlayer = CreatePlayer();

	m_pCamera = m_pCore->CreatGameObjectFromTemplate("Camera", "Camera01");

	m_pCamera->SetTranslation(0, 3, -1);
	m_pCamera->LookAt(math::Vector3(0, 2, 1));

	m_pCamera->LinkTo(m_pPlayer);
	
	//m_pCore->CreatGameObjectFromTemplate("Plane", "Plane");

	//GameObjectPtr pSphere = m_pCore->CreatGameObjectFromTemplate("Sphere", "Sphere");

	//pSphere->Translate(0, 2, 0);

	//GameObjectPtr pCube = m_pCore->CreatGameObjectFromTemplate("Cube", "Cube");
	//pCube->SetScale(1, 10, 1);
	//pCube->Translate(0, 5, 0);

	
	//GameObjectPtr pLight = m_pCore->CreatGameObjectFromTemplate("DirectionalLight", "light");

	//pLight->SetTranslation(5, 5, 5);
	//pLight->LookAt(math::Vector3(0, 0, 0));


//	m_pWorld = m_pCore->CreatGameObjectFromTemplate("VoxelWorld", "world");
//
//	VoxelWorldPtr pWorld = std::dynamic_pointer_cast<VoxelWorld>(m_pWorld->GetComponent("VoxelWorld"));
//	pWorld->SetWorldSizeX(100);
//	pWorld->SetWorldSizeY(100);
//	pWorld->SetWorldSizeZ(100);
//
//	VoxelWorldGeneratorPtr pGenerator = std::dynamic_pointer_cast<VoxelWorldGenerator>(m_pWorld->GetComponent("VoxelWorldGenerator"));
//
//	pGenerator->RebuildWorld();
//
//	m_pWorld->SetTranslation(-50, 0, -50);
//
//	GameObjectPtr pLight = m_pCore->CreatGameObjectFromTemplate("SkyLight", "light");
//
//	pLight->SetTranslation(-20, 60, 30);
//	pLight->LookAt(math::Vector3(0, 0, 0));
//	
//	
//	/*int count = 1;
//	for(int x = -count; x <= count; ++x)
//	{
//		for(int y = -count ; y <= count; ++y)
//		{
//			if(x == 0 && y == 0)
//			{
//				continue;
//			}
//			GameObjectPtr pLight = m_pCore->CreatGameObjectFromTemplate("PointLight", "pl");
//			pLight->SetTranslation(10 * x, 3, 10 * y);
//		}
//	}*/
//
//	/*for(int i = -count; i <= count; ++i)
//	{
//		if(i == 0)
//		{
//			continue;
//		}
//
//		GameObjectPtr pLight = m_pCore->CreatGameObjectFromTemplate("PointLight", "pl");
//		pLight->SetTranslation(0, 3, 10 * i);
//	}*/
//
//
//	//pLight = m_pCore->CreatGameObjectFromTemplate("SpotLight", "pl");
//	//pLight->SetTranslation(4, 5, 0);
//	//pLight->LookAt(math::Vector3(0, 0, 0));
//
//
//	//GameObjectPtr pLight = m_pCore->CreatGameObjectFromTemplate("PointLight", "pl");
//	//pLight->SetTranslation(0, 3, 0);
//
//	math::Ray r(math::Vector3(0, 1000, 0), math::Vector3(0, -1, 0));
//	Contact ret = m_pCore->GetPhysicsManager()->RayIntersect(r);
//	m_pPlayer->SetTranslation(1, ret.enter_point.y + 10, 1);
//
////	m_pCore->GetSysInput()->ShowCursor(false);
//

	return true;
}
void VoxelDemo::Release()
{
	/*m_pCore->RemoveConsoleCommand("rebuild_world");		

	m_pPlayer->Clear();
	m_pPlayer.reset();
	m_pWorld.reset();*/
}
void VoxelDemo::Update()
{
}

void VoxelDemo::_on_key_state(ld3d::EventPtr pEvent)
{
	//using namespace ld3d;
	//Event_KeyboardState* pState = (Event_KeyboardState*)pEvent.get();

	//
	//if(pState->keyboard_state->KeyDown(key_2) && pState->keyboard_state->KeyDown(key_1))
	//{
	//	return;
	//}
	//

	////if(pState->key_code == key_r && pState->keyboard_state->KeyDown(key_r) == false)
	////{

	////	VoxelWorldGeneratorPtr pGenerator = std::dynamic_pointer_cast<VoxelWorldGenerator>(m_pWorld->GetComponent("VoxelWorldGenerator"));

	////	pGenerator->RebuildWorld();
	////	
	////}

	//if(pState->key_code == key_escape && pState->keyboard_state->KeyDown(key_escape) == false)
	//{
	//	m_pCore->QuitApp();
	//}
	//return;
}
ld3d::GameObjectPtr VoxelDemo::CreatePlayer()
{
	/*using namespace ld3d;

	GameObjectPtr pTop = m_pCore->CreateGameObject("PlayerTop");

	MeshDataPtr pMesh = std::dynamic_pointer_cast<MeshData>(m_pCore->GetGameObjectManager()->CreateComponent("MeshData"));
	pMesh->SetMeshAsset("_cube_");
	pTop->AddComponent(pMesh);

	GameObjectComponentPtr pRenderer = m_pCore->GetGameObjectManager()->CreateComponent("MeshRenderer");

	pTop->AddComponent(pRenderer);
	
	GameObjectPtr pBottom = m_pCore->CreateGameObject("PlayerBottom");

	pMesh = std::dynamic_pointer_cast<MeshData>(m_pCore->GetGameObjectManager()->CreateComponent("MeshData"));
	pMesh->SetMeshAsset("_cube_");
	pBottom->AddComponent(pMesh);

	pRenderer = m_pCore->GetGameObjectManager()->CreateComponent("MeshRenderer");

	pBottom->AddComponent(pRenderer);

	GameObjectPtr pPlayerMesh = m_pCore->CreateGameObject("PlayerMesh");

	pBottom->SetLocalTransform(math::MatrixTranslation(math::Vector3(0, 0.5, 0)));
	pTop->SetLocalTransform(math::MatrixTranslation(math::Vector3(0, 1.5, 0)));
	pTop->LinkTo(pPlayerMesh);
	pBottom->LinkTo(pPlayerMesh);

	
	GameObjectPtr pPlayer = m_pCore->CreateGameObject("Player");
	pPlayerMesh->LinkTo(pPlayer);

	GameObjectComponentPtr pController = m_pCore->GetGameObjectManager()->alloc_object<PlayerController>(m_pCore->GetGameObjectManager());

	pPlayer->AddComponent(pController);

	CollisionData_AABBoxPtr pCD = std::dynamic_pointer_cast<CollisionData_AABBox>(m_pCore->GetGameObjectManager()->CreateComponent("CollisionData_AABBox"));
	math::AABBox box;
	box.Make(math::Vector3(0, 0, 0), math::Vector3(1, 2, 1));
	pCD->SetAABBox(box);
	pPlayer->AddComponent(pCD);

	pCD->SetHandler(std::bind(&PlayerController::_on_collide, (PlayerController*)pController.get(), std::placeholders::_1, std::placeholders::_2));

	return pPlayer;*/

	return nullptr;
}
void VoxelDemo::_on_cmd_rebuild(const ld3d::CommandLine& cl, std::function<void (const std::string&)> writeln)
{
	/*using namespace ld3d;

	VoxelWorldGeneratorPtr pGenerator = std::dynamic_pointer_cast<VoxelWorldGenerator>(m_pWorld->GetComponent("VoxelWorldGenerator"));
	pGenerator->RebuildWorld();
	writeln("world is rebuilt.");*/
}
