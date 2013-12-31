#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nehewidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    glWidget = new NeHeWidget();
    this->setCentralWidget(glWidget);


}

MainWindow::~MainWindow()
{
    delete ui;
}

