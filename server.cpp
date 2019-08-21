#include "server.h"
#include "ui_server.h"

server::server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::server),player1(10,5),player2(17,10)
{
    ui->setupUi(this);
    QString localHostName = QHostInfo::localHostName();
    //qDebug() <<"localHostName: "<<localHostName;

    QHostInfo info = QHostInfo::fromName(localHostName);
    //qDebug() <<"IP Address: "<<info.addresses();

    foreach(QHostAddress address,info.addresses())
    {

         if(address.protocol() == QAbstractSocket::IPv4Protocol)
         {
             qDebug() << address.toString();
             ui->edip->setText(address.toString());
         }
    }


}

server::~server()
{
    delete ui;
}

void server::on_startbtn_clicked()
{
    mServer=new QTcpServer(this);
    connect(mServer, SIGNAL(newConnection()), this, SLOT(conn()));
    mServer->listen(QHostAddress::Any,225);
    this->setAttribute(Qt::WA_DeleteOnClose,1);

    speed=1000;
    Timer= new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(timeout()));

    srand(time(0));
    goodfood=QPoint(2,4);
    badfood=QPoint(4,5);
    repaint();
    //qDebug()<<"yes";
    score1=0;
    score2=0;
    ui->score->setText("1号："+QString::number(score1)+"分 2号："+QString::number(score2)+"分");
}

void server::conn()
{
    mSocket=mServer->nextPendingConnection();
    connect(mSocket,&QTcpSocket::readyRead,this,&server::ReadData);
    QMessageBox::about(this, "连接成功", "player2进入游戏");
}
void server::new_client()
{
    mSocket = mServer->nextPendingConnection();
    connect(mSocket, SIGNAL(readyRead()),this,SLOT(ReadData()));
}

void server::ReadData()
{
    QTcpSocket *obj = (QTcpSocket*)sender();
    QByteArray msg = obj->readAll();
    QString str=QString(msg).toUtf8();
    Dcode(str);
}

void server::Dcode(QString str)
{
    qDebug()<<str;
    QString type=str.mid(0,2);
    if(type=="00")
    {
        Timer->start(speed);
        send("00");
    }
    if(type=="01")
    {
        int tmp=str.mid(2,1).toInt();
        switch(tmp)
        {
        case 1: player2.move(0,-1);  break;
        case 2: player2.move(0,1);   break;
        case 3: player2.move(-1,0);  break;
        case 4: player2.move(1,0);   break;
        }
    }
    if(type=="02")
    {
        int tmp=str.mid(2,str.length()-2).toInt();
        score2=tmp;
        ui->score->setText("1号："+QString::number(score1)+"分 2号："+QString::number(score2)+"分");
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

void server::send(QString str)
{
    mSocket->write(str.toUtf8());
    mSocket->flush();
}

void server::paintEvent(QPaintEvent*)
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
        //qDebug()<<player1.list[i].x()<<","<<player1.list[i].y()<<endl;

    }

    for(int i = 0; i<player2.getlength(); i++)
    {
        paint.fillRect(QRect(player2.list[i].x()*15,player2.list[i].y()*15,15,15),Qt::blue);
        //qDebug()<<player2.list[i].x()<<","<<player2.list[i].y()<<endl;

    }

    //画好果子
    paint.fillRect(QRect(goodfood.x()*15,goodfood.y()*15,15,15),Qt::yellow);
    //画坏果子
    paint.fillRect(QRect(badfood.x()*15,badfood.y()*15,15,15),Qt::black);
}

void server::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:    player1.move(0,-1); send("011");  break;
    case Qt::Key_W:     player1.move(0,-1); send("011"); break;
    case Qt::Key_Down:  player1.move(0,1);  send("012"); break;
    case Qt::Key_S:     player1.move(0,1);  send("012");  break;
    case Qt::Key_Left:  player1.move(-1,0); send("013"); break;
    case Qt::Key_A:     player1.move(-1,0); send("013"); break;
    case Qt::Key_Right: player1.move(1,0);  send("014"); break;
    case Qt::Key_D:     player1.move(1,0);  send("014"); break;
    }
}


void server::timeout()
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

    ui->score->setText("1号："+QString::number(score1)+"分 2号："+QString::number(score2)+"分");
    this->update();
    repaint();
    Timer->start(speed);
    //qDebug()<<"yse"<<endl;
}

void server::updategood()
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
    QString tmp="03";
    if(goodfood.x()<10) tmp+="0"+QString::number(goodfood.x());
    else tmp+=QString::number(goodfood.x());
    if(goodfood.y()<10) tmp+="0"+QString::number(goodfood.y());
    else tmp+=QString::number(goodfood.y());
    send(tmp);
}

void server::updatebad()
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
    QString tmp;
    if(badfood.x()<10) tmp+="0"+QString::number(badfood.x());
    else tmp+=QString::number(badfood.x());
    if(badfood.y()<10) tmp+="0"+QString::number(badfood.y());
    else tmp+=QString::number(badfood.y());
    send(tmp);
}

bool server::crash()
{
    for(int i=0;i<player1.getlength();i++)
        if(player1.list[i]==player2.getHead()) return true;
    for(int i=0;i<player2.getlength();i++)
        if(player2.list[i]==player1.getHead()) return true;
    return false;
}
