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

	QObject::connect(menuFile, SIGNAL(aboutToShow()), this, SLOT(on_menufile_abouttoshow()));

	QObject::connect(actionNew_Project, SIGNAL(triggered()), this, SLOT(on_menufile_new_project()));

	
	 
}

GameStudio::~GameStudio()
{
	AppContext::project.reset();
	m_pProject.reset();
	
}
void GameStudio::closeEvent(QCloseEvent *pEvent)
{
	if(m_pProject)
	{
		m_pProject->Close();
		m_pProject.reset();
	}
	AppContext::project = nullptr;

	QSettings settings("GGUHA Ltd.", "Game Studio");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("windowState", saveState());

	QMainWindow::closeEvent(pEvent);
}
bool GameStudio::event(QEvent *event)
{
	
	int returnValue = QMainWindow::event(event);

	/*if (event->type() == QEvent::Polish && event->spontaneous() == false)
	{
		Form_ProjectWizard dlg(this);

		dlg.setModal(true);
		dlg.exec();
		return true;
	}*/

	return returnValue;

}
void GameStudio::logInfo(const QString& str)
{
	m_pLogForm->logInfo(str);
}
void GameStudio::logBuild(const QString& str)
{
	m_pLogForm->logBuild(str);
}
void GameStudio::on_menufile_abouttoshow()
{
	actionSave_Project->setEnabled(m_pProject != nullptr);
	actionSave_Scene->setEnabled(m_pProject != nullptr);
	actionSave_Scene_As->setEnabled(m_pProject != nullptr);
	actionClose_Project->setEnabled(m_pProject != nullptr);
	actionNew_Scene->setEnabled(m_pProject != nullptr);
	actionOpen_Scene->setEnabled(m_pProject != nullptr);
}
void GameStudio::on_menufile_new_project()
{
	if(m_pProject != nullptr)
	{
		m_pProject->Save();
		m_pProject->Close();
	}

	Form_ProjectWizard dlg(this);

	if(QDialog::Rejected == dlg.exec())
	{
		return;
	}



	m_pProject = alloc_shared<Project>();
	
	if(m_pProject->New(dlg.ProjectFilePath()) == false)
	{
		QMessageBox::critical(this, "Failed", "Failed to create new project: " + QString::fromStdWString(dlg.ProjectFilePath().wstring()));
		m_pProject->Close();
		m_pProject.reset();
		return;
	}

	AppContext::project = m_pProject;

	logInfo("Project created.");
}

void GameStudio::on_mdiArea_subWindowActivated(QMdiSubWindow* pSub)
{
	if(pSub)
	{
		logInfo(pSub->windowTitle());
	}
}
void GameStudio::on_actionSave_Project_triggered()
{
	if(m_pProject)
	{
		m_pProject->Save();
	}
}