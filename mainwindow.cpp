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

    connect(ui->singlegamebtn,SIGNAL(clicked()),this,SLOT(singleslot()));
    connect(ui->doublegamebtn,SIGNAL(clicked()), this, SLOT(doubleslot()));
    connect(ui->webgameclientbtn,SIGNAL(clicked()), this, SLOT(webclientslot()));
    connect(ui->webgameserverbtn,SIGNAL(clicked()), this, SLOT(webserverslot()));
    connect(ui->exitbtn,SIGNAL(clicked()), this, SLOT(exitslot()));
    //box->move(20,20);

}

void  MainWindow::singleslot()
{
    box= new gamebox();
    box->show();
}

void MainWindow::exitslot()
{
    if(QMessageBox::question(this, "exit", "exit?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
        {
            delete this;
            exit(0);
        }
}

void  MainWindow::doubleslot()
{
    doublebox= new doublegame;
    doublebox->show();
}

void  MainWindow::webclientslot()
{
    mclient=new client;
    mclient->show();
}

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
