#pragma once

class PlayerController : public ld3d::GameObjectComponent
{
public:
	PlayerController(ld3d::GameObjectManagerPtr pManager);
	virtual ~PlayerController(void);
};

