#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
namespace Ui {
class MainWindow;
}

class TreeView;
class QStandardItemModel;
class QStandItem;
class QTableView;
class GLWindow;
class SettingsDialog;
class TcpServerDialog;
class ReceDockWidget;
class SendDockWidget;

enum PortType{Serial, Tcp};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void writeSerialData(const QString data);
    void writeTcpData(const QString data);

private slots:
    void treeDockShowPolicy(void);
    void receDockShowPolicy(void);
    void sendDockShowPolicy(void);

    void selectSerialPort(void);
    void setSerialPort(void);
    bool openSerialPort(void);
    void closeSerialPort(void);
    void readSerialData(void);
    void handleError(QSerialPort::SerialPortError error);

    void selectTcpPort(void);
    void setTcpPort(void);
    bool openTcpPort(void);
    bool closeTcpPort(void);
    void readTcpData(QString str);

    void openPort(void);
    void closePort(void);
    void sendData(void);

    void howToUse(void);
private:
    void initAllConnections();
private:
    Ui::MainWindow *ui;

    QDockWidget * treeDockWidget;
    TreeView * treeView;
    QStandardItemModel * mode;
    QStandItem * item;

    SendDockWidget * sendDockWidget;
    ReceDockWidget * receDockWidget;

    TreeView * nodeView;
    GLWindow * struct3DScene;

    PortType portType;
    SettingsDialog *settings;
    QSerialPort *serial;
    TcpServerDialog * tcpServer;

};

#endif // MAINWINDOW_H
