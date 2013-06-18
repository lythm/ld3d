#ifndef FORM_INSPECTOR_H
#define FORM_INSPECTOR_H

#include <QWidget>
#include "ui_form_inspector.h"

class Widget_Inspector;

class Form_Inspector : public QWidget, public Ui::Form_Inspector
{
	Q_OBJECT

public:
	Form_Inspector(QWidget *parent = 0);
	~Form_Inspector();



private:
	Widget_Inspector*						m_pInspector;
};

#endif // FORM_INSPECTOR_H
