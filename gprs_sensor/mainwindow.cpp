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
#include "settingsdialog.h"
#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QIcon>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("gprs_sensor");


    portType = Debug;


    this->serial = new QSerialPort(this);
    settings = new SettingsDialog;

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);

    initActionsConnections();


    treeView = new TreeView();
    treeView->setAllEnable(true, false, false, true);
    treeView->showExample();
    treeView->deleteNode(3, 4);
    treeView->deleteRoot(4);
    treeView->addRoot("try");
    treeView->addNode(5, "try2");
    treeView->insertNode(6, 3, "try3");
    treeView->insertRoot(7, "QString rootName");

    treeDockWidget = new QDockWidget(this);
    treeDockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetVerticalTitleBar);
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

    receDockWidget = new QDockWidget(this);
    receDockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetVerticalTitleBar);
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

    sendDockWidget = new QDockWidget(this);
    sendDockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetVerticalTitleBar);
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
    delete settings;
    delete ui;
}

void MainWindow::treeDockShowPolicy(void)
{
    if(this->treeDockWidget->isHidden())
    {
        this->treeDockWidget->show();
        ui->actionStruct_Window->setIcon(QIcon(":/image/ACDSEE2.ICO"));
    }
    else
    {
        this->treeDockWidget->hide();
        ui->actionStruct_Window->setIcon(QIcon(":/image/ACDSEE4.ICO"));
    }
}

void MainWindow::receDockShowPolicy(void)
{
    if(this->receDockWidget->isHidden())
    {
        this->receDockWidget->show();
        ui->actionRece_Window->setIcon(QIcon(":/image/ACDSEE2.ICO"));
    }
    else
    {
        this->receDockWidget->hide();
        ui->actionRece_Window->setIcon(QIcon(":/image/ACDSEE4.ICO"));
    }
}
void MainWindow::sendDockShowPolicy(void)
{
    if(this->sendDockWidget->isHidden())
    {
        this->sendDockWidget->show();
        ui->actionSend_Window->setIcon(QIcon(":/image/ACDSEE2.ICO"));
    }
    else
    {
        this->sendDockWidget->hide();
        ui->actionSend_Window->setIcon(QIcon(":/image/ACDSEE4.ICO"));
    }
}

bool MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    if (serial->open(QIODevice::ReadWrite)) {
        if (serial->setBaudRate(p.baudRate)
                && serial->setDataBits(p.dataBits)
                && serial->setParity(p.parity)
                && serial->setStopBits(p.stopBits)
                && serial->setFlowControl(p.flowControl)) {


            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));

            return true;
        } else {
            serial->close();
            QMessageBox::critical(this, tr("Error"), serial->errorString());

            ui->statusBar->showMessage(tr("Open error"));

            return false;
        }
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        ui->statusBar->showMessage(tr("Configure error"));

        return false;
    }
}


void MainWindow::closeSerialPort()
{
    serial->close();
    ui->statusBar->showMessage(tr("Disconnected"));
}

void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}

void MainWindow::readData()
{
    QByteArray data = serial->readAll();
    //console->putData(data);
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::initActionsConnections()
{
    QObject::connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openPort()));
    QObject::connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closePort()));
    QObject::connect(ui->actionSerial_Port, SIGNAL(triggered()), this, SLOT(setSerialPort()));
    QObject::connect(ui->actionSerial_Port_2, SIGNAL(triggered()), this, SLOT(selectSerialPort()));
    QObject::connect(ui->actionStruct_Window, SIGNAL(triggered()), this, SLOT(treeDockShowPolicy()));
    QObject::connect(ui->actionRece_Window, SIGNAL(triggered()), this, SLOT(receDockShowPolicy()));
    QObject::connect(ui->actionSend_Window, SIGNAL(triggered()), this, SLOT(sendDockShowPolicy()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    QObject::connect(ui->actionHow_to_use, SIGNAL(triggered()), this, SLOT(howToUse()));
}
void MainWindow::setSerialPort()
{
    settings->show();
}

void MainWindow::selectSerialPort(void)
{
   // ui->actionSerial_Port_2->setIcon(QIcon(:/image/DOWNLOADS567.ICO));
    ui->actionSerial_Port_2->setIcon(QIcon(":/image/DOWNLOADS567.ICO"));
    ui->actionTCP_Port_2->setIcon(QIcon(":/image/SEA MONSTER.ICO"));
    ui->actionDebug_Port_2->setIcon(QIcon(":/image/SEA MONSTER.ICO"));
    portType = Serial;
}


void MainWindow::openPort()
{
    switch(portType)
    {
    case Serial:
        if(openSerialPort())
        {
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            ui->actionSerial_Port_2->setEnabled(false);
            ui->actionSerial_Port->setEnabled(false);
            ui->actionTCP_Port_2->setEnabled(false);
            ui->actionDebug_Port_2->setEnabled(false);
            ui->actionConnect->setIcon(QIcon(":/image/DOWNLOADS567.ICO"));
            ui->actionDisconnect->setIcon(QIcon(":/image/SEA MONSTER.ICO"));
        }
        break;
    case Tcp:
        break;
    case Debug:
        break;

    }

}

void MainWindow::closePort()
{
    switch(portType)
    {
    case Serial:
        closeSerialPort();
        ui->actionConnect->setEnabled(true);
        ui->actionDisconnect->setEnabled(false);
        ui->actionSerial_Port_2->setEnabled(true);
        ui->actionTCP_Port_2->setEnabled(true);
        ui->actionDebug_Port_2->setEnabled(true);
        ui->actionSerial_Port->setEnabled(true);
        ui->actionConnect->setIcon(QIcon(":/image/SEA MONSTER.ICO"));
        ui->actionDisconnect->setIcon(QIcon(":/image/DOWNLOADS567.ICO"));
        break;
    case Tcp:
        break;
    case Debug:
        break;
    }

}

void MainWindow::howToUse()
{
    QMessageBox::information(this, "tip", "this software is accomplish with the gprs_sensor hardware");
}
