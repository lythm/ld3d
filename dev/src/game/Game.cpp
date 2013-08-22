#include "game_pch.h"
#include "Game.h"



EXPORT_C_API Game* CreateGame()
{
	return new Game;
}

EXPORT_C_API void DestroyGame(ld3d::GameInterface* pGame)
{
	delete (Game*)pGame;
}

Game::Game(void)
{
	m_pDemo = NULL;
	m_pGraphcicsTest = nullptr;
}


Game::~Game(void)
{
}
bool Game::Initialize(ld3d::CoreApiPtr pCore)
{
	m_pGraphcicsTest = new GraphicsTest;

	/*if(m_pGraphcicsTest->Init(pCore) == false)
	{
		return false;
	}*/
	m_pDemo = new VoxelDemo;

	if(m_pDemo->Init(pCore) == false)
	{
		return false;
	}
	
	return true;
}
void Game::Release()
{

	//m_pGraphcicsTest->Release();
	m_pDemo->Release();
}
bool Game::Update()
{
	m_pDemo->Update();
	
	return true;
}
void Game::AdjustSysSetting(ld3d::SysSetting& setting)
{
	setting.graphics.sysMod = "./ogl4graphics_x64.dll";
	setting.graphics.windowed = false;
}
