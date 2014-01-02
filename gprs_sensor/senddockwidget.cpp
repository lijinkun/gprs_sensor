#include "senddockwidget.h"
#include <QTextEdit>
#include <QGroupBox>
#include <QPushButton>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

SendDockWidget::SendDockWidget(QWidget * parent) :
    QDockWidget(parent)
{
    message = "";

    sendTextEdit = new QTextEdit(this);
    sendTextEdit->setMinimumSize(100,100);
    sendTextEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    sendButton = new QPushButton("send",this);
    sendButton->setMaximumSize(100,50);
    sendButton->setMinimumSize(100,50);
    sendButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed );
    sendButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    brocastUpdateButton = new QRadioButton("all update");
    brocastDebugButton = new QRadioButton("all debug");
    selectUpdateButton = new QRadioButton("select update");
    selectDebugButton = new QRadioButton("select debug");
    otherButton = new QRadioButton("write in");

    QHBoxLayout * sendLayout1 = new QHBoxLayout();
    QHBoxLayout * sendLayout2 = new QHBoxLayout();
    QVBoxLayout * sendLayout3 = new QVBoxLayout();
    QHBoxLayout * sendLayout4 = new QHBoxLayout();
    QHBoxLayout * sendLayout5 = new QHBoxLayout();
    QHBoxLayout * sendLayout6 = new QHBoxLayout();
    QVBoxLayout * sendLayout7 = new QVBoxLayout();
    QHBoxLayout * sendLayout8 = new QHBoxLayout();
    sendLayout1->addWidget(brocastUpdateButton);
    sendLayout1->addWidget(brocastDebugButton);
    sendLayout2->addWidget(selectUpdateButton);
    sendLayout2->addWidget(selectDebugButton);
    sendLayout8->addWidget(otherButton);
    sendLayout3->addLayout(sendLayout1);
    sendLayout3->addLayout(sendLayout2);
    sendLayout3->addLayout(sendLayout8);
    sendLayout4->addWidget(sendButton);
    sendLayout5->addLayout(sendLayout3);
    sendLayout5->addLayout(sendLayout4);
    sendLayout6->addWidget(sendTextEdit);
    sendLayout7->addLayout(sendLayout6);
    sendLayout7->addLayout(sendLayout5);
    otherButton->setChecked(true);
    sendMode = Other;

    QGroupBox * sendBox = new QGroupBox("send");
    sendBox->setLayout(sendLayout7);

    this->setWidget(sendBox);

    QObject::connect(sendButton, SIGNAL(clicked()), this, SIGNAL(sendButtonClick()));
    QObject::connect(brocastUpdateButton, SIGNAL(toggled(bool)), this, SLOT(sendModeChange(bool)));
    QObject::connect(brocastDebugButton, SIGNAL(toggled(bool)), this, SLOT(sendModeChange(bool)));
    QObject::connect(selectUpdateButton, SIGNAL(toggled(bool)), this, SLOT(sendModeChange(bool)));
    QObject::connect(selectDebugButton, SIGNAL(toggled(bool)), this, SLOT(sendModeChange(bool)));
    QObject::connect(otherButton, SIGNAL(toggled(bool)), this, SLOT(sendModeChange(bool)));
}

QString SendDockWidget::toPlainText()
{
    switch(sendMode)
    {
    case BrocastUpdate:
        return "Update";
        break;
    case BrocastDebug:
        return "Debug";
        break;
    case SelectUpdate:
        return message + "Update";
        break;
    case SelectDebug:
        return message + "Update";
        break;
    case Other:
        return this->sendTextEdit->toPlainText();
    }
    return "error";
}

void SendDockWidget::sendModeChange(bool)
{

   if(brocastUpdateButton->isChecked())
        sendMode = BrocastUpdate;
   if(brocastDebugButton->isChecked())
       sendMode = BrocastDebug;
   if(selectUpdateButton->isChecked())
       sendMode = SelectUpdate;
   if(selectDebugButton->isChecked())
       sendMode = SelectDebug;
   if(otherButton->isChecked())
        sendMode = Other;
}
