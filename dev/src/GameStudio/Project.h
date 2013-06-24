#pragma once

class Project
{
public:
	Project(GameEnginePtr pEngine);
	virtual ~Project(void);

	bool								Save();
	void								Close();
	bool								Save(const boost::filesystem::path& file);
	bool								Open(const boost::filesystem::path& file);
	bool								New(const boost::filesystem::path& file);

	bool								NewScene();
	bool								SaveScene();
	bool								SaveScene(const boost::filesystem::path& file);
	bool								OpenScene(const boost::filesystem::path& file);

	boost::filesystem::path				RelativeToRoot(const boost::filesystem::path& path);
	boost::filesystem::path				RootPath();
	void								RestoreProjectRoot();

	GameScenePtr						GetGameScene();

	bool								HasSceneFileSpecified();

	boost::filesystem::path				GetSceneFilePath();
private:
	bool								CreateNewProject(const boost::filesystem::path& root);
	bool								CopyDirectory(boost::filesystem::path src, boost::filesystem::path dst);
	

private:
	boost::filesystem::path				m_filePath;

	GameEnginePtr						m_pEngine;
	GameScenePtr						m_pScene;
};

