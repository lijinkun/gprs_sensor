#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;


private slots:
    void aboutSlot();
    void checkSlot();
    void changeLineSlot();
    void setFontSlot();
    void setcolorSlot();
    void quitSlot();
    void saveFileSlot();
    void saveAsFileSlot();
    void openFileSlot();
    void newFileSlot();
    void currentDateTimeSlot();
   // void findSlot();//涉及到多窗口操作，暂时不进行设计

};

#endif // MAINWINDOW_H
