#ifndef RECEDOCKWIDGET_H
#define RECEDOCKWIDGET_H

#include <QDockWidget>

class QTextEdit;
class QPushButton;
class QString;


class ReceDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit ReceDockWidget(QWidget *parent = 0);

    void appendText(const QString &text);
    void setText(const QString &text);
    QString toPlainText(void);
signals:
public slots:
    void saveFile(void);
private:
    QTextEdit * receTextEdit;
    QPushButton * clearButton;
    QPushButton * saveButton;
    QWidget * receParent;


};

#endif // RECEDOCKWIDGET_H
