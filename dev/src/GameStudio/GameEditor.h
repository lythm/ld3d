#pragma once

class GameStudio;

class GameEditor
{
public:
	GameEditor(GameStudio* pMainWnd);
	virtual ~GameEditor(void);


	bool														Initialize();
	void														Release();
	void														Reset();

	bool														OpenProject(boost::filesystem::path path);
	bool														NewProject(boost::filesystem::path path);
	bool														SaveProject();
	void														Resize(int w, int h);

	void														Update();

	ProjectPtr													GetProject();

private:
	bool														ResetEngine();

private:
	GameEnginePtr												m_pEngine;
	GameStudio*													m_pMainWnd;

	ProjectPtr													m_pProject;

	OrbitCameraPtr												m_pCamera;
};



