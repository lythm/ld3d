#include "solitude_pch.h"
#include "Scene_Title.h"

#include "GameSceneManager.h"


Scene_Title::Scene_Title(GameSceneManagerPtr pManager) : GameScene(pManager)
{
}


Scene_Title::~Scene_Title(void)
{
}
bool Scene_Title::Initialize(ld3d::CoreApiPtr pCore)
{
	using namespace ld3d;
	m_pCore = pCore;

	GameObjectPtr pCamera= pCore->CreateGameObject("MainCamera");

	CameraDataPtr pMD = std::dynamic_pointer_cast<CameraData>(pCore->CreateGameObjectComponent("Camera"));
	pCamera->AddComponent(pMD);
	
	math::RectI rc = pCore->GetScreen()->ScreenRect();

	m_pOL = pCore->GetUIManager()->CreateHtmlOverlay("TitleScene", rc, "file:///assets/solitude/gui/title.html");


	m_ehOnKey = pCore->AddEventHandler(EV_KEYBOARD_STATE, std::bind(&Scene_Title::_on_key, this, std::placeholders::_1));
	return true;
}
void Scene_Title::Release()
{
	m_pCore->RemoveEventHandler(m_ehOnKey);
	m_pOL->Release();
	m_pCore->ResetScene();
}
void Scene_Title::Update(float dt)
{
	
}
void Scene_Title::_on_key(ld3d::EventPtr pEvent)
{
	using namespace ld3d;

	Event_KeyboardState* pState = (Event_KeyboardState*)pEvent.get();

	if(pState->key_code == key_1 && pState->IsKeyUp())
	{
		Exit("Game");
	}
}