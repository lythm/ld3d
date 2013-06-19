#pragma once
class GameEngine
{
public:
	GameEngine(void);
	virtual ~GameEngine(void);

	bool									Initialize();
	void									Release();

	ld3d::CoreApiPtr						GetCoreApi();

private:
	ld3d::CoreApiPtr						m_pCore;
};

