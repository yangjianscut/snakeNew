#include "doublegame.h"
#include "ui_doublegame.h"

doublegame::doublegame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::doublegame),player1(10,5),player2(17,10)
{
    ui->setupUi(this);
    repaint();
}

//开始按钮触发
void doublegame::on_startbtn_clicked()
{
    //设定速度
    speed=ui->speed->text().toInt();
    ui->speed->setFocusPolicy(Qt::NoFocus);
    this->setFocus();

    //for(int i=1;i<=5;i++) player.eatplus();
    Timer= new QTimer(this);
    Timer->start(speed);

    //设定计时器到时间后的事件
    connect(Timer,SIGNAL(timeout()),this,SLOT(timeout()));

    //初始化随机数
    srand(time(0));

    //初始化好果子坏果子
    updatebad();
    updategood();
    score1=0;
    score2=0;

    //设定积分榜
    ui->score->setText("1号："+QString::number(score1)+"分 2号："+QString::number(score2)+"分");

}

doublegame::~doublegame()
{
    delete ui;
}

//绘图模块
void doublegame::paintEvent(QPaintEvent*)
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
    for(int i = 0; i<player1.getlength(); i++)
    {
        paint.fillRect(QRect(player1.list[i].x()*15,player1.list[i].y()*15,15,15),Qt::red);
        qDebug()<<player1.list[i].x()<<","<<player1.list[i].y()<<endl;

    }

    for(int i = 0; i<player2.getlength(); i++)
    {
        paint.fillRect(QRect(player2.list[i].x()*15,player2.list[i].y()*15,15,15),Qt::blue);
        qDebug()<<player2.list[i].x()<<","<<player2.list[i].y()<<endl;

    }

    //画好果子
    paint.fillRect(QRect(goodfood.x()*15,goodfood.y()*15,15,15),Qt::yellow);
    //画坏果子
    paint.fillRect(QRect(badfood.x()*15,badfood.y()*15,15,15),Qt::black);
}

//键盘监听
//对于player1,WSAD代表上下左右
//对于plyaer2,方向键控制上下左右
void doublegame::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:    player1.move(0,-1);  break;
        case Qt::Key_W:     player2.move(0,-1);  break;
        case Qt::Key_Down:  player1.move(0,1);   break;
        case Qt::Key_S:     player2.move(0,1);   break;
        case Qt::Key_Left:  player1.move(-1,0);  break;
        case Qt::Key_A:     player2.move(-1,0);  break;
        case Qt::Key_Right: player1.move(1,0);   break;
        case Qt::Key_D:     player2.move(1,0);   break;
    }
}

//计时器触发
void doublegame::timeout()
{
    //两蛇移动
    player1.moveon();
    player2.moveon();

    //1号碰到了墙
    if(player1.getHead().x()<0||player1.getHead().x()>=20||player1.getHead().y()<0||player1.getHead().y()>=25)
    {
        QMessageBox::about(this, "1号碰到了墙", "游戏结束");
        exit(0);
    }

    //2号碰到了墙
    if(player2.getHead().x()<0||player2.getHead().x()>=20||player2.getHead().y()<0||player2.getHead().y()>=25)
    {
        QMessageBox::about(this, "2号碰到了墙", "游戏结束");
        exit(0);
    }

    //吃到了自己
    if(player1.eatself()||player2.eatself())
    {
        QMessageBox::about(this, "吃到了自己", "游戏结束");
        exit(0);
    }

    //两蛇相撞
    if(crash())
    {
        QMessageBox::about(this, "相撞", "游戏结束");
        exit(0);
    }

    //1吃到好果子
    if(player1.getHead()==goodfood)
    {
        player1.eatplus();
        updategood();
        score1++;
    }

    //2吃到好果子
    if(player2.getHead()==goodfood)
    {
        player2.eatplus();
        updategood();
        score2++;
    }

    //1吃到坏果子
    if(player1.getHead()==badfood)
    {
        player1.eatdev();
        updatebad();
        score1--;
    }

    //2吃到坏果子
    if(player2.getHead()==badfood)
    {
        player2.eatdev();
        updatebad();
        score2--;
    }

    //显示分数
    ui->score->setText("1号："+QString::number(score1)+"分 2号："+QString::number(score2)+"分");
    //重绘界面
    this->update();
    repaint();

    //计时器重新开始计时
    Timer->start(speed);
    //qDebug()<<"yes"<<endl;
}

//更新好果子
void doublegame::updategood()
{
    //找出一个不与蛇重合，坏果子重合的点
    while(true)
    {
        goodfood=QPoint(rand()%20,rand()%25);
        bool flag=true;
        for(int i=0;i<player1.getlength();i++)
            if(player1.list[i].x()==goodfood.x()&&player1.list[i].y()==goodfood.y())
            {
                flag=false;
                break;
            }
        for(int i=0;i<player2.getlength();i++)
            if(player2.list[i].x()==goodfood.x()&&player2.list[i].y()==goodfood.y())
            {
                flag=false;
                break;
            }
        if(goodfood==badfood) flag=false;
        if(flag) break;
    }
}

//更新坏果子
void doublegame::updatebad()
{
    //找出一个不与蛇重合，好果子重合的点
    while(true)
    {
        badfood=QPoint(rand()%20,rand()%25);
        bool flag=true;
        for(int i=0;i<player1.getlength();i++)
            if(player1.list[i].x()==badfood.x()&&player1.list[i].y()==badfood.y())
            {
                flag=false;
                break;
            }
        for(int i=0;i<player2.getlength();i++)
            if(player2.list[i].x()==badfood.x()&&player2.list[i].y()==badfood.y())
            {
                flag=false;
                break;
            }
        if(goodfood==badfood) flag=false;
        if(flag) break;
    }
}

//碰撞判断
bool doublegame::crash()
{
    //两只蛇互相判断蛇头是否重叠
    for(int i=0;i<player1.getlength();i++)
        if(player1.list[i]==player2.getHead()) return true;

    for(int i=0;i<player2.getlength();i++)
        if(player2.list[i]==player1.getHead()) return true;

    return false;
}
