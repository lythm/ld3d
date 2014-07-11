#include "solitude_pch.h"
#include "GameScene.h"
#include "GameSceneManager.h"

GameScene::GameScene(GameSceneManagerPtr pManager)
{
	m_pManager = pManager;
}


GameScene::~GameScene(void)
{
}
void GameScene::Exit(const std::string& next_scene)
{
	GameSceneManagerPtr pManager = m_pManager.lock();
	if(pManager)
	{
		pManager->ExitScene(next_scene);
	}


}