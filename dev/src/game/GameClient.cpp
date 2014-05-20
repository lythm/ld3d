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

		Chunk ck;

		ck[0] = 1;

		uint8 v = ck[0];
		return true;
	}
	void GameClient::Release()
	{
	}
	void GameClient::UpdateFrame()
	{
	}
}
