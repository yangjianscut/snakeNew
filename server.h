#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QString>
#include <QPainter>
#include "snake.h"
#include <QRect>
#include "QTimer"
#include <QTime>
#include <QKeyEvent>
#include <QMessageBox>
#include <QKeyEvent>
#include <cstdlib>
#include <QHostInfo>

namespace Ui {
class server;
}

class server : public QWidget
{
    Q_OBJECT

public:
    explicit server(QWidget *parent = nullptr);
    ~server();


private:
    Ui::server *ui;
    QTcpServer *mServer;
    QTcpSocket *mSocket;
    void paintEvent(QPaintEvent*);//绘图
    QTimer* Timer;//计时器
    void keyPressEvent(QKeyEvent* event);//按键
    snake player1,player2;//玩家
    int setDiretion;
    QPoint goodfood, badfood;//好果子坏果子位置
    void updategood();//更新好果子
    void updatebad();//更新坏果子
    bool crash();//相撞
    int score1,score2,speed;

private slots:
    void ReadData();//读数据
    void new_client();//新客户端
    void send(QString );//发送数据
    void Dcode(QString);//解码
    void conn();//连接
    void timeout();//计时器触发
    void on_startbtn_clicked();
};

#endif // SERVER_H
