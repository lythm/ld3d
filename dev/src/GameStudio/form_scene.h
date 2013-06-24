#ifndef FORM_SCENE_H
#define FORM_SCENE_H

#include <QMdiSubWindow>
#include "ui_form_scene.h"

class Form_Scene : public QMdiSubWindow, public Ui::Form_Scene
{
	Q_OBJECT

public:
	Form_Scene(QWidget *parent = 0);
	~Form_Scene();

	void													resizeEvent(QResizeEvent* e);
	void													mouseMoveEvent(QMouseEvent* e);
	void													wheelEvent(QWheelEvent* e);
	void													mousePressEvent(QMouseEvent* e);
	void													mouseReleaseEvent(QMouseEvent* e);


	void													InstallDelegates(GameEditorPtr pEditor);
	void													UnInstallDelegates();

	std::function<void(QResizeEvent*)>						on_resize;
	std::function<void(QMouseEvent*)>						on_mouse_move;
	std::function<void(QWheelEvent*)>						on_mouse_wheel;
	std::function<void(QMouseEvent*)>						on_mouse_press;
	std::function<void(QMouseEvent*)>						on_mouse_release;


private:
	template<typename F, typename E>
	void													_call(F f, E e)
	{
		f ? f(e) : 0;
	}


};

#endif // FORM_SCENE_H
