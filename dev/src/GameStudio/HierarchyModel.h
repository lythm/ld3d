#pragma once


class HierarchyModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	HierarchyModel(void);
	virtual ~HierarchyModel(void);

	int														columnCount(const QModelIndex &) const;
	QVariant												data(const QModelIndex &index, int role) const;
	Qt::ItemFlags											flags(const QModelIndex &index) const;
	ld3d::GameObject*										getItem(const QModelIndex &index) const;
	QVariant												headerData(int section, Qt::Orientation orientation, int role) const;
	void													updateHierarchy(ld3d::GameObjectPtr pRoot);
	QModelIndex												index(int row, int column, const QModelIndex &parent) const;

	bool													insertColumns(int position, int columns, const QModelIndex &parent);
	bool													insertRows(int position, int rows, const QModelIndex &parent);
	QModelIndex												parent(const QModelIndex &index) const;
	bool													removeColumns(int position, int columns, const QModelIndex &parent);
	bool													removeRows(int position, int rows, const QModelIndex &parent);
	int														rowCount(const QModelIndex &parent) const;
	bool													setData(const QModelIndex &index, const QVariant &value, int role);
	bool													setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role);
	bool													hasChildren(const QModelIndex & parent = QModelIndex()) const;

	Qt::DropActions											supportedDragActions() const;
private:
	ld3d::GameObjectPtr										m_pRoot;
};

