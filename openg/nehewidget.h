#ifndef NEHEWIDGET_H
#define NEHEWIDGET_H

#include <QGLWidget>


class QList <QList<qint32> >;
class QVector <QVector<int> >;

class NeHeWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit NeHeWidget(QWidget *parent = 0);
    ~NeHeWidget();
signals:

public slots:
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *e);
   // void mousePressEvent(QMouseEvent *e);
   // void mouseMoveEvent(QMouseEvent *e);
   // void mouseReleaseEvent(QMouseEvent *e);
    void buildList1(void);
    void buildNode(qint32 num);
    void buildRoot(void);
    void addNode(qint32 nodeID, qint32 rootID);
    void addRoot(qint32 rootID);
    void drawGrid(void);

private:
    GLfloat rPoint;
    GLuint	box, box1, box2, line;
    GLfloat zMove,xMove,yMove;


    QVector <int> structList;
    QVector <int> nodeList;


};

#endif // NEHEWIDGET_H
