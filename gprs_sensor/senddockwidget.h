#ifndef SENDDOCKWIDGET_H
#define SENDDOCKWIDGET_H

#include <QDockWidget>
class QTextEdit;
class QRadioButton;
class QPushButton;

enum SendMode{    BrocastUpdate,
                  BrocastDebug,
                  SelectUpdate,
                  SelectDebug,
                  Other
             };

class SendDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit SendDockWidget(QWidget *parent = 0);
    QString toPlainText();
    QString  message;
signals:
    void sendButtonClick();
public slots:
    void sendModeChange(bool);

private:
    QTextEdit * sendTextEdit;
    QPushButton * sendButton;
    QRadioButton * brocastUpdateButton;
    QRadioButton * brocastDebugButton;
    QRadioButton * selectUpdateButton;
    QRadioButton * selectDebugButton;
    QRadioButton * otherButton;
    SendMode sendMode;

};

#endif // SENDDOCKWIDGET_H
