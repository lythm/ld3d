#include "stdafx.h"
#include "form_hierarchy.h"

Form_Hierarchy::Form_Hierarchy(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	
	//treeView->setDropEnabled(true);
	treeView->setModel(&m_dataModel);

	QItemSelectionModel* pModel = treeView->selectionModel();

	connect(pModel, SIGNAL(currentChanged(const QModelIndex&, const QModelIndex& )), this, SLOT(currentChanged(const QModelIndex&, const QModelIndex&)));
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

void Form_Hierarchy::currentChanged(const QModelIndex& current, const QModelIndex& prev)
{
	if(on_current_changed)
	{
		on_current_changed(m_dataModel.getItem(current));
	}
}
