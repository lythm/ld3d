#pragma once
class GameScene
{
public:
	GameScene(GameSceneManagerPtr pManager);
	virtual ~GameScene(void);

	virtual bool											Initialize(ld3d::CoreApiPtr pCore)				= 0;
	virtual void											Release()										= 0;
	virtual void											Update(float dt)								= 0;

	virtual void											Exit(const std::string& next_scene);
protected:
	std::weak_ptr<GameSceneManager>							m_pManager;
};

