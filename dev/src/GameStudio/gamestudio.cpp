#include "stdafx.h"
#include "gamestudio.h"
#include "form_scene.h"
#include "form_preview.h"
#include "form_hierarchy.h"
#include "form_projectwizard.h"
#include "form_log.h"
#include "form_inspector.h"
#include "widget_inspector.h"

#include "AppContext.h"

#include "Project.h"
#include "GameEditor.h"


GameStudio::GameStudio(QWidget *parent)
	: QMainWindow(parent)
{

	setupUi(this);

	

	m_pSceneForm = new Form_Scene(this);
	m_pSceneForm->setWindowTitle("Scene");
	m_pPreviewForm = new Form_Preview(this);
	m_pPreviewForm->setWindowTitle("Preview");

	mdiArea->addSubWindow(m_pSceneForm);
	m_pSceneForm->showMaximized();

	mdiArea->addSubWindow(m_pPreviewForm);
	m_pPreviewForm->showMaximized();

	m_pSceneForm->raise();
	
	m_pHierarchyForm = new Form_Hierarchy(this);
	dockHierarchy->setWidget(m_pHierarchyForm);
	
	m_pLogForm = new Form_Log(this);
	dockLog->setWidget(m_pLogForm);

	m_pInspectorForm = new Form_Inspector(this);
	dockInspector->setWidget(m_pInspectorForm);
	
	
	QSettings settings("GGUHA Ltd.", "Game Studio");
	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("windowState").toByteArray());

	AppContext::form_scene = m_pSceneForm;
	AppContext::form_preview = m_pPreviewForm;
	AppContext::form_log = m_pLogForm;


	m_pEditor = alloc_shared<GameEditor>((GameStudio*)this);

	if(m_pEditor->Initialize() == false)
	{
		return;
	}

	
	UpdateActions();
}

GameStudio::~GameStudio()
{
	
}
void GameStudio::closeEvent(QCloseEvent *pEvent)
{
	g_app_running = false;
	//killTimer(m_updateTimer);
	
	if(m_pEditor)
	{
		m_pEditor->Release();
		m_pEditor.reset();
	}

	AppContext::project = nullptr;

	QSettings settings("GGUHA Ltd.", "Game Studio");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("windowState", saveState());

	QMainWindow::closeEvent(pEvent);
}

void GameStudio::logInfo(const QString& str)
{
	m_pLogForm->logInfo(str);
}
void GameStudio::logBuild(const QString& str)
{
	m_pLogForm->logBuild(str);
}

void GameStudio::on_menuFile_aboutToShow()
{
	bool show = m_pEditor->GetProject() != nullptr;

	actionSave_Project->setEnabled(show);
	actionSave_Scene->setEnabled(show);
	actionSave_Scene_As->setEnabled(show);
	actionClose_Project->setEnabled(show);
	actionNew_Scene->setEnabled(show);
	actionOpen_Scene->setEnabled(show);
}
void GameStudio::on_actionNew_Project_triggered()
{
	Form_ProjectWizard dlg(this);

	if(QDialog::Rejected == dlg.exec())
	{
		return;
	}
		
	if(m_pEditor->NewProject(dlg.ProjectFilePath()) == false)
	{
		QMessageBox::critical(this, "Failed", "Failed to create new project: " + QString::fromStdWString(dlg.ProjectFilePath().wstring()));
		return;
	}
	
	logInfo("Project created.");
}

void GameStudio::on_mdiArea_subWindowActivated(QMdiSubWindow* pSub)
{
	if(pSub )
	{
		logInfo(pSub->windowTitle());
	}
}
void GameStudio::on_actionSave_Project_triggered()
{
	m_pEditor->SaveProject();

}

void GameStudio::on_actionOpen_Project_triggered()
{

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                QString(),
                                                tr("Project File (*.gp)"));

	if(fileName == "")
	{
		return;
	}

	boost::filesystem::path filePath(fileName.toStdWString());

	if(m_pEditor->OpenProject(filePath) == false)
	{
		QMessageBox::critical(this, "Failed", "Failed to open project: " + fileName);
		return;
	}
	logInfo("Project loaded.");
}

void GameStudio::showEvent(QShowEvent* e)
{
	QMainWindow::showEvent(e);
}

Form_Scene* GameStudio::GetFormScene()
{
	return m_pSceneForm;
}
void GameStudio::on_idle()
{
	m_pEditor ? m_pEditor->on_idle() : 0;
}
void GameStudio::on_actionClose_Project_triggered()
{
	m_pEditor->Reset();

	m_pSceneForm->repaint();
}
Form_Hierarchy* GameStudio::GetFormHierarchy()
{
	return m_pHierarchyForm;
}

void GameStudio::on_actionNew_Scene_triggered()
{
	if(QMessageBox::Yes == QMessageBox::question(this, "warning", "Do you want to save the scene before continue?"))
	{
		if(m_pEditor->GetProject()->HasSceneFileSpecified() == false)
		{
			if(false == SaveSceneAs())
			{
				return;
			}
		}
		else
		{
			if(false == SaveScene())
			{
				return;
			}
		}
	}

	m_pEditor->NewScene();
}
void GameStudio::on_actionSave_Scene_triggered()
{
	if(m_pEditor->GetProject()->HasSceneFileSpecified() == false)
	{
		SaveSceneAs();
		return;
	}

	SaveScene();
}
void GameStudio::on_actionSave_Scene_As_triggered()
{
	SaveSceneAs();
}
void GameStudio::on_actionOpen_Scene_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                QString(),
                                                tr("Scene File (*.scene)"));

	if(fileName == "")
	{
		return;
	}

	boost::filesystem::path filePath(fileName.toStdWString());

	if(m_pEditor->OpenScene(filePath) == false)
	{
		QMessageBox::critical(this, "Failed", "Failed to open scene: " + fileName);
		return;
	}
	logInfo("Scene openned.");
}
bool GameStudio::SaveSceneAs()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"),
                                                QString(),
                                                tr("Scene File (*.scene)"));

	if(fileName == "")
	{
		return false;
	}

	boost::filesystem::path filePath(fileName.toStdWString());

	if(m_pEditor->SaveScene(filePath) == false)
	{
		QMessageBox::critical(this, "Failed", "Failed to save scene: " + fileName);
		return false;
	}
	logInfo("Scene Saved.");

	return true;
}
bool GameStudio::SaveScene()
{
	if(m_pEditor->SaveScene() == false)
	{
		QMessageBox::critical(this, "Failed", "Failed to save scene: " + QString::fromStdWString(m_pEditor->GetSceneFile().wstring()));
		return false;
	}
	logInfo("Scene Saved.");

	return true;
}
void GameStudio::UpdateActions()
{
	bool show = m_pEditor->GetProject() != nullptr;

	actionSave_Project->setEnabled(show);
	actionSave_Scene->setEnabled(show);
	actionSave_Scene_As->setEnabled(show);
	actionClose_Project->setEnabled(show);
	actionNew_Scene->setEnabled(show);
	actionOpen_Scene->setEnabled(show);

}