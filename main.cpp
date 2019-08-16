#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "snake.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //qDebug()<<"yes"<<endl;
    //snake s;
    //s.test();
    //gamebox box;
   // box.show();
    return a.exec();
}
