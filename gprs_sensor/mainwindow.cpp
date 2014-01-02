#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDockWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QGroupBox>
#include <QPushButton>
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
#include "tcpserverdialog.h"
#include "recedockwidget.h"
#include "senddockwidget.h"
#include <QDateTime>
#include <QFile>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("gprs_sensor");


    portType = Tcp;

    this->serial = new QSerialPort(this);
    settings = new SettingsDialog(this);

    this->tcpServer = new TcpServerDialog(this);


    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);

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


    receDockWidget = new ReceDockWidget(this);
    receDockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetVerticalTitleBar);
    receDockWidget->setMinimumWidth(200);
    receDockWidget->setSizePolicy( QSizePolicy::Fixed,QSizePolicy::Expanding);
    this->addDockWidget(Qt::RightDockWidgetArea, receDockWidget);

    this->sendDockWidget = new SendDockWidget(this);
    sendDockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetVerticalTitleBar);
    sendDockWidget->setMinimumSize(100,100);
    sendDockWidget->setSizePolicy( QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->addDockWidget(Qt::RightDockWidgetArea, sendDockWidget);

    nodeView = new TreeView();
    nodeView->setAllEnable(false, false, true, true);
    struct3DScene = new GLWindow(this);
    QSplitter *splitter= new QSplitter(Qt::Vertical, 0);

    splitter->addWidget(nodeView);
    splitter->addWidget(struct3DScene);
    this->setCentralWidget(splitter);
    struct3DScene->showExample();
    nodeView->showExample2();

    initAllConnections();
}

MainWindow::~MainWindow()
{
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
        receDockWidget->show();
        ui->actionRece_Window->setIcon(QIcon(":/image/ACDSEE2.ICO"));
    }
    else
    {
        receDockWidget->hide();
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

bool MainWindow::openTcpPort()
{
    if(tcpServer->serverListen(true))
        return true;
    else
        return false;
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

bool MainWindow::closeTcpPort()
{
    if(tcpServer->serverListen(false))
        return true;
    else
        return false;
}

void MainWindow::closeSerialPort()
{
    serial->close();
    ui->statusBar->showMessage(tr("Disconnected"));
}

void MainWindow::writeSerialData(const QString data)
{
    QByteArray block;

    block.append(data);
    serial->write(block);
}

void MainWindow::writeTcpData(const QString data)
{
    tcpServer->writeClient(data);
}

void MainWindow::readSerialData()
{
    QByteArray data = serial->readAll();
    receDockWidget->appendText(data);
}

void MainWindow::readTcpData(QString str)
{
    receDockWidget->appendText(str);
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::initAllConnections()
{
    QObject::connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openPort()));
    QObject::connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closePort()));
    QObject::connect(ui->actionSerial_Port, SIGNAL(triggered()), this, SLOT(setSerialPort()));
    QObject::connect(ui->actionTCP_Port, SIGNAL(triggered()), this, SLOT(setTcpPort()));
    QObject::connect(ui->actionSerial_Port_2, SIGNAL(triggered()), this, SLOT(selectSerialPort()));
    QObject::connect(ui->actionTCP_Port_2, SIGNAL(triggered()), this, SLOT(selectTcpPort()));
    QObject::connect(ui->actionStruct_Window, SIGNAL(triggered()), this, SLOT(treeDockShowPolicy()));
    QObject::connect(ui->actionRece_Window, SIGNAL(triggered()), this, SLOT(receDockShowPolicy()));
    QObject::connect(ui->actionSend_Window, SIGNAL(triggered()), this, SLOT(sendDockShowPolicy()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    QObject::connect(ui->actionHow_to_use, SIGNAL(triggered()), this, SLOT(howToUse()));
    QObject::connect(serial, SIGNAL(readyRead()), this, SLOT(readSerialData()));
    QObject::connect(tcpServer, SIGNAL(readReady(QString)), this, SLOT(readTcpData(QString)));
    QObject::connect(sendDockWidget, SIGNAL(sendButtonClick()), this, SLOT(sendData()));
}
void MainWindow::setSerialPort()
{
    settings->show();
}

void MainWindow::setTcpPort()
{

    this->tcpServer->show();
}

void MainWindow::selectSerialPort(void)
{
    ui->actionSerial_Port_2->setIcon(QIcon(":/image/DOWNLOADS567.ICO"));
    ui->actionTCP_Port_2->setIcon(QIcon(":/image/SEA MONSTER.ICO"));

    portType = Serial;
}

void MainWindow::selectTcpPort(void)
{
    ui->actionSerial_Port_2->setIcon(QIcon(":/image/SEA MONSTER.ICO"));
    ui->actionTCP_Port_2->setIcon(QIcon(":/image/DOWNLOADS567.ICO"));
    portType = Tcp;

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
            ui->actionConnect->setIcon(QIcon(":/image/DOWNLOADS567.ICO"));
            ui->actionDisconnect->setIcon(QIcon(":/image/SEA MONSTER.ICO"));
        }
        break;
    case Tcp:
        if(openTcpPort())
        {
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            ui->actionSerial_Port_2->setEnabled(false);
            ui->actionTCP_Port->setEnabled(false);
            ui->actionTCP_Port_2->setEnabled(false);
            ui->actionConnect->setIcon(QIcon(":/image/DOWNLOADS567.ICO"));
            ui->actionDisconnect->setIcon(QIcon(":/image/SEA MONSTER.ICO"));
        }
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
        ui->actionSerial_Port->setEnabled(true);
        ui->actionConnect->setIcon(QIcon(":/image/SEA MONSTER.ICO"));
        ui->actionDisconnect->setIcon(QIcon(":/image/DOWNLOADS567.ICO"));
        break;
    case Tcp:
        if(closeTcpPort())
        {
            ui->actionConnect->setEnabled(true);
            ui->actionDisconnect->setEnabled(false);
            ui->actionSerial_Port_2->setEnabled(true);
            ui->actionTCP_Port_2->setEnabled(true);
            ui->actionTCP_Port->setEnabled(true);
            ui->actionConnect->setIcon(QIcon(":/image/SEA MONSTER.ICO"));
            ui->actionDisconnect->setIcon(QIcon(":/image/DOWNLOADS567.ICO"));
        }
        break;
    }
}

void MainWindow::sendData()
{

    switch(portType)
    {
    case Serial:
        if(!ui->actionConnect->isEnabled())
            writeSerialData(this->sendDockWidget->toPlainText());
        break;
    case Tcp:
        if(!ui->actionConnect->isEnabled())
         writeTcpData(this->sendDockWidget->toPlainText());
        break;
    }
}

void MainWindow::howToUse()
{
    QMessageBox::information(this, "tip", "this software is accomplish with the gprs_sensor hardware");
}
