#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
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

namespace Ui {
class client;
}

class client : public QWidget
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = nullptr);
    ~client();
public slots:
    void timeout();//时间结束时进行操作

private:
    Ui::client *ui;
    QTcpSocket *mSocket;//服务器

    void paintEvent(QPaintEvent*);//绘图
    QTimer* Timer;//计时器
    void keyPressEvent(QKeyEvent* event);//键盘监控
    snake player1,player2;//玩家
    int setDiretion;//方向
    QPoint goodfood, badfood;//好果子坏果子位置
    void updategood();//更新好果子
    void updatebad();//更新坏果子
    bool crash();//相撞
    int score1,score2,speed;
    QString ip;
    void send(QString);//发送信息
    void Dcode(QString);//解码信息

private slots:
    void ReadData();//读数据
    void on_startbtn_clicked();//开始按钮
    void conn();//触发连接

};

#endif // CLIENT_H
