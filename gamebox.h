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

private:
    Ui::gamebox *ui;
    void paintEvent(QPaintEvent*);
    QTimer* Timer;//计时器
    void keyPressEvent(QKeyEvent* event);
    snake player;//玩家
    int setDiretion;
    QPoint goodfood, badfood;//好果子坏果子
    void updategood();
    void updatebad();
    bool eatself();
    int score,speed;//分数、速度
};

#endif // GAMEBOX_H
