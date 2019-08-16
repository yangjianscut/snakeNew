#include "client.h"
#include "ui_client.h"

client::client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::client),player1(10,5),player2(17,10)
{
    ui->setupUi(this);
}

void client::on_startbtn_clicked()
{
    ip=ui->serverip->text();
    mSocket=new QTcpSocket(this);
    QObject::connect(mSocket,&QTcpSocket::connected,this,&client::conn);
    QObject::connect(mSocket,&QIODevice::readyRead,this,&client::ReadData);
    mSocket->connectToHost(ip,225);
    if(mSocket->waitForConnected(1000))
        qDebug()<<"连接成功";
    else qDebug()<<"连接失败";
    speed=1000;
    Timer= new QTimer(this);
    //Timer->start(speed);
    QObject::connect(Timer,SIGNAL(timeout()),this,SLOT(timeout()));
    score1=0;
    score2=0;
    ui->score->setText("1号："+QString::number(score1)+"分 2号："+QString::number(score2)+"分");
}

client::~client()
{
    delete ui;
}

void client::conn()
{
    send(QString("00"));
}

void client::ReadData()
{
    QByteArray buffer;
    buffer=mSocket->readAll();
    mSocket->flush();
    QString str=QString(buffer).toUtf8();
    Dcode(str);
}

void client::send(QString str)
{
    mSocket->write(str.toUtf8());
    mSocket->flush();
}

void client::Dcode(QString str)
{
    qDebug()<<str;
    QString type=str.mid(0,2);
    if(type=="00") Timer->start(speed);
    if(type=="01")
    {
        int tmp=str.mid(2,1).toInt();
        switch(tmp)
        {
        case 1: player1.move(0,-1);  break;
        case 2: player1.move(0,1);   break;
        case 3: player1.move(-1,0);  break;
        case 4: player1.move(1,0);   break;
        }
    }
    if(type=="02")
    {
        int tmp=str.mid(2,str.length()-2).toInt();
        score1=tmp;
    }
    if(type=="03")
    {
        int x=str.mid(2,2).toInt();
        int y=str.mid(4,2).toInt();
        goodfood.setX(x);
        goodfood.setY(y);
    }
    if(type=="04")
    {
        int x=str.mid(2,2).toInt();
        int y=str.mid(4,2).toInt();
        badfood.setX(x);
        badfood.setY(y);
    }
    if(type=="05")
    {
        QMessageBox::about(this, "游戏结束", "游戏结束");
        exit(0);
    }
}

void client::paintEvent(QPaintEvent*)
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

void client::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:    player2.move(0,-1); send("011");  break;
        case Qt::Key_W:     player2.move(0,-1); send("011"); break;
        case Qt::Key_Down:  player2.move(0,1);  send("012"); break;
        case Qt::Key_S:     player2.move(0,1);  send("012");  break;
        case Qt::Key_Left:  player2.move(-1,0); send("013"); break;
        case Qt::Key_A:     player2.move(-1,0); send("013"); break;
        case Qt::Key_Right: player2.move(1,0);  send("014"); break;
        case Qt::Key_D:     player2.move(1,0);  send("014"); break;
    }
}


void client::timeout()
{
    player1.moveon();
    player2.moveon();
    if(player1.getHead().x()<0||player1.getHead().x()>=20||player1.getHead().y()<0||player1.getHead().y()>=25)
    {
        QMessageBox::about(this, "1号碰到了墙", "游戏结束");
        send("05");
        exit(0);
    }

    if(player2.getHead().x()<0||player2.getHead().x()>=20||player2.getHead().y()<0||player2.getHead().y()>=25)
    {
        QMessageBox::about(this, "2号碰到了墙", "游戏结束");
        send("05");
        exit(0);
    }

    if(player1.eatself()||player2.eatself())
    {
        QMessageBox::about(this, "吃到了自己", "游戏结束");
        send("05");
        exit(0);
    }

    if(crash())
    {
        QMessageBox::about(this, "相撞", "游戏结束");
        send("05");
        exit(0);
    }
    if(player1.getHead()==goodfood)
    {
        player1.eatplus();
        updategood();
        score1++;
    }

    if(player2.getHead()==goodfood)
    {
        player2.eatplus();
        updategood();
        score2++;
    }

    if(player1.getHead()==badfood)
    {
        player1.eatdev();
        updatebad();
        score1--;
    }

    if(player2.getHead()==badfood)
    {
        player2.eatdev();
        updatebad();
        score2--;
    }
    send("02"+QString::number(score2));
    ui->score->setText("1号："+QString::number(score1)+"分 2号："+QString::number(score2)+"分");
    this->update();
    repaint();
    Timer->start(speed);
    //qDebug()<<"yse"<<endl;
}

void client::updategood()
{
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

void client::updatebad()
{
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

bool client::crash()
{
    for(int i=0;i<player1.getlength();i++)
        if(player1.list[i]==player2.getHead()) return true;
    for(int i=0;i<player2.getlength();i++)
        if(player2.list[i]==player1.getHead()) return true;
    return false;
}
