#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QGLWidget>
class QVector <QVector<int> >;

class GLWindow : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWindow(QWidget *parent = 0);
    ~GLWindow();
public:
     void showExample(void);
signals:

public slots:


protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);
    virtual void keyPressEvent(QKeyEvent *e);
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

#endif // GLWINDOW_H
