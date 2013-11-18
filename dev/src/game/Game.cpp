#include "game_pch.h"
#include "Game.h"


#include "utils/Logger.h"

_DLL_API Game* CreateGame()
{
	return new Game;
}

_DLL_API void DestroyGame(ld3d::GameInterface* pGame)
{
	delete (Game*)pGame;
}

Game::Game(void)
{
	m_pDemo = NULL;
}


Game::~Game(void)
{
}
bool Game::Initialize(ld3d::CoreApiPtr pCore)
{
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
bool Game::Update(float dt)
{
	m_pDemo->Update();
	
	return true;
}
