#include "stdafx.h"
#include "form_scene.h"
#include "GameEditor.h"

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
	
	QMdiSubWindow::timerEvent(event);
}
void Form_Scene::resizeEvent(QResizeEvent* e)
{
	_call(on_resize, e);
	QMdiSubWindow::resizeEvent(e);
}
void Form_Scene::mouseMoveEvent(QMouseEvent* e)
{
	_call(on_mouse_move, e);
	QMdiSubWindow::mouseMoveEvent(e);
}
void Form_Scene::wheelEvent(QWheelEvent* e)
{
	_call(on_mouse_wheel, e);
	QMdiSubWindow::wheelEvent(e);
}
void Form_Scene::mousePressEvent(QMouseEvent* e)
{
	_call(on_mouse_press, e);
	QMdiSubWindow::mousePressEvent(e);
}
void Form_Scene::mouseReleaseEvent(QMouseEvent* e)
{
	_call(on_mouse_release, e);
	QMdiSubWindow::mouseReleaseEvent(e);
}

void Form_Scene::InstallDelegates(GameEditorPtr pEditor)
{
	on_mouse_move			= std::bind(&GameEditor::on_mouse_move, pEditor.get(), std::placeholders::_1);
	on_resize				= std::bind(&GameEditor::on_resize, pEditor.get(), std::placeholders::_1);;
	on_mouse_wheel			= std::bind(&GameEditor::on_mouse_wheel, pEditor.get(), std::placeholders::_1);;
	on_mouse_press			= std::bind(&GameEditor::on_mouse_press, pEditor.get(), std::placeholders::_1);;
	on_mouse_release		= std::bind(&GameEditor::on_mouse_release, pEditor.get(), std::placeholders::_1);;

}
void Form_Scene::UnInstallDelegates()
{
	on_resize				= nullptr;
	on_mouse_move			= nullptr;
	on_mouse_wheel			= nullptr;
	on_mouse_press			= nullptr;
	on_mouse_release		= nullptr;
}