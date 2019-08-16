#ifndef DOUBLEGAME_H
#define DOUBLEGAME_H

#include <QWidget>
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
class doublegame;
}

class doublegame : public QWidget
{
    Q_OBJECT

public:
    explicit doublegame(QWidget *parent = nullptr);
    ~doublegame();

public slots:
    void timeout();//时间结束时进行操作

private:
    Ui::doublegame *ui;
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
};

#endif // DOUBLEGAME_H
