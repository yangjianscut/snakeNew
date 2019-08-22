#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //this->resize(600,600);
    //this->setMaximumSize(1000,1000);
    //this->setWindowTitle("Snake");

    //startbtn = new QPushButton( "start" , this);
    //startbtn->setIconSize(QSize(20,20));
    //startbtn->move(450,100);

    //returnbtn = new QPushButton ( "return" , this);
    //returnbtn->setIconSize(QSize(20,20));
    //returnbtn->move(450,400);

    //连接单人
    connect(ui->singlegamebtn,SIGNAL(clicked()),this,SLOT(singleslot()));

    //连接双人
    connect(ui->doublegamebtn,SIGNAL(clicked()), this, SLOT(doubleslot()));

    //连接服务器端
    connect(ui->webgameclientbtn,SIGNAL(clicked()), this, SLOT(webclientslot()));

    //连接客户端
    connect(ui->webgameserverbtn,SIGNAL(clicked()), this, SLOT(webserverslot()));

    //连接结束按钮
    connect(ui->exitbtn,SIGNAL(clicked()), this, SLOT(exitslot()));
    //box->move(20,20);

}

//单人
void  MainWindow::singleslot()
{
    box= new gamebox();
    box->show();
}

//结束
void MainWindow::exitslot()
{
    if(QMessageBox::question(this, "exit", "exit?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
        {
            delete this;
            exit(0);
        }
}

//双人
void  MainWindow::doubleslot()
{
    doublebox= new doublegame;
    doublebox->show();
}

//客户端
void  MainWindow::webclientslot()
{
    mclient=new client;
    mclient->show();
}

//服务器端
void  MainWindow::webserverslot()
{
    mserver=new server;
    mserver->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete startbtn;
    //delete returnbtn;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    /*QPainter painter(this);
    painter.drawLine(80, 100, 650, 500);
    painter.setPen(Qt::red);
    painter.drawRect(10, 10, 100, 400);
    painter.setPen(QPen(Qt::green, 5));
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(50, 150, 400, 200);*/
}
