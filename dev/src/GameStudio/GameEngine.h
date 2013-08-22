#pragma once
class GameEngine
{
public:
	GameEngine(void);
	virtual ~GameEngine(void);

	bool									Initialize(QWidget* pTarget);
	void									Release();

	ld3d::CoreApiPtr						GetCoreApi();

	void									Update();
	void									Render();
	void									Render(ld3d::CameraPtr pCamera);

	void									ShowGrid(bool bShow);
	bool									GridVisible();

	void									OnResize(int w, int h);

	ld3d::GameObjectPtr						RootObject();

	void									CreateObject_Empty();
	ld3d::GameObjectPtr						CreateObject(const std::string& name);
	ld3d::GameObjectPtr						CreateObjectFromTpl(const std::string& name, const std::string& tpl);
	ld3d::GameObjectComponentPtr			CreateGameObjectComponent(const std::string& name);

private:
	ld3d::CoreApiPtr						m_pCore;

	GridMeshPtr								m_pGrid;
	bool									m_bShowGrid;
	ld3d::RenderManagerPtr					m_pRenderManager;

	int										m_objNo;

};

