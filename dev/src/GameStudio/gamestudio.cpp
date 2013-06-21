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
void GameStudio::on_menuFile_aboutToShow()
{
	actionSave_Project->setEnabled(m_pProject != nullptr);
	actionSave_Scene->setEnabled(m_pProject != nullptr);
	actionSave_Scene_As->setEnabled(m_pProject != nullptr);
	actionClose_Project->setEnabled(m_pProject != nullptr);
	actionNew_Scene->setEnabled(m_pProject != nullptr);
	actionOpen_Scene->setEnabled(m_pProject != nullptr);
}
void GameStudio::on_actionNew_Project_triggered()
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
	if(pSub )
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

void GameStudio::on_actionOpen_Project_triggered()
{
	QFileDialog dlg(this);
	dlg.setFileMode(QFileDialog::ExistingFile);
	dlg.setNameFilter(tr("Project File (*.gp)"));
	dlg.setAcceptMode(QFileDialog::AcceptOpen);

	if(dlg.exec() == QFileDialog::Rejected)
	{
		return;
	}

	QString file = dlg.selectedFiles().at(0);
	boost::filesystem::path filePath(file.toStdWString());

	if(m_pProject != nullptr)
	{
		m_pProject->Save();
		m_pProject->Close();
	}

	m_pProject = alloc_shared<Project>();
	
	if(m_pProject->Open(filePath) == false)
	{
		QMessageBox::critical(this, "Failed", "Failed to open project: " + file);
		m_pProject->Close();
		m_pProject.reset();
		return;
	}

	AppContext::project = m_pProject;

	logInfo("Project loaded.");
}
