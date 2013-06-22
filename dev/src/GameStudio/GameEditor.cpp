#include "stdafx.h"
#include "GameEditor.h"
#include "GameEngine.h"
#include "Project.h"
#include "gamestudio.h"
#include "form_scene.h"
#include "OrbitCamera.h"

GameEditor::GameEditor(GameStudio* pMainWnd)
{
	m_pMainWnd = pMainWnd;

}


GameEditor::~GameEditor(void)
{

}
bool GameEditor::Initialize()
{
	m_pCamera = alloc_shared<OrbitCamera>();
	return true;
}
void GameEditor::Release()
{
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
}
void GameEditor::Reset()
{
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

	return true;
}
bool GameEditor::NewProject(boost::filesystem::path path)
{
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