#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    TreeView * treeView;
    QStandardItemModel * mode;
    QStandItem * item;
    QTextEdit * sendTextEdit;
    QTextEdit * receTextEdit;
    QList <QRadioButton *> radioButtonList;
    QPushButton * sendButton;
    QPushButton * clearButton;
    QPushButton * saveButton;
    TreeView * nodeView;
    GLWindow * struct3DScene;

};

#endif // MAINWINDOW_H
