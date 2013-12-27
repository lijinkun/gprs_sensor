#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>
class QStandardItem;
class QAction;
class QStandardItemModel;
class QList <QStandardItem>;

class TreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit TreeView(QWidget *parent = 0);
    ~TreeView();

public:
    void showExample(void);
    void showExample2(void);
    void setAllEnable(bool rightClick, bool douckClickEdit,
                                bool multiSelect ,bool enable);
    void setColumn(int column, int width, QString RootID, QString NodeIDHead = NULL);

   /* void deleteNode(void);
    void deleteRoot(void);
    void addRoot(void);
    void addNode(void);
    void insertNode(void);
    void insertRoot(void);
    void debugNode(void);*///havent achieve
signals:

public slots:
    void ShowMouseRightButton(const QPoint &);
    void deleteNode(void);
    void deleteRoot(void);
    void addRoot(void);
    void addNode(void);
    void insertNode(void);
    void insertRoot(void);
    void debugNode(void);
private:

private:
    QAction * deleteNodeAction;
    QAction * insertNodeAction;
    QAction * addNodeAction;
    QAction * deleteRootAction;
    QAction * insertRootAction;
    QAction * addRootAction;
    QAction * debugPaneAction;
    QStandardItemModel *mode;
    QList<QStandardItem *>  topLeve;

};

#endif // TREEVIEW_H
