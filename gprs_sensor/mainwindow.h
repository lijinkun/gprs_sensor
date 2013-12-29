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
class QTextEdit;
class QPushButton;
class QRadioButton;
class QList<QRadioButton>;
class QTableView;
class GLWindow;
class SettingsDialog;
//class QSerialPort;

enum PortType{Serial, Tcp, Debug};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void treeDockShowPolicy(void);
    void receDockShowPolicy(void);
    void sendDockShowPolicy(void);

    void selectSerialPort(void);
    void setSerialPort(void);
    bool openSerialPort(void);
    void closeSerialPort(void);
    void writeData(const QByteArray &data);
    void readData(void);
    void handleError(QSerialPort::SerialPortError error);

    void openPort(void);
    void closePort(void);

    void howToUse(void);
private:

    void initActionsConnections();
private:
    Ui::MainWindow *ui;
    QDockWidget * treeDockWidget;
    TreeView * treeView;
    QStandardItemModel * mode;
    QStandItem * item;

    QDockWidget * sendDockWidget;
    QTextEdit * sendTextEdit;
    QList <QRadioButton *> radioButtonList;
    QPushButton * sendButton;
    QPushButton * clearButton;
    QPushButton * saveButton;

    QDockWidget * receDockWidget;
    QTextEdit * receTextEdit;


    TreeView * nodeView;
    GLWindow * struct3DScene;


    SettingsDialog *settings;
    QSerialPort *serial;
    PortType portType;



};

#endif // MAINWINDOW_H
