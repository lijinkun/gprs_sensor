#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QList>
#include <QtWidgets>
#include <QtNetwork>
#include <QTcpSocket>
#include <QDebug>

tcpClient::tcpClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tcpClient)
{
    ui->setupUi(this);

    this->setWindowTitle("Client");
    client = new QTcpSocket(this);


    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    ui->lineEditIP->setText(ipAddressesList.at(0).toString());
    ui->lineEditPort->setValidator(new QIntValidator(1, 65535, this));

    QObject::connect(ui->pushButtonConnect, SIGNAL(clicked()), this, SLOT(connectTcpServer()));
    QObject::connect(ui->pushButtonQuit, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->pushButtonSend, SIGNAL(clicked()), this, SLOT(sendData()));
    QObject::connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(clearText()));
    QObject::connect(client, SIGNAL(readyRead()), this, SLOT(receiveData()));

}

tcpClient::~tcpClient()
{
    delete ui;
}

void tcpClient::connectTcpServer()
{
    if(ui->pushButtonConnect->text() == "Connect")
    {
        ui->pushButtonConnect->setText("DisConnect");
        client->abort();
        QHostAddress hostAddress;
        hostAddress.setAddress(ui->lineEditIP->text());
        client->connectToHost(hostAddress,
                             ui->lineEditPort->text().toInt());
        ui->lineEditPort->setEnabled(false);
        ui->lineEditIP->setEnabled(false);

    }
    else
    {
        ui->pushButtonConnect->setText("Connect");
        client->abort();
        ui->lineEditPort->setEnabled(true);
        ui->lineEditIP->setEnabled(true);
    }
}

void tcpClient::sendData()
{
    QByteArray block;

    block.append(ui->textEditSend->toPlainText());
    client->write(block);
}

void tcpClient::receiveData()
{
    ui->textEditrReceive->append(client->readAll());
}

void tcpClient::clearText()
{
    ui->textEditrReceive->clear();
}
