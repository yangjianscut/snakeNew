#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include "gamebox.h"
#include "doublegame.h"
#include "server.h"
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton* startbtn;
    QPushButton* returnbtn;
    gamebox* box;
    client* mclient;
    server* mserver;
    doublegame* doublebox;
public slots:
    void singleslot();
    void doubleslot();
    void exitslot();
    void webserverslot();
    void webclientslot();
    void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
