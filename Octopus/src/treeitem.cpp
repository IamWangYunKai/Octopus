#include <QStringList>
#include "treeitem.h"

TreeItem::TreeItem(const QStringList &data, TreeItem *parent){
    m_parentItem = parent;
    m_itemData = data;
}

TreeItem::~TreeItem(){
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item){
    m_childItems.append(item);
}

TreeItem *TreeItem::child(int row){
    return m_childItems.value(row);
}

int TreeItem::childCount() const{
    return m_childItems.count();
}

int TreeItem::columnCount() const{
    return m_itemData.count();
}

QString TreeItem::data(int column) const{
    return m_itemData.value(column);
}

void TreeItem::changeData(int column,const QString& value){
    m_itemData[column] = value;
}

TreeItem *TreeItem::parentItem(){
    return m_parentItem;
}

int TreeItem::row() const{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}
