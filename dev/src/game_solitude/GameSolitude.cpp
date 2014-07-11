#include "solitude_pch.h"
#include "GameSolitude.h"

#include "GameSceneManager.h"
#include "GameScene.h"


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
	m_pCore->GetRenderManager()->SetClearColor(math::Color4(0.1f, 0.2f, 0.3f, 1));

	m_pSceneManager = std::make_shared<GameSceneManager>();
	if(m_pSceneManager->Initialize(pCore) == false)
	{
		return false;
	}

	return true;
}
void GameSolitude::Release()
{
	using namespace ld3d;
	_release_and_reset(m_pSceneManager);
}
bool GameSolitude::Update(float dt)
{
	m_pSceneManager->Update(dt);

	return true;
}
