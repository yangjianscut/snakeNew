#ifndef GAMEBOX_H
#define GAMEBOX_H

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
class gamebox;
}

class gamebox : public QWidget
{
    Q_OBJECT

public:
    explicit gamebox(QWidget *parent = nullptr);
    ~gamebox();

public slots:
    void timeout();
    void on_startbtn_clicked();//按压开始按钮

private:
    Ui::gamebox *ui;
    void paintEvent(QPaintEvent*);
    QTimer* Timer;//计时器
    void keyPressEvent(QKeyEvent* event);
    snake player;//玩家
    int setDiretion;//方向
    QPoint goodfood, badfood;//好果子坏果子
    void updategood();//更新好果子
    void updatebad();//更新坏果子
    bool eatself();//判断有没有吃到自己
    int score,speed;//分数、速度
};

#endif // GAMEBOX_H
