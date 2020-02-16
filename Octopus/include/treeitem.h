#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QStringList>

class TreeItem{
public:
    explicit TreeItem(const QStringList &data, TreeItem *parentItem = 0);
    ~TreeItem();
    void appendChild(TreeItem *child);
    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QString data(int column) const;
    void changeData(int column,const QString&);
    int row() const;
    TreeItem *parentItem();

private:
    QList<TreeItem*> m_childItems;
    QStringList m_itemData;
    TreeItem *m_parentItem;
};

#endif // TREEITEM_H
