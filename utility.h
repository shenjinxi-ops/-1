#ifndef UTILITY_H
#define UTILITY_H

#endif // UTILITY_H
#include <QPoint>
#include <cmath>

//判断两个点是否相撞（判断是否在射程之内）
inline bool collisionWithCircle(QPoint p1,int r1,QPoint p2,int r2)
{
    int xx=p1.x()-p2.x();
    int yy=p1.y()-p2.y();
    int dis=sqrt(xx*xx+yy*yy);
    if(dis<r1+r2)
    {
        return true;
    }
    return false;
}
