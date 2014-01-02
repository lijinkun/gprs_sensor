#ifndef TCPSERVERDIALOG_H
#define TCPSERVERDIALOG_H

#include <QDialog>

namespace Ui {
class TcpServerDialog;
}

class QTcpServer;
class QTcpSocket;
class QHostAddress;


class TcpServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TcpServerDialog(QWidget *parent = 0);
    ~TcpServerDialog();
    bool serverListen(bool);
    void writeClient(QString);
signals:
    void readReady(QString str);
private slots:
    void readClient(void);
    void acceptConnection(void);
private:

    QHostAddress getIP(void);
    int getPort(void);
private:
    Ui::TcpServerDialog *ui;
    QTcpServer *tcpServer;
    QTcpSocket *clientConnection;
    QString currentMessage;
};

#endif // TCPSERVERDIALOG_H
