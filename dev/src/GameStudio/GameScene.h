#pragma once


class GameScene
{
public:
	GameScene(GameEnginePtr pEngine);
	virtual ~GameScene(void);

	bool										Load(boost::filesystem::path file);
	bool										Save(boost::filesystem::path file);
	bool										Save();
	void										Close();
	bool										New();

	const boost::filesystem::path&				GetFileName();

	ld3d::GameObjectPtr							Root();
	
private:
	void										AddDefaultLight();
private:
	boost::filesystem::path						m_filepath;
	ld3d::CoreApiPtr							m_pCore;

	

	GameEnginePtr								m_pEngine;
};

