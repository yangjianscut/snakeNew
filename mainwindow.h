#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include "gamebox.h"
#include "doublegame.h"
#include "server.h"
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton* startbtn;
    QPushButton* returnbtn;//结束按钮
    gamebox* box;//单人游戏
    client* mclient;//客户端
    server* mserver;//服务器端
    doublegame* doublebox;//双人游戏

public slots:
    void singleslot();//单人
    void doubleslot();//双人
    void exitslot();//结束按钮
    void webserverslot();//服务器
    void webclientslot();//客户端
    void paintEvent(QPaintEvent *);//绘图组件
};

#endif // MAINWINDOW_H
