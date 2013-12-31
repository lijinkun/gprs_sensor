#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   // QPixmap pixmap("screen.png");
   // QSplashScreen splash(pixmap);
   // splash.show();
   // a.processEvents();
   // for(long index = 0; index < 800000000; index++);

    MainWindow w;
    w.show();
   // splash.finish(&w);
    return a.exec();
}
