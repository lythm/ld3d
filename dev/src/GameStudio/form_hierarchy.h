#ifndef FORM_HIERARCHY_H
#define FORM_HIERARCHY_H

#include <QWidget>
#include "ui_form_hierarchy.h"

class Form_Hierarchy : public QWidget, public Ui::Form_Hierarchy
{
	Q_OBJECT

public:
	Form_Hierarchy(QWidget *parent = 0);
	~Form_Hierarchy();
};


#endif // FORM_HIERARCHY_H
