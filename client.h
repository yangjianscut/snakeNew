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
    QTcpSocket *mSocket;

    void paintEvent(QPaintEvent*);
    QTimer* Timer;//计时器
    void keyPressEvent(QKeyEvent* event);
    snake player1,player2;
    int setDiretion;
    QPoint goodfood, badfood;//好果子坏果子位置
    void updategood();//更新好果子
    void updatebad();//更新坏果子
    bool crash();//相撞
    int score1,score2,speed;
    QString ip;
    void send(QString);
    void Dcode(QString);

private slots:
    void ReadData();
    void on_startbtn_clicked();
    void conn();

};

#endif // CLIENT_H
