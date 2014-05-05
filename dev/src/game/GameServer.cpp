#include "game_pch.h"
#include "GameServer.h"

namespace server
{
	GameServer::GameServer(void)
	{
	}


	GameServer::~GameServer(void)
	{
	}
	bool GameServer::Initialize()
	{
		return true;
	}
	void GameServer::Release()
	{
	}
	void GameServer::Run()
	{
		while(true)
		{
			RunFrame();
			ld3d::os_sleep(1);
		}
	}
	void GameServer::RunFrame()
	{

	}
}