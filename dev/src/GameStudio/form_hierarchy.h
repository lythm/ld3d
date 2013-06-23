#ifndef FORM_HIERARCHY_H
#define FORM_HIERARCHY_H

#include <QWidget>
#include "ui_form_hierarchy.h"

#include "HierarchyModel.h"


class Form_Hierarchy : public QWidget, public Ui::Form_Hierarchy
{
	Q_OBJECT

public:



	Form_Hierarchy(QWidget *parent = 0);
	~Form_Hierarchy();

	void										UpdateHierarchy(ld3d::GameObjectPtr pRoot);

	void										Clear();
private:
	HierarchyModel								m_dataModel;

};


#endif // FORM_HIERARCHY_H
