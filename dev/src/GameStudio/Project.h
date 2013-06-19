#pragma once

class Project
{
public:
	Project(void);
	virtual ~Project(void);


	void								Close();
	void								Save();
	void								Open();
	bool								New(const boost::filesystem::path& file);

	boost::filesystem::path				RelativeToRoot(const boost::filesystem::path& path);
	boost::filesystem::path				RootPath();
	void								RestoreProjectRoot();
private:
	bool								CreateNewProject(const boost::filesystem::path& root);
	bool								CopyDirectory(boost::filesystem::path src, boost::filesystem::path dst);
	

private:
	boost::filesystem::path				m_filePath;

	GameScenePtr						m_pScene;

	GameEnginePtr						m_pEngine;
};

