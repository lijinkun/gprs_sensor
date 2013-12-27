#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDockWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTextEdit>
#include <QGroupBox>
#include <QPushButton>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include <QSplitter>
#include "glwindow.h"
#include "treeview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("gprs_sensor");

    treeView = new TreeView();
    treeView->setAllEnable(true, false, false, true);
    treeView->showExample();

    QDockWidget * treeDockWidget = new QDockWidget(this);
    treeDockWidget->setWidget(treeView);
    treeDockWidget->setMinimumWidth(200);
    treeDockWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->addDockWidget(Qt::LeftDockWidgetArea, treeDockWidget);

    receTextEdit = new QTextEdit();
    receTextEdit->setMinimumSize(100,100);
    receTextEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    clearButton = new QPushButton("clear");
    clearButton->setMaximumSize(100,30);
    clearButton->setMinimumSize(100,30);
    clearButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed );
    clearButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    saveButton = new QPushButton("save");
    saveButton->setMaximumSize(100,30);
    saveButton->setMinimumSize(100,30);
    saveButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed );
    saveButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QHBoxLayout * receLayout1 = new QHBoxLayout;
    QHBoxLayout * receLayout2 = new QHBoxLayout;
    QVBoxLayout * receLayout3 = new QVBoxLayout;
    receLayout1->addWidget(receTextEdit);
    receLayout2->addWidget(saveButton);
    receLayout2->addWidget(clearButton);
    receLayout3->addLayout(receLayout1);
    receLayout3->addLayout(receLayout2);
    QGroupBox * receBox = new QGroupBox("receive");
    receBox->setLayout(receLayout3);

    QDockWidget * receDockWidget = new QDockWidget(this);
    receDockWidget->setWidget(receBox);
    receDockWidget->setMinimumWidth(200);
    receDockWidget->setSizePolicy( QSizePolicy::Fixed,QSizePolicy::Expanding);
    this->addDockWidget(Qt::RightDockWidgetArea, receDockWidget);

    sendTextEdit = new QTextEdit();
    receTextEdit = new QTextEdit();
    sendTextEdit->setMinimumSize(100,100);
    sendTextEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    sendButton = new QPushButton("send");
    sendButton->setMaximumSize(100,50);
    sendButton->setMinimumSize(100,50);
    sendButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed );
    sendButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QRadioButton * brocastUpdateButton = new QRadioButton("all update");
    QRadioButton * brocastDebugButton = new QRadioButton("all debug");
    QRadioButton * selectUpdateButton = new QRadioButton("select update");
    QRadioButton * selectDebugButton = new QRadioButton("select debug");
    QRadioButton * otherButton = new QRadioButton("write in");
    radioButtonList.append(brocastUpdateButton);
    radioButtonList.append(brocastDebugButton);
    radioButtonList.append(selectUpdateButton);
    radioButtonList.append(selectDebugButton);
    radioButtonList.append(otherButton);

    QHBoxLayout * sendLayout1 = new QHBoxLayout;
    QHBoxLayout * sendLayout2 = new QHBoxLayout;
    QVBoxLayout * sendLayout3 = new QVBoxLayout;
    QHBoxLayout * sendLayout4 = new QHBoxLayout;
    QHBoxLayout * sendLayout5 = new QHBoxLayout;
    QHBoxLayout * sendLayout6 = new QHBoxLayout;
    QVBoxLayout * sendLayout7 = new QVBoxLayout;
    QHBoxLayout * sendLayout8 = new QHBoxLayout;
    sendLayout1->addWidget(brocastUpdateButton);
    sendLayout1->addWidget(brocastDebugButton);
    sendLayout2->addWidget(selectUpdateButton);
    sendLayout2->addWidget(selectDebugButton);
    sendLayout8->addWidget(otherButton);
    sendLayout3->addLayout(sendLayout1);
    sendLayout3->addLayout(sendLayout2);
    sendLayout3->addLayout(sendLayout8);
    sendLayout4->addWidget(sendButton);
    sendLayout5->addLayout(sendLayout3);
    sendLayout5->addLayout(sendLayout4);
    sendLayout6->addWidget(sendTextEdit);
    sendLayout7->addLayout(sendLayout6);
    sendLayout7->addLayout(sendLayout5);

    QGroupBox * sendBox = new QGroupBox("send");
    sendBox->setLayout(sendLayout7);

    QDockWidget * sendDockWidget = new QDockWidget(this);
    sendDockWidget->setWidget(sendBox);

    sendDockWidget->setMinimumSize(100,100);
    sendDockWidget->setSizePolicy( QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->addDockWidget(Qt::RightDockWidgetArea, sendDockWidget);


    nodeView = new TreeView();
    nodeView->setAllEnable(false, false, true, true);
    struct3DScene = new GLWindow();
    QSplitter *splitter= new QSplitter(Qt::Vertical, 0);


    splitter->addWidget(nodeView);
    splitter->addWidget(struct3DScene);
    this->setCentralWidget(splitter);
    struct3DScene->showExample();
    nodeView->showExample2();
}

MainWindow::~MainWindow()
{
    delete ui;
}




