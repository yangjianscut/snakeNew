#ifndef SNAKE_H
#define SNAKE_H
#include <QPoint>
#include <vector>
#include <QDebug>
class snake
{
public:
    snake()
    {
        head=QPoint(15,15);
        length=1;
        list[0]=head;
        direction=QPoint(-1,0);
    }

    snake(int x, int y)
    {
        head=QPoint(x,y);
        length=1;
        list[0]=head;
        direction=QPoint(-1,0);
    }

    void move(int a, int b)
    {
        if(a != -direction.x() || b != -direction.y())
            direction=QPoint(a,b);

    } //方向变动

    void moveon()
    {
       for(int i=length-1;i;i--)
           list[i]=list[i-1];
        list[0]=list[0]+direction;
    }    //按方向

    void eatplus()
    {
        length++;
        moveon();
    }

    void eatdev()
    {
        if(length>1) length--;
        moveon();
    }

    QPoint getDirection()
    {
        return direction;

    }

    QPoint getHead()
    {
        head=list[0];
        return head;
    }

    void paint()
    {
        for(int i=0;i<length;i++)
        {
            qDebug()<<list[i].x()<<list[i].y()<<",";
        }
        qDebug()<<"length:"<<length<<"direction"<<direction<<endl;

    }

    int getlength()
    {
        return length;
    }

    void test()
    {
        moveon();
        paint();
        move(1,0);
        paint();
        eatplus();
        paint();
        eatdev();
        paint();
        eatplus();
        move(1,-1);
        moveon();moveon();
        paint();
    }

    bool eatself()
    {
        for(int i=1;i<getlength();i++)
            if(list[i]==getHead()) return true;
        return false;
    }

    QPoint list[150];
private:
    QPoint direction;
    QPoint head;

    int length;
};

#endif // SNAKE_H
