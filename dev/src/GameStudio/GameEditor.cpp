#include "stdafx.h"
#include "GameEditor.h"
#include "GameEngine.h"
#include "Project.h"
#include "gamestudio.h"
#include "form_scene.h"
#include "OrbitCamera.h"
#include "form_hierarchy.h"
#include "menumanager.h"
#include "form_inspector.h"
GameEditor::GameEditor(GameStudio* pMainWnd)
{
	m_pMainWnd = pMainWnd;
	m_pCurrentObject = nullptr;
}


GameEditor::~GameEditor(void)
{

}
bool GameEditor::Initialize()
{
	m_pMainWnd->GetFormScene()->InstallDelegates(shared_from_this());
	m_pMainWnd->GetFormHierarchy()->on_current_changed = std::bind(&GameEditor::SetCurrentObject, this, std::placeholders::_1);
	m_pCamera = alloc_shared<OrbitCamera>();

	m_pMenuManager = alloc_shared<MenuManager>(m_pMainWnd);
	m_pMenuManager->on_action_triggered = std::bind(&GameEditor::UpdateHierarchyView, this);
	return true;
}
void GameEditor::Release()
{
	m_pMainWnd->GetFormScene()->UnInstallDelegates();
	ClearHierarchyView();
	ClearInspectorView();

	if(m_pProject)
	{
		m_pProject->Close();
		m_pProject.reset();
	}

	if(m_pEngine)
	{
		m_pEngine->Release();
		m_pEngine.reset();
	}

	m_pCamera.reset();

	m_pMenuManager->Clear();
	m_pMenuManager.reset();
}
void GameEditor::Reset()
{
	Release();
	Initialize();
}

bool GameEditor::ResetEngine()
{
	if(m_pEngine)
	{
		m_pEngine->Release();
		m_pEngine.reset();
	}

	m_pEngine = alloc_shared<GameEngine>();
	if(m_pEngine->Initialize(m_pMainWnd->GetFormScene()) == false)
	{
		return false;
	}

	QSize size = m_pMainWnd->GetFormScene()->size();

	m_pCamera->SetViewPort(size.width(), size.height());

	return true;
}
void GameEditor::Update()
{
	if(m_pCamera)
	{
		m_pCamera->Update();
	}
	if(m_pEngine)
	{
		m_pEngine->Update();
		m_pEngine->Render(m_pCamera);
	}
}
void GameEditor::Resize(int w, int h)
{
	if(w <= 0 || h <=0 || m_pEngine == nullptr)
	{
		return;
	}

	m_pEngine->Resize(w, h);
}
bool GameEditor::OpenProject(boost::filesystem::path path)
{
	ClearHierarchyView();
	if(m_pProject != nullptr)
	{
		m_pProject->Save();
		m_pProject->Close();
	}

	ResetEngine();

	m_pProject = alloc_shared<Project>(m_pEngine);
	
	if(m_pProject->Open(path) == false)
	{
		m_pProject->Close();
		m_pProject.reset();
		return false;
	}
	UpdateHierarchyView();
	m_pMenuManager->Reset(shared_from_this());
	return true;
}
bool GameEditor::NewProject(boost::filesystem::path path)
{
	ClearHierarchyView();
	if(m_pProject != nullptr)
	{
		m_pProject->Save();
		m_pProject->Close();
	}

	ResetEngine();
	m_pProject = alloc_shared<Project>(m_pEngine);
	
	if(m_pProject->New(path) == false)
	{
		m_pProject->Close();
		m_pProject.reset();
		return false;
	}

	UpdateHierarchyView();

	m_pMenuManager->Reset(shared_from_this());
	return true;
}
ProjectPtr GameEditor::GetProject()
{
	return m_pProject;
}
bool GameEditor::SaveProject()
{
	return m_pProject->Save();
}

void GameEditor::on_resize(QResizeEvent* e)
{
	QSize size = e->size();

	m_pCamera->SetViewPort(size.width(), size.height());
	if(m_pEngine)
	{
		m_pEngine->Resize(size.width(), size.height());
	}
}
void GameEditor::on_mouse_move(QMouseEvent* e)
{
	using namespace math;
	QPoint point = e->pos();
	static QPoint lastpt = point;
	QPoint delta = point - lastpt;

	if(e->buttons() & Qt::MiddleButton && e->modifiers() & Qt::ControlModifier)
	{
		m_pCamera->Rotate(delta.x(), delta.y());
	}
	else if(e->buttons() & Qt::MiddleButton)
	{
		m_pCamera->Move(delta.x(), delta.y());
	}
	lastpt = point;

	//m_pMainWnd->logInfo("mouse move");
}
void GameEditor::on_mouse_wheel(QWheelEvent* e)
{
	m_pCamera->Zoom(e->delta());
}
void GameEditor::on_mouse_press(QMouseEvent* e)
{
}
void GameEditor::on_mouse_release(QMouseEvent* e)
{
}
void GameEditor::on_idle()
{
	Update();
}
void GameEditor::UpdateHierarchyView()
{
	m_pMainWnd->GetFormHierarchy()->UpdateHierarchy(m_pEngine->RootObject());
}
void GameEditor::ClearHierarchyView()
{
	m_pMainWnd->GetFormHierarchy()->Clear();
}

bool GameEditor::NewScene()
{
	if(m_pProject)
	{
		ClearHierarchyView();
		bool ret = m_pProject->NewScene();
		UpdateHierarchyView();

		return ret;
	}
	return false;
}
bool GameEditor::OpenScene(boost::filesystem::path path)
{
	if(m_pProject == nullptr)
	{
		return false;
	}
	ClearHierarchyView();
	bool ret =  m_pProject->OpenScene(path);
	UpdateHierarchyView();
	return ret;
}
bool GameEditor::SaveScene()
{
	if(m_pProject == nullptr)
	{
		return false;
	}

	return m_pProject->SaveScene();
}
bool GameEditor::SaveScene(boost::filesystem::path path)
{
	if(m_pProject == nullptr)
	{
		return false;
	}
	return m_pProject->SaveScene(path);
}
boost::filesystem::path	GameEditor::GetSceneFile()
{
	return m_pProject->GetSceneFilePath();
}
void GameEditor::SetCurrentObject(ld3d::GameObject* pObj)
{
	m_pCurrentObject = pObj;

	UpdateInspectorView();
}
ld3d::GameObject* GameEditor::GetCurrentObject()
{
	return m_pCurrentObject;
}
GameEnginePtr GameEditor::GetGameEngine()
{
	return m_pEngine;
}
void GameEditor::UpdateInspectorView()
{
	m_pMainWnd->GetFormInspector()->SetObject(m_pCurrentObject);
}
void GameEditor::ClearInspectorView()
{
	m_pMainWnd->GetFormInspector()->SetObject(nullptr);
}
