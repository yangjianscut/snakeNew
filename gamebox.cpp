#include "gamebox.h"
#include "ui_gamebox.h"

gamebox::gamebox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamebox)
{
    ui->setupUi(this);
    repaint();
}

//开始按钮触发
void gamebox::on_startbtn_clicked()
{
    //设定速度
    speed=ui->speed->text().toInt();
    //for(int i=1;i<=5;i++) player.eatplus();
    Timer= new QTimer(this);

    //开始计时
    Timer->start(speed);

    //设定计时器到时间后的事件
    connect(Timer,SIGNAL(timeout()),this,SLOT(timeout()));
    srand(time(0));

    //初始化好果子坏果子
    updatebad();
    updategood();
    score=0;

    //设定积分榜
    ui->score->setText(QString::number(score)+"分");
}

//绘图模块
void gamebox::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    //绘制地图
    QPainter paint(this);
    for(int i = 0; i<15*20;i+=15)
    {
        for(int j = 0; j<15*25;j+=15)
        {
            paint.drawRect(i,j,15,15);  //绘制方格
        }
    }

    //绘制食物
    //paint.drawImage(food[0]*20,food[1]*20,QImage(":/images/red").scaled(QSize(20,20)));

    //绘制蛇
    for(int i = 0; i<player.getlength(); i++)
    {
        paint.fillRect(QRect(player.list[i].x()*15,player.list[i].y()*15,15,15),Qt::red);
        qDebug()<<player.list[i].x()<<","<<player.list[i].y()<<endl;

    }

    //画好果子
    paint.fillRect(QRect(goodfood.x()*15,goodfood.y()*15,15,15),Qt::yellow);
    //画坏果子
    paint.fillRect(QRect(badfood.x()*15,badfood.y()*15,15,15),Qt::black);
}

//键盘监听
//WSAD代表上下左右
//方向键也可以控制
void gamebox::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:    player.move(0,-1);  break;
        case Qt::Key_W:     player.move(0,-1);  break;
        case Qt::Key_Down:  player.move(0,1);   break;
        case Qt::Key_S:     player.move(0,1);   break;
        case Qt::Key_Left:  player.move(-1,0);  break;
        case Qt::Key_A:     player.move(-1,0);  break;
        case Qt::Key_Right: player.move(1,0);   break;
        case Qt::Key_D:     player.move(1,0);   break;
    }
}

gamebox::~gamebox()
{
    delete ui;
}

//计时器触发
void gamebox::timeout()
{
    //蛇移动
    player.moveon();

    //碰到了墙
    if(player.getHead().x()<0||player.getHead().x()>=20||player.getHead().y()<0||player.getHead().y()>=25)
    {
        QMessageBox::about(this, "碰到了墙", "游戏结束");
        exit(0);
    }

    //吃到了自己
    if(eatself())
    {
        QMessageBox::about(this, "吃到了自己", "游戏结束");
        exit(0);
    }

    //吃到好果子
    if(player.getHead()==goodfood)
    {
        player.eatplus();
        updategood();
        score++;
    }

    //吃到坏果子
    if(player.getHead()==badfood)
    {
        player.eatdev();
        updatebad();
        score--;
    }

    //显示分数
    ui->score->setText(QString::number(score)+"分");
    //重绘界面
    this->update();
    repaint();
    Timer->start(speed);
    //qDebug()<<"yse"<<endl;
}

//更新好果子
void gamebox::updategood()
{
    //找出一个不与蛇重合，坏果子重合的点
    while(true)
    {
        goodfood=QPoint(rand()%20,rand()%25);
        bool flag=true;
        for(int i=0;i<player.getlength();i++)
            if(player.list[i].x()==goodfood.x()&&player.list[i].y()==goodfood.y())
            {
                flag=false;
                break;
            }
        if(goodfood==badfood) flag=false;
        if(flag) break;
    }
}

//更新坏果子
void gamebox::updatebad()
{
    //找出一个不与蛇重合，好果子重合的点
    while(true)
    {
        badfood=QPoint(rand()%20,rand()%25);
        bool flag=true;
        for(int i=0;i<player.getlength();i++)
            if(player.list[i].x()==badfood.x()&&player.list[i].y()==badfood.y())
            {
                flag=false;
                break;
            }
        if(goodfood==badfood) flag=false;
        if(flag) break;
    }
}

//吃到了自己
bool gamebox::eatself()
{
    for(int i=1;i<player.getlength();i++)
        if(player.list[i]==player.getHead()) return true;
    return false;
}
