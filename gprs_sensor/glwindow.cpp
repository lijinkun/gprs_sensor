#include "glwindow.h"
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <math.h>
#include <QImage>
#include <GL/GLU.h>
#include <QList>
#include <QVector>
#include <QDebug>

GLWindow::GLWindow(QWidget *parent) :
   QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

    rPoint = 0.0;
    zMove = xMove = yMove =0.0;
    setGeometry( 0, 0, 640, 480 );
    setFocusPolicy(Qt::ClickFocus);


}

GLWindow::~GLWindow()
{
}

void GLWindow::showExample()
{
    addRoot(3);
    addRoot(6);
    addRoot(3);
    addRoot(3);
    addRoot(3);
    addRoot(3);
    addRoot(6);
    addRoot(3);
    addRoot(3);
    addRoot(3);
    addNode(1,1);
    addNode(2,1);
    addNode(3,1);
    addNode(4,1);
    addNode(5,1);

}
void GLWindow::initializeGL()
{

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

}

void GLWindow::drawGrid(void)
{

    glPushAttrib(GL_CURRENT_BIT);

    glPushMatrix();
     glLoadIdentity();
     glTranslatef(  0.0, -10.0 , 0.0);
     glColor3f(1.0, 1.0, 1.0);
     for(GLfloat i = -200; i <= 200; i+= 5)
     {
         glBegin(GL_LINES);
         glVertex3f(-200, 0, i);
         glVertex3f(200, 0, i);
         glVertex3f(i, 0, -200);
         glVertex3f(i, 0, 200);
         glEnd();

     }
     glPopMatrix();
     glPopAttrib();

}
void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawGrid();
    buildRoot();

   // QMetaObject::invokeMethod(this,"updateGL",Qt::QueuedConnection);

}

void GLWindow::resizeGL(int width, int height)
{


    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLdouble rFov = 45.0 * 3.14159265 / 180.0;
    glFrustum( -0.1 * tan( rFov / 2.0 ) * (GLfloat)width/(GLfloat)height,
                   0.1 * tan( rFov / 2.0 ) * (GLfloat)width/(GLfloat)height,
                 -0.1 * tan( rFov / 2.0 ),
                   0.1 * tan( rFov / 2.0 ),
                  0.1, 200.0  );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWindow::buildNode(qint32 num)
{
    glPushAttrib(GL_CURRENT_BIT);


    for(int i = 0; i < nodeList.size(); ++i)
    {
        glPushMatrix();

        glTranslatef(  0.0,  0.0, 0.0);
        glBegin( GL_LINES );

        glColor3f( 1.0, 0.0, 0.0 );
        glVertex3f(  0.0,  0.0,  0.0 );
        glColor3f( 0.0, 1.0, 0.0 );
        if(i % 2 == 0 && i != 0)
            glVertex3f( 2.0 * i-1, -20,  0.0 );
        else if(i % 2 != 0 && i != 0)
            glVertex3f( 2.0 * -i, -20,  0.0 );
        else
            glVertex3f( 0.0, -20,  0.0 );


        glEnd();

        if(i % 2 == 0 && i != 0)
            glTranslatef( 2.0 * i-1, -20,  0.0 );
        else if(i % 2 != 0 && i != 0)
            glTranslatef( 2.0 * -i, -20,  0.0 );
        else
            glTranslatef( 0.0, -20,  0.0 );

        glColor3f(0.0, 1.0, 0.0);

        glPointSize( 100 - 10 - 10*num + zMove/2);
                //进行平滑处理
        glEnable(GL_POINT_SMOOTH);
        //glHint(GL_POINT_SMOOTH,GL_NICEST);
               //开始绘点
        glBegin(GL_POINTS);
        glVertex3f(0.0, 0.0, 0.0);
               //结束绘点
        glEnd();

        glPopMatrix();
    }


    glPopAttrib();


}

void GLWindow::addNode(qint32 nodeID, qint32 rootID)
{
    Q_UNUSED(rootID);

    nodeList.push_back(nodeID);

}

void GLWindow::addRoot(qint32 rootID)
{
    structList.push_back(rootID);
    qDebug() << structList.size() << ":" << rootID;
}

void GLWindow::buildRoot(void)
{
    glPushAttrib(GL_CURRENT_BIT);

    glPushMatrix();
    glLoadIdentity();

    for(int i = 0; i <= structList.size(); ++i)
    {
        glLoadIdentity();
        glTranslatef(  xMove+4.0, 10, -10-20*i +zMove);
        glColor3f(0.0, 1.0, 1.0);

        glPointSize( 100 -10 - 10*i + zMove/2);
                //进行平滑处理
        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH,GL_NICEST);
               //开始绘点
        glBegin(GL_POINTS);
        glVertex3f(0.0, 0.0, 0.0);
               //结束绘点
        glEnd();
        glRotatef(rPoint, 0.0,1.0,0.0);
        buildNode(i);
    }

    glPopMatrix();
    glPopAttrib();
}
void GLWindow::keyPressEvent( QKeyEvent *e )
{
  switch ( e->key() )
  {
  case Qt::Key_0:
      updateGL();
      break;
  case Qt::Key_Up:
      if(zMove < 200)
      {
          zMove += 1;
          zMove += 1;
      }
      updateGL();
      break;
  case Qt::Key_Down:
      if(zMove > -200)
      {
          zMove -= 1;
          zMove -= 1;
      }
      updateGL();
      break;
  case Qt::Key_Left:
      xMove += 2.0;
      xMove += 5.0;
      updateGL();
      break;
  case Qt::Key_Right:
      xMove -= 2.0;
      xMove -= 5.0;
      updateGL();
      break;
  case Qt::Key_A:
      yMove += 2.0;
      yMove += 5.0;
      updateGL();
      break;
  case Qt::Key_D:
      yMove -= 2.0;
      yMove -= 5.0;
      updateGL();
      break;

  case Qt::Key_S:
      rPoint += 5.0;
      if(rPoint > 360)
          rPoint = 0.0;
      updateGL();
      break;
  case Qt::Key_Escape:
    close();
  }
}

