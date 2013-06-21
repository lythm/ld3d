#include "stdafx.h"
#include "form_scene.h"
#include "AppContext.h"
#include "Project.h"
#include "GameScene.h"

Form_Scene::Form_Scene(QWidget *parent)
	: QMdiSubWindow(parent)
{
	setupUi(this);

	m_timer = startTimer(100);

}

Form_Scene::~Form_Scene()
{
	killTimer(m_timer);
}
void Form_Scene::timerEvent(QTimerEvent* event)
{
	if(AppContext::project)
	{
		GameScenePtr pScene = AppContext::project->GetGameScene();
		if(pScene)
		{

			pScene->Update();
			pScene->Render();
		}
	}
	QMdiSubWindow::timerEvent(event);
}
void Form_Scene::resizeEvent(QResizeEvent* e)
{
	QMdiSubWindow::resizeEvent(e);
}
void Form_Scene::mouseMoveEvent(QMouseEvent* e)
{
	QMdiSubWindow::mouseMoveEvent(e);
}
void Form_Scene::wheelEvent(QWheelEvent* e)
{
	QMdiSubWindow::wheelEvent(e);
}