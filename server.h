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

private slots:
    void ReadData();
    void new_client();
    void send(QString );
    void Dcode(QString);
    void conn();
    void timeout();
    void on_startbtn_clicked();
};

#endif // SERVER_H
