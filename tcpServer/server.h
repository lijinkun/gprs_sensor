#ifndef SERVER_H
#define SERVER_H

#include <QDialog>

namespace Ui {
class Server;
}
class QTcpServer;
class QTcpSocket;
class QHostAddress;

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();
private slots:
    void acceptConnection();
    void readClient();
    void sendClient(void);
    void clearText(void);
    void setListen(void);
private:
    Ui::Server *ui;
    QTcpServer *tcpServer;
    QTcpSocket *clientConnection;

};

#endif // SERVER_H
