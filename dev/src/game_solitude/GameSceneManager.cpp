#include "solitude_pch.h"
#include "GameSceneManager.h"
#include "Scene_Title.h"
#include "Scene_Game.h"


GameSceneManager::GameSceneManager(void)
{
	m_quitCurrent				= false;
}


GameSceneManager::~GameSceneManager(void)
{
}
bool GameSceneManager::Initialize(ld3d::CoreApiPtr pCore)
{
	m_pCore = pCore;

	m_sceneMap["Title"]			= std::make_shared<Scene_Title>(shared_from_this());
	m_sceneMap["Game"]			= std::make_shared<Scene_Game>(shared_from_this());


	MakeCurrentScene("Game");
	
	return true;
}
void GameSceneManager::Release()
{
	ld3d::_release_and_reset(m_pCurrent);
}
void GameSceneManager::Update(float dt)
{
	m_pCurrent->Update(dt);
	ProcessSceneSwitch();
	
}
void GameSceneManager::ProcessSceneSwitch()
{
	if(m_quitCurrent == false)
	{
		return;
	}
	

	m_quitCurrent = false;


	if(m_nextScene == "")
	{
		m_pCore->QuitApp();
		return;
	}

	if(false == MakeCurrentScene(m_nextScene))
	{
		m_pCore->QuitApp();
		return;
	}
}
bool GameSceneManager::MakeCurrentScene(const std::string & sceneName)
{
	GameScenePtr pScene = m_sceneMap[sceneName];
	if(pScene == nullptr)
	{
		return false;
	}
	if(m_pCurrent)
	{
		m_pCurrent->Release();
	}

	if(pScene->Initialize(m_pCore) == false)
	{
		return false;
	}

	m_pCurrent = pScene;

	return true;
}
void GameSceneManager::ExitScene(const std::string& next_scene)
{
	m_nextScene			= next_scene;
	m_quitCurrent		= true;
}
