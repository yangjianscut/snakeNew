#ifndef SNAKE_H
#define SNAKE_H
#include <QPoint>
#include <vector>
#include <QDebug>
class snake
{
public:
    //初始化函数
    snake()
    {
        head=QPoint(15,15);
        length=1;
        list[0]=head;
        direction=QPoint(-1,0);
    }

    //用坐标初始化
    snake(int x, int y)
    {
        head=QPoint(x,y);
        length=1;
        list[0]=head;
        direction=QPoint(-1,0);
    }

    //方向改变
    void move(int a, int b)
    {
        //若不是相反方向就改变方向
        if(a != -direction.x() || b != -direction.y())
            direction=QPoint(a,b);

    }

    //继续向前走
    void moveon()
    {
       for(int i=length-1;i;i--)
           list[i]=list[i-1];
        list[0]=list[0]+direction;
    }

    //吃到好果子，长度增加
    void eatplus()
    {
        length++;
        moveon();
    }

    //吃到坏果子，长度减小
    void eatdev()
    {
        if(length>1) length--; //若长度小于2就不减
        moveon();
    }

    //返回方向
    QPoint getDirection()
    {
        return direction;

    }

    //返回蛇头
    QPoint getHead()
    {

        head=list[0];
        return head;

    }

    //打印蛇的坐标
    void paint()
    {
        for(int i=0;i<length;i++)
        {
            qDebug()<<list[i].x()<<list[i].y()<<",";
        }

        //打印长度
        qDebug()<<"length:"<<length<<"direction"<<direction<<endl;

    }

    //返回蛇长
    int getlength()
    {
        return length;
    }

    //测试函数
    void test()
    {
        //测试移动
        moveon();
        paint();

        //测试改变方向
        move(1,0);
        paint();

        //测试吃了变长
        eatplus();
        paint();

        //测试吃了减小
        eatdev();
        paint();

        //综合测试
        eatplus();
        move(1,-1);
        moveon();moveon();
        paint();

    }

    //判断有没有吃到自己
    bool eatself()
    {
        for(int i=1;i<getlength();i++)
            if(list[i]==getHead())
                return true;

        return false;
    }

    //蛇长数组
    QPoint list[150];

private:
    QPoint direction; //蛇的方向
    QPoint head; //蛇头

    int length; //蛇长
};

#endif // SNAKE_H
