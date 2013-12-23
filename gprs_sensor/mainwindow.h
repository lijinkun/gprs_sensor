#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QTreeView;
class QStandardItemModel;
class QStandItem;
class QTextEdit;
class QPushButton;
class QRadioButton;
class QList<QRadioButton>;
class QTableView;
class QGLWidget;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
   // void subResize();

private:
  //  void allSignalConnect();
private:
    Ui::MainWindow *ui;
    QTreeView * treeView;
    QStandardItemModel * mode;
    QStandItem * item;
    QTextEdit * sendTextEdit;
    QTextEdit * receTextEdit;
    QList <QRadioButton *> radioButtonList;
    QPushButton * sendButton;
    QPushButton * clearButton;
    QPushButton * saveButton;
    QTableView * nodeTable;
    QGLWidget * struct3DScene;

};

#endif // MAINWINDOW_H
