#include "tcpserverdialog.h"
#include "ui_tcpserverdialog.h"
#include <QTcpSocket>
#include <QtNetwork>
#include <QDebug>

TcpServerDialog::TcpServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpServerDialog)
{
    ui->setupUi(this);

    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    ui->lineEditIP->setText(ipAddressesList.at(0).toString());
    ui->lineEditPort->setValidator(new QIntValidator(1, 65535, this));

    //clientConnection = NULL;
    tcpServer = new QTcpServer(this);
    QObject::connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

TcpServerDialog::~TcpServerDialog()
{
    delete ui;
}

QHostAddress TcpServerDialog::getIP(void)
{
    QHostAddress hostAddress;
    hostAddress.setAddress(ui->lineEditIP->text());
    return hostAddress;

}

int TcpServerDialog::getPort(void)
{
    return ui->lineEditPort->text().toInt();
}

void TcpServerDialog::readClient(void)
{
     currentMessage = clientConnection->readAll();
     qDebug() << "the message is " << endl <<
                 currentMessage << "the conteis clientConnection->readAll();" ;
     emit readReady(currentMessage);
}

void TcpServerDialog::writeClient(QString str)
{
    QByteArray block;

    block.append(str);
    if(clientConnection != NULL)
        clientConnection->write(block);
}

bool TcpServerDialog::serverListen(bool listen)
{
    if(listen == true)
    {
        if(!tcpServer->isListening())
        {
            ui->lineEditIP->setEnabled(false);
            ui->lineEditPort->setEnabled(false);
            tcpServer->listen(getIP(), getPort());
            return true;
        }
    }
    else if(listen == false)
    {
        if(tcpServer->isListening())
            tcpServer->close();
        ui->lineEditIP->setEnabled(true);
        ui->lineEditPort->setEnabled(true);
        return true;

    }

    return false;
}

void TcpServerDialog::acceptConnection()
{
    if(tcpServer->isListening())
    {
        clientConnection = tcpServer->nextPendingConnection();
        connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readClient()));
    }

}
