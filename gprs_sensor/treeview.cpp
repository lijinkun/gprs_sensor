#include "treeview.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QList>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QInputDialog>

TreeView::TreeView(QWidget *parent) :
    QTreeView(parent)
{

    deleteNodeAction= new QAction("&Delete",this);
    insertNodeAction= new QAction("&insert",this);
    addNodeAction= new QAction("&add node",this);
    debugPaneAction = new QAction("debug",this);
    deleteRootAction= new QAction("&Delete",this);
    insertRootAction= new QAction("&insert",this);
    addRootAction= new QAction("&add Root",this);



    QObject::connect(this->deleteRootAction, SIGNAL(triggered()), this,
                     SLOT(deleteRoot()));
    QObject::connect(this->insertRootAction, SIGNAL(triggered()), this,
                     SLOT(insertRoot()));

    QObject::connect(this->addRootAction, SIGNAL(triggered()), this,
                     SLOT(addRoot()));
    QObject::connect(this->deleteNodeAction, SIGNAL(triggered()), this,
                     SLOT(deleteNode()));
    QObject::connect(this->insertNodeAction, SIGNAL(triggered()), this,
                     SLOT(insertNode()));

    QObject::connect(this->addNodeAction, SIGNAL(triggered()), this,
                     SLOT(addNode()));

    QObject::connect(this->debugPaneAction, SIGNAL(triggered()), this,
                     SLOT(debugNode()));
}

TreeView::~TreeView()
{

}

void TreeView::showExample(void)
{
    this->setColumn(1, 100,QStringLiteral("GPRS_STRUCT"));
    for(int i = 0; i < 10; ++i)
    {
        QList<QStandardItem *>  leve0;
        QStandardItem * item = new QStandardItem(QString("GRPS_%0").arg(i));
        item->setCheckable(1);//使能复选框
        item->setIcon(QIcon(":/image/Aqua Ball.ico"));
        leve0.append(item);

        mode->appendRow(leve0);

        for(int j = 0; j < 5; ++j)
        {
            QList<QStandardItem *> leve1;
            QStandardItem * item = new QStandardItem(QString("Sensor_%0").arg(j));
            item->setCheckable(1);//使能复选框
            item->setIcon(QIcon(":/image/Aqua Ball Green.ico"));
            leve1.append(item);
         /*   for(int i = 1; i < 4; ++i)
            {
                QStandardItem * item = new QStandardItem(QString("state_%0").arg(i));
                leve1.append(item);
            }*/
            leve0.at(0)->appendRow(leve1);
        }

    }

   // ui->treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);//设置多选
    this->setEditTriggers(0);//取消双击修改
   this->setContextMenuPolicy(Qt::CustomContextMenu);//设置treeView右键单击产生相应信号，并设置连接
}

void TreeView::showExample2(void)
{
    this->setColumn(4, 100, QStringLiteral("Abnormal sensor"), QStringLiteral("state"));

    for(int i = 0; i < 10; ++i)
    {
        QList<QStandardItem *>  leve2;
        QStandardItem * item = new QStandardItem(QString("GRPS_%0").arg(i));
        item->setCheckable(1);//使能复选框
        item->setIcon(QIcon(":/image/Aqua Ball Red.ico"));
        item->setText(QString("%0").arg(i));
        leve2.append(item);
        for(int i = 1; i < 4; ++i)
       {
           QStandardItem * item = new QStandardItem(QString("state_%0").arg(i));
           leve2.append(item);
       }

        mode->appendRow(leve2);

    }

   // ui->treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);//设置多选
    this->setEditTriggers(0);//取消双击修改
   this->setContextMenuPolicy(Qt::CustomContextMenu);//设置treeView右键单击产生相应信号，并设置连接
}


void TreeView::ShowMouseRightButton(const QPoint& pos)
{
   Q_UNUSED(pos);

   QModelIndex index = currentIndex();
   QMenu * qMenu = new QMenu(this);

   if(index.parent().row() == -1)
   {
       qMenu->addAction(addRootAction);
       qMenu->addAction(addNodeAction);
       qMenu->addAction(insertRootAction);
       qMenu->addAction(deleteRootAction);
   }
   else
   {
       qMenu->addAction(addRootAction);
       qMenu->addAction(insertNodeAction);
       qMenu->addAction(deleteNodeAction);
   }

   qMenu->addAction(debugPaneAction);
   qMenu->exec(QCursor::pos());


}

void TreeView::setColumn(int column, int width,  QString  rootID,  QString  nodeIDHead)
{
    mode = new QStandardItemModel(0,column,this);
    mode->setHeaderData(0, Qt::Horizontal, QString("%1").arg(rootID));
    this->setColumnWidth(0,200);

    for(int i = 1; i < column; ++i)
    {

        mode->setHeaderData(i, Qt::Horizontal, QString("%1_%2").arg(nodeIDHead).arg(i));
        this->setColumnWidth(i,width);
    }
    this->setModel(mode);
}

void TreeView::deleteNode(int rootID, int nodeID)
{
    mode->item(rootID)->removeRow(nodeID);
}

void TreeView::deleteNode(void)
{
    QModelIndex index = currentIndex();

    mode->item(index.parent().row())->removeRow(index.row());

}

void TreeView::deleteRoot(int rootID)
{
    mode->removeRow(rootID);
}

void TreeView::deleteRoot(void)
{
    QModelIndex index = currentIndex();

    mode->removeRow(index.row());
}

void TreeView::insertNode(int rootID, int nodeID, QString nodeName)
{
        QStandardItem * item = new QStandardItem(nodeName);
        item->setCheckable(1);//使能复选框
        item->setIcon(QIcon(":/image/Aqua Ball Green.ico"));
        mode->item(rootID-1)->insertRow(nodeID, item);
}

void TreeView::insertNode(void)
{
    QModelIndex index = currentIndex();


    bool isOK;
    QString text = QInputDialog::getText(NULL, "Input Dialog",
                                                       "Please input the node name",
                                                       QLineEdit::Normal,
                                                       "sensor_",
                                                       &isOK);
    if(isOK)
    {
        QStandardItem * item = new QStandardItem(text);
        item->setCheckable(1);//使能复选框
        item->setIcon(QIcon(":/image/Aqua Ball Green.ico"));
        mode->item(index.parent().row())->insertRow(index.row(), item);
    }

}


void TreeView::insertRoot(int rootID, QString rootName)
{

        QStandardItem * item = new QStandardItem(rootName);
        item->setCheckable(1);//使能复选框
        item->setIcon(QIcon(":/image/Aqua Ball.ico"));
        mode->insertRow(rootID-1, item);
}


void TreeView::insertRoot(void)
{

    QModelIndex index = currentIndex();
    bool isOK;

    QString text = QInputDialog::getText(NULL, "Input Dialog",
                                                       "Please input the node name",
                                                       QLineEdit::Normal,
                                                       "GPRS_",
                                                        &isOK);
    if(isOK)
    {
        QStandardItem * item = new QStandardItem(text);
        item->setCheckable(1);//使能复选框
        item->setIcon(QIcon(":/image/Aqua Ball.ico"));
        mode->insertRow(index.row(), item);
    }

}


void TreeView::addNode(int rootID, QString nodeName)
{

            QStandardItem * item = new QStandardItem(nodeName);
            item->setCheckable(1);//使能复选框
            item->setIcon(QIcon(":/image/Aqua Ball Green.ico"));
            mode->item(rootID-1)->appendRow(item);

}

void TreeView::addNode(void)
{
    QModelIndex index = currentIndex();

    if(index.parent().row() == -1)
    {
        bool isOK;

        QString text = QInputDialog::getText(NULL, "Input Dialog",
                                                           "Please input the node name",
                                                           QLineEdit::Normal,
                                                           "sensor_",
                                                            &isOK);
        if(isOK)
        {
            QStandardItem * item = new QStandardItem(text);
            item->setCheckable(1);//使能复选框
            item->setIcon(QIcon(":/image/Aqua Ball Green.ico"));
            mode->item(index.row())->appendRow(item);


        }


    }
}

void TreeView::addRoot(QString rootName)
{
        QStandardItem * item = new QStandardItem(rootName);
        item->setCheckable(1);
        item->setIcon(QIcon(":/image/Aqua Ball.ico"));
        mode->appendRow(item);
}

void TreeView::addRoot(void)
{
    bool isOK;

    QString text = QInputDialog::getText(NULL, "Input Dialog",
                                                       "Please input the node name",
                                                       QLineEdit::Normal,
                                                       "GPRS_",
                                                        &isOK);
    if(isOK)
    {
        QStandardItem * item = new QStandardItem(text);
        item->setCheckable(1);
        item->setIcon(QIcon(":/image/Aqua Ball.ico"));
        mode->appendRow(item);
    }
}

void TreeView::debugNode(void)
{
    QModelIndex index = currentIndex();
    qDebug() << index << endl;

}

void TreeView::setAllEnable(bool rightClick, bool douckClickEdit, bool multiSelect ,bool enable)
{

    this->setEnabled(enable);
    if(multiSelect == true)
        this->setSelectionMode(QAbstractItemView::ExtendedSelection);//设置多选
    else
        this->setSelectionMode(QAbstractItemView::SingleSelection);//设置多选

    if(douckClickEdit == true)
        this->setEditTriggers(0);//取消双击修改
    if(rightClick == true)
    {
        this->setContextMenuPolicy(Qt::CustomContextMenu);//设置treeView右键单击产生相应信号，并设置连接
        QObject::connect(this, SIGNAL(customContextMenuRequested(const QPoint)),
                         this, SLOT(ShowMouseRightButton(const QPoint)));
    }
    else
        this->setContextMenuPolicy(Qt::DefaultContextMenu);
}


QStandardItemModel * TreeView::getMode(void)
{
    return mode;
}
