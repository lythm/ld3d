#pragma once

#include "GameScene.h"

class Scene_Game : public GameScene
{
public:
	Scene_Game(GameSceneManagerPtr pManager);
	virtual ~Scene_Game(void);

	bool											Initialize(ld3d::CoreApiPtr pCore);
	void											Release();
	void											Update(float dt);


private:
	void											_on_key(ld3d::EventPtr pEvent);

private:
	ld3d::CoreApiPtr								m_pCore;
	ld3d::EventHandlerID							m_ehOnKey;

};

