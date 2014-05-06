#pragma once


#include "core/GameInterface.h"

#include "voxeldemo.h"
#include "GameServer.h"
#include "GameClient.h"

class Game : public ld3d::GameInterface
{
public:
	Game(void);
	virtual ~Game(void);

	bool									Initialize(ld3d::CoreApiPtr pCore);
	void									Release();
	bool									Update(float dt);

private:


	std::shared_ptr<server::GameServer>		m_pServer;
	std::shared_ptr<client::GameClient>		m_pClient;


	VoxelDemo*								m_pDemo;
};

