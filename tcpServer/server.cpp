#include "server.h"
#include "ui_server.h"
#include <QTcpSocket>
#include <QtNetwork>
#include <QDebug>

Server::Server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    ui->lineEditIP->setText(ipAddressesList.at(0).toString());
    ui->lineEditPort->setValidator(new QIntValidator(1, 65535, this));

    tcpServer = new QTcpServer(this);

    QObject::connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    QObject::connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(clearText()));
    QObject::connect(ui->pushButtonSend, SIGNAL(clicked()), this, SLOT(sendClient()));
    QObject::connect(ui->pushButtonQuit, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->pushButtonListen, SIGNAL(clicked()), this, SLOT(setListen()));
}

Server::~Server()
{
    delete ui;
}

void Server::acceptConnection()
{
    if(ui->pushButtonListen->text() == "No Listen")
    {
        qDebug() << "new connect";

        clientConnection = tcpServer->nextPendingConnection();
        connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readClient()));
    }

}

void Server::readClient()
{
    ui->textEditrReceive->append(clientConnection->readAll());
}

void Server::clearText()
{
    ui->textEditrReceive->clear();
}

void Server::sendClient()
{
    QByteArray block;

    block.append(ui->textEditSend->toPlainText());
    clientConnection->write(block);

}

void Server::setListen()
{
    if(ui->pushButtonListen->text() == "Listen")
    {
        ui->pushButtonListen->setText("No Listen");
        ui->lineEditIP->setEnabled(false);
        ui->lineEditPort->setEnabled(false);
        QHostAddress hostAddress;
        hostAddress.setAddress(ui->lineEditIP->text());
        tcpServer->listen(hostAddress,
                          ui->lineEditPort->text().toInt());
    }
    else
    {
        ui->pushButtonListen->setText("Listen");
        if(tcpServer->isListening())
            tcpServer->close();
        ui->lineEditIP->setEnabled(true);
        ui->lineEditPort->setEnabled(true);
    }
}
