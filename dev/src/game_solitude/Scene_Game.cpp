#include "solitude_pch.h"
#include "Scene_Game.h"

#include "GameSceneManager.h"

Scene_Game::Scene_Game(GameSceneManagerPtr pManager) : GameScene(pManager)
{
}


Scene_Game::~Scene_Game(void)
{
}
bool Scene_Game::Initialize(ld3d::CoreApiPtr pCore)
{
	using namespace ld3d;
	m_pCore = pCore;
	GameObjectPtr pCamera= pCore->CreateGameObject("MainCamera");
	CameraDataPtr pMD = std::dynamic_pointer_cast<CameraData>(pCore->CreateGameObjectComponent("Camera"));
	pCamera->AddComponent(pMD);


	m_ehOnKey = pCore->AddEventHandler(EV_KEYBOARD_STATE, std::bind(&Scene_Game::_on_key, this, std::placeholders::_1));
	return true;
}
void Scene_Game::Release()
{
	m_pCore->RemoveEventHandler(m_ehOnKey);
	m_pCore->ResetScene();
}
void Scene_Game::Update(float dt)
{
}
void Scene_Game::_on_key(ld3d::EventPtr pEvent)
{
	using namespace ld3d;
	Event_KeyboardState* pState = (Event_KeyboardState*)pEvent.get();

	if(pState->key_code == key_2 && pState->IsKeyUp())
	{
		m_pManager.lock()->ExitScene("Title");
	}
}
