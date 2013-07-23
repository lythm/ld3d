#pragma once

class GameStudio;

class GameEditor : public std::enable_shared_from_this<GameEditor>
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

	bool														NewScene();
	bool														OpenScene(boost::filesystem::path path);
	bool														SaveScene();
	bool														SaveScene(boost::filesystem::path path);

	void														Update();

	ProjectPtr													GetProject();
	void														on_resize(QResizeEvent* e);
	void														on_mouse_move(QMouseEvent* e);
	void														on_mouse_wheel(QWheelEvent* e);
	void														on_mouse_press(QMouseEvent* e);
	void														on_mouse_release(QMouseEvent* e);;

	void														on_idle();

	void														UpdateHierarchyView();
	void														UpdateInspectorView();
	void														ClearInspectorView();
	void														ClearHierarchyView();

	boost::filesystem::path										GetSceneFile();

	void														SetCurrentObject(ld3d::GameObject* pObj);
	ld3d::GameObject*											GetCurrentObject();

	GameEnginePtr												GetGameEngine();
private:
	bool														ResetEngine();

private:
	GameEnginePtr												m_pEngine;
	GameStudio*													m_pMainWnd;
	ProjectPtr													m_pProject;
	OrbitCameraPtr												m_pCamera;

	MenuManagerPtr												m_pMenuManager;

	ld3d::GameObject*											m_pCurrentObject;
};
