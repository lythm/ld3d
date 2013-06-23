#include "stdafx.h"
#include "form_hierarchy.h"

Form_Hierarchy::Form_Hierarchy(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	
	//treeView->setDropEnabled(true);
	treeView->setModel(&m_dataModel);
}

Form_Hierarchy::~Form_Hierarchy()
{

}
void Form_Hierarchy::UpdateHierarchy(ld3d::GameObjectPtr pRoot)
{
	m_dataModel.updateHierarchy(pRoot);

	
}
void Form_Hierarchy::Clear()
{
	m_dataModel.updateHierarchy(nullptr);
}
