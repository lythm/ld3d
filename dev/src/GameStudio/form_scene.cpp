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
