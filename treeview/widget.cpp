#include "widget.h"
#include "ui_widget.h"
#include <QTreeView>
#include <QMenu>
#include <QIcon>
#include <QStandardItem>
#include <QStandardItemModel>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QStandardItemModel *mode = new QStandardItemModel(0,4,this);
    mode->setHeaderData(0, Qt::Horizontal, tr("Network Struct"));
    mode->setHeaderData(1, Qt::Horizontal, tr("state1"));
    mode->setHeaderData(2, Qt::Horizontal, tr("state2"));
    mode->setHeaderData(3, Qt::Horizontal, tr("state3"));

    ui->treeView->setColumnWidth(0,200);
    ui->treeView->setColumnWidth(1,100);
    ui->treeView->setColumnWidth(2,100);
    ui->treeView->setColumnWidth(3,100);
    ui->treeView->setModel(mode);

    for(int i = 0; i < 10; ++i)
    {
        QList<QStandardItem *> leve0;
        QStandardItem * item = new QStandardItem(QString("GRPS_%0").arg(i));
        item->setCheckable(1);//使能复选框
        item->setIcon(QIcon(":/new/prefix1/images/Aqua Ball.ico"));
        leve0.append(item);

        mode->appendRow(leve0);

        for(int j = 0; j < 4; ++j)
        {
            QList<QStandardItem *> leve1;
            QStandardItem * item = new QStandardItem(QString("Sensor_%0").arg(j));
            item->setCheckable(1);//使能复选框
            item->setIcon(QIcon(":/new/prefix1/green"));
            leve1.append(item);
            for(int i = 1; i < 4; ++i)
            {
                QStandardItem * item = new QStandardItem(QString("state_%0").arg(i));
                leve1.append(item);
            }
            leve0.at(0)->appendRow(leve1);
        }

    }

   // ui->treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);//设置多选
   ui->treeView->setEditTriggers(0);//取消双击修改
   ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);//设置treeView右键单击产生相应信号，并设置连接
   QObject::connect(ui->treeView, SIGNAL(customContextMenuRequested(const QPoint)),
           this, SLOT(ShowMouseRightButton(const QPoint)));

}


Widget::~Widget()
{
    delete ui;
}

void Widget::ShowMouseRightButton(const QPoint& pos)
{
           QMenu * qMenu = new QMenu(ui->treeView);

           QAction* closePaneAction = new QAction("&Close",this);
           connect(closePaneAction, SIGNAL(triggered()), this, SLOT(close()));

           qMenu->addAction(closePaneAction);

           qMenu->exec(QCursor::pos()); //在鼠标点击的位置显示鼠标右键菜单
}

