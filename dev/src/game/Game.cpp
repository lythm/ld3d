#include "game_pch.h"
#include "Game.h"



_DLL_API ld3d::GameInterface* CreateGame()
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
	pCore->GetCursor()->ConfineCursor(true);
	m_pDemo = new VoxelDemo;

	if(m_pDemo->Init(pCore) == false)
	{
		return false;
	}


	m_pServer			= std::make_shared<server::GameServer>();

	if(m_pServer->Initialize(pCore->logger()) == false)
	{
		return false;
	}

	m_pClient			= std::make_shared<client::GameClient>();
	if(m_pClient->Initialize() == false)
	{
		return false;
	}

	return true;
}
void Game::Release()
{
	m_pClient->Release();

	m_pServer->Release();

	//m_pGraphcicsTest->Release();
	m_pDemo->Release();
}
bool Game::Update(float dt)
{
	m_pDemo->Update();


	m_pServer->RunFrame();

	m_pClient->UpdateFrame();
	return true;
}
