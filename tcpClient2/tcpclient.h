#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QDialog>


namespace Ui {
class tcpClient;
}
class QTcpSocket;

class tcpClient : public QDialog
{
    Q_OBJECT

public:
    explicit tcpClient(QWidget *parent = 0);
    ~tcpClient();

private slots:
    void connectTcpServer();
    void sendData(void);
    void receiveData(void);
    void clearText(void);

private:
    Ui::tcpClient *ui;

    QTcpSocket * client;
};

#endif // TCPCLIENT_H
