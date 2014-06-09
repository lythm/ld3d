#include "game_pch.h"
#include "GameClient.h"

#include "voxel/voxel_all.h"

namespace client
{
	GameClient::GameClient(void)
	{
	}


	GameClient::~GameClient(void)
	{
	}
	bool GameClient::Initialize()
	{
		using namespace ld3d;
		using namespace ld3d::voxel;


		return true;
	}
	void GameClient::Release()
	{
	}
	void GameClient::UpdateFrame()
	{
	}
}
