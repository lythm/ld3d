#pragma once

#include "core/GameInterface.h"

class GameSolitude: public ld3d::GameInterface
{
public:
	GameSolitude(void);
	virtual ~GameSolitude(void);


	bool											Initialize(ld3d::CoreApiPtr pCore);
	void											Release();
	bool											Update(float dt);


private:
	ld3d::CoreApiPtr								m_pCore;

	GameSceneManagerPtr								m_pSceneManager;
};

