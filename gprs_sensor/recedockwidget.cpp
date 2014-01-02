#include "recedockwidget.h"
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QDateTime>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

ReceDockWidget::ReceDockWidget(QWidget *parent) :
    QDockWidget(parent)
{
    receParent = parent;

    receTextEdit = new QTextEdit();
    receTextEdit->setMinimumSize(100,100);
    receTextEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    clearButton = new QPushButton("clear");
    clearButton->setMaximumSize(100,30);
    clearButton->setMinimumSize(100,30);
    clearButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed );
    clearButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    saveButton = new QPushButton("save");
    saveButton->setMaximumSize(100,30);
    saveButton->setMinimumSize(100,30);
    saveButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed );
    saveButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QHBoxLayout * receLayout1 = new QHBoxLayout();
    QHBoxLayout * receLayout2 = new QHBoxLayout();
    QVBoxLayout * receLayout3 = new QVBoxLayout();
    receLayout1->addWidget(receTextEdit);
    receLayout2->addWidget(saveButton);
    receLayout2->addWidget(clearButton);
    receLayout3->addLayout(receLayout1);
    receLayout3->addLayout(receLayout2);
    QGroupBox * receBox = new QGroupBox("receive");
    receBox->setLayout(receLayout3);

    this->setWidget(receBox);

    QObject::connect(clearButton, SIGNAL(clicked()), receTextEdit, SLOT(clear()));
    QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(saveFile()));
  //  QObject::connect(saveButton, SIGNAL(clicked()), this, SIGNAL(saveButtonClick()));
}

void ReceDockWidget::appendText(const QString &text)
{

    receTextEdit->append(text);
}

void ReceDockWidget::setText(const QString &text)
{
    receTextEdit->setText(text);
}
void ReceDockWidget::saveFile(void)
{
    QDateTime datetime = QDateTime::currentDateTime();
    QString time = datetime.toString("yy.MM.dd.hh.m");

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "./data/"+time, tr("Textfiles (*.txt)"));
    QFile * file = new QFile;
    file->setFileName(fileName);
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(file);
    out << this->receTextEdit->toPlainText();
    file->close();
    delete file;
}

QString ReceDockWidget::toPlainText(void)
{
    return this->receTextEdit->toPlainText();
}
