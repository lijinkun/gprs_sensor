#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("untitled.txt");
    ui->statusBar->hide();

    QObject::connect(ui->aboutAction, SIGNAL(triggered()), this, SLOT(aboutSlot()));
    QObject::connect(ui->checkAction, SIGNAL(triggered()), this, SLOT(checkSlot()));
    QObject::connect(ui->autoLineAction, SIGNAL(triggered()), this, SLOT(changeLineSlot()));
    QObject::connect(ui->fontAction, SIGNAL(triggered()), this, SLOT(setFontSlot()));
    QObject::connect(ui->colorAction, SIGNAL(triggered()), this, SLOT(setcolorSlot()));
    QObject::connect(ui->quitAction, SIGNAL(triggered()), this, SLOT(quitSlot()));
    QObject::connect(ui->saveFileAction, SIGNAL(triggered()), this, SLOT(saveFileSlot()));
    QObject::connect(ui->saveAsFileAction, SIGNAL(triggered()), this, SLOT(saveAsFileSlot()));
    QObject::connect(ui->openFileAction, SIGNAL(triggered()), this, SLOT(openFileSlot()));
    QObject::connect(ui->newFileAction, SIGNAL(triggered()), this, SLOT(newFileSlot()));
    QObject::connect(ui->undoAction, SIGNAL(triggered()), ui->textEdit, SLOT(undo()));
    QObject::connect(ui->copyAction, SIGNAL(triggered()), ui->textEdit, SLOT(copy()));
    QObject::connect(ui->cutAction, SIGNAL(triggered()), ui->textEdit, SLOT(cut()));
    QObject::connect(ui->pasteAction, SIGNAL(triggered()), ui->textEdit, SLOT(paste()));
    QObject::connect(ui->allSelectAction, SIGNAL(triggered()), ui->textEdit, SLOT(selectAll()));
    QObject::connect(ui->dateAction, SIGNAL(triggered()), this, SLOT(currentDateTimeSlot()));
    //QObject::connect(ui->dateAction, SIGNAL(triggered()), ui->textEdit, SLOT()


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(ui->textEdit->document()->isModified())
    {

    }
    else
    {
        event->accept();
    }

}

void MainWindow::aboutSlot()
{
    QMessageBox::information(this,"帮助信息","this is a opensource software writed by lijinkun");
}

void MainWindow::checkSlot()
{
    if(ui->statusBar->isHidden())
    {
        ui->statusBar->show();
    }
    else
    {
        ui->statusBar->hide();
    }
}

void MainWindow::changeLineSlot()
{
    if(ui->textEdit->horizontalScrollBarPolicy() == Qt::ScrollBarAlwaysOn)
        ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    else
        ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

}

void MainWindow::setFontSlot()
{
    bool ok;
    QFont font = QFontDialog::getFont(
                    &ok, QFont("Helvetica [Cronyx]", 10), this);
    if (ok) {
        ui->textEdit->setFont(font);
    }
}

void MainWindow::setcolorSlot()
{
    QColor color = QColorDialog::getColor();
    ui->textEdit->setTextColor(color);
}

void MainWindow::quitSlot()
{
    if(ui->textEdit->document()->isModified())
    {
        QMessageBox msgBox;
        msgBox.setText("the file is modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Save:
              break;
          case QMessageBox::Discard:
              this->close();
              break;
          case QMessageBox::Cancel:
              break;
          default:
              break;
        }
    }
    else
        this->close();

}

void MainWindow::saveFileSlot()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "../"+this->windowTitle(), tr("Textfiles (*.txt)"));

    QFile * file = new QFile;
    file->setFileName(fileName);
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(file);
    out << ui->textEdit->toPlainText();
    file->close();
    delete file;

    this->setWindowTitle(fileName);
}

void MainWindow::saveAsFileSlot()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                              "../"+this->windowTitle(), tr("*.*"));

  /*  QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();为什么该种方式无法实现？*/

    QFile * file = new QFile;
    file->setFileName(fileName);
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(file);
    out << ui->textEdit->toPlainText();
    file->close();
    delete file;

}


void MainWindow::openFileSlot()
{
    if(ui->textEdit->document()->isModified())
    {
        QMessageBox msgBox;
        msgBox.setText("the file is modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        if(ret == QMessageBox::Save)
        {
             this->saveFileSlot();
        }
        else if(ret == QMessageBox::Discard)
        {
            QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                            "../"+this->windowTitle(),tr("*.*"));

            QFile *file = new QFile;
            file->setFileName((fileName));
            if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
                return;

            ui->textEdit->clear();
            QTextStream in(file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                ui->textEdit->append(line);
            }
            file->close();
            delete file;
        }
    }
    else
    {

        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "../"+this->windowTitle(),tr("*.*"));

        QFile *file = new QFile;
        file->setFileName((fileName));
        if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        ui->textEdit->clear();
        QTextStream in(file);
        while (!in.atEnd()) {
            QString line = in.readLine();

            ui->textEdit->append(line);
        }
        file->close();
        delete file;
    }
}

void MainWindow::newFileSlot()
{
    if(ui->textEdit->document()->isModified())
    {
        QMessageBox msgBox;
        msgBox.setText("the file is modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        if(ret == QMessageBox::Save)
        {
              this->saveFileSlot();
        }
        else if(ret == QMessageBox::Discard)
        {

              ui->textEdit->clear();
              this->setWindowTitle("untitld.txt");
        }
    }
    else
    {
        ui->textEdit->clear();
        this->setWindowTitle("untitld.txt");

    }
}

void MainWindow::currentDateTimeSlot()
{
    QDateTime datetime = QDateTime::currentDateTime();
    QString time = datetime.toString("yyyy-M-dd hh:mm:ss");
    ui->textEdit->append(time);
}

/*void MainWindow::findSlot()
{
    if(!tmptextEdit->find(str, QTextDocument::FindBackward)){    QMessageBox::warning(this, tr("Search"), tr("Cann't find %1")        .arg(str));}else    this->activateWindow();

}  */
