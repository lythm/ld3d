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


private:

};

#endif // FORM_SCENE_H
