#include "stdafx.h"
#include "HierarchyModel.h"


HierarchyModel::HierarchyModel(void)
{
}


HierarchyModel::~HierarchyModel(void)
{
}
void HierarchyModel::updateHierarchy(ld3d::GameObjectPtr pRoot)
{
	beginResetModel();
	m_pRoot = pRoot;
	endResetModel();
}
int HierarchyModel::columnCount(const QModelIndex & /* parent */) const
{
	return 1;
}
QVariant HierarchyModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole && role != Qt::EditRole)
		return QVariant();

	ld3d::GameObject* pObj = getItem(index);

	if(pObj == nullptr)
	{
		return QVariant();
	}
	QString name = QString::fromStdWString(pObj->GetName());

	return name;
}
Qt::ItemFlags HierarchyModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsDropEnabled | QAbstractItemModel::flags(index);

	return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}
ld3d::GameObject* HierarchyModel::getItem(const QModelIndex &index) const
{
	if (index.isValid())
	{
		ld3d::GameObject *item = static_cast<ld3d::GameObject*>(index.internalPointer());
		if (item)
			return item;
	}
	return m_pRoot.get();
}
QVariant HierarchyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	return QVariant();
}
QModelIndex HierarchyModel::index(int row, int column, const QModelIndex &parent) const
{
	if (parent.isValid() && parent.column() != 0)
		return QModelIndex();

	using namespace ld3d;

	GameObject* parentItem = getItem(parent);
	if(parentItem == nullptr)
	{
		return QModelIndex();
	}
	GameObjectPtr pChild = parentItem->GetFirstChild();

	for(int i = 0; i < row && pChild; ++i)
	{
		pChild = pChild->GetNextNode();
	}

	if (pChild)
	{
		return createIndex(row, column, pChild.get());
	}

	return QModelIndex();
}
bool HierarchyModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
	return QAbstractItemModel::insertColumns(position, columns, parent);
}
Qt::DropActions HierarchyModel::supportedDragActions() const
{
	return Qt::MoveAction;
}
bool HierarchyModel::insertRows(int position, int rows, const QModelIndex &parent)
{
	return QAbstractItemModel::insertRows(position, rows, parent);
}
QModelIndex HierarchyModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	using namespace ld3d;

	GameObject* childItem = getItem(index);
	GameObjectPtr parentItem = childItem->GetParent();

	if (parentItem == m_pRoot || parentItem == nullptr)
		return QModelIndex();

	int n = 0;

	GameObjectPtr pNode = parentItem->GetParent();
	while(pNode && pNode != parentItem)
	{
		pNode = pNode->GetNextNode();
		++n;
	}

	return createIndex(n, 0, parentItem.get());
}
bool HierarchyModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
	return QAbstractItemModel::removeColumns(position, columns, parent);;
}
bool HierarchyModel::removeRows(int position, int rows, const QModelIndex &parent)
{
	return QAbstractItemModel::removeRows(position, rows, parent);
}
int HierarchyModel::rowCount(const QModelIndex &parent) const
{
	ld3d::GameObject* parentItem = getItem(parent);
	if(parentItem == nullptr)
	{
		return 0;
	}
	int n = 0;
	ld3d::GameObjectPtr pNode = parentItem->GetFirstChild();
	while(pNode)
	{
		pNode = pNode->GetNextNode();
		++n;
	}
	return n;
}
bool HierarchyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    ld3d::GameObject*  item = getItem(index);

    item->SetName(value.toString().toStdWString());

    emit dataChanged(index, index);

    return true;
}
bool HierarchyModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
   
	return false;
}
bool HierarchyModel::hasChildren(const QModelIndex & parent) const
{
	 ld3d::GameObject*  item = getItem(parent);
	 if(item == nullptr)
	 {
		 return false;
	 }

	 return item->GetFirstChild();
}
