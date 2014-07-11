#pragma once


class GameSceneManager : public std::enable_shared_from_this<GameSceneManager>
{
public:
	GameSceneManager(void);
	virtual ~GameSceneManager(void);


	bool													Initialize(ld3d::CoreApiPtr pCore);
	void													Release();

	void													Update(float dt);

	bool													MakeCurrentScene(const std::string & sceneName);

	void													ExitScene(const std::string& next_scene);
private:
	void													ProcessSceneSwitch();
private:

	GameScenePtr											m_pCurrent;

	std::map<std::string, GameScenePtr>						m_sceneMap;

	ld3d::CoreApiPtr										m_pCore;

	std::string												m_nextScene;

	bool													m_quitCurrent;
};

