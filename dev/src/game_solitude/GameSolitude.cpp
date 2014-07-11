#include "solitude_pch.h"
#include "GameSolitude.h"

_DLL_API ld3d::GameInterface* CreateGame()
{
	return new GameSolitude;
}

_DLL_API void DestroyGame(ld3d::GameInterface* pGame)
{
	delete (GameSolitude*)pGame;
}



GameSolitude::GameSolitude(void)
{
}


GameSolitude::~GameSolitude(void)
{
}
bool GameSolitude::Initialize(ld3d::CoreApiPtr pCore)
{
	m_pCore = pCore;

	return true;
}
void GameSolitude::Release()
{
}
bool GameSolitude::Update(float dt)
{
	return true;
}
