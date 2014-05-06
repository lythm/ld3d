#include "game_pch.h"
#include "GameServer.h"

namespace server
{

	ld3d::Logger				GameServer::s_logger;

	GameServer::GameServer(void)
	{
	}


	GameServer::~GameServer(void)
	{
	}
	bool GameServer::Initialize(ld3d::Logger& logger)
	{
		s_logger = logger;




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

