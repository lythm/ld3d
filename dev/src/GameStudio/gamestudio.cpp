#include "stdafx.h"
#include "gamestudio.h"
#include "form_scene.h"
#include "form_preview.h"

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

	QSettings settings("GGUHA Ltd.", "Game Studio");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

GameStudio::~GameStudio()
{

}
void GameStudio::closeEvent(QCloseEvent *pEvent)
{
	QSettings settings("GGUHA Ltd.", "Game Studio");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("windowState", saveState());

	QMainWindow::closeEvent(pEvent);
}
