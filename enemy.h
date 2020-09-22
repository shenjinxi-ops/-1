#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QSize>

#include "waypoint.h"
#include "mainwindow.h"
#include "tower.h"



class MainWindow;
class Tower;
class QPainter;
class wayPoint;

class Enemy:public QObject
{
    Q_OBJECT
public:
    Enemy(wayPoint * start,MainWindow * game,const QPixmap & sprite=QPixmap(":/images/monster1.png"));
    ~Enemy();
    void draw(QPainter * painter) const;
    void move();     //敌人移动

    QPoint get_pos();    //得到敌人当前位置

    void getAttack(Tower * tower);      //被tower攻击
    void getDamage(int damage);         //敌人被攻击受到伤害
    void getRemoved();                  //当敌人血量小于零时，敌人死亡、移除
    void getLostSight(Tower * tower);   //敌人脱离tower的攻击范围
    void reSetHp(int maxHp);            //判断当前血量

private slots:
    void doActive();                    //私有信号槽，判断敌人是否可以移动
private:
    int m_maxHp;                        //最大血量
    int m_currentHp;                    //当前血量
    int m_walkingSpeed;                 //移动速度
    bool m_active;                      //是否可以移动

    wayPoint * m_destinationWayPoint;
    MainWindow * m_game;
    QPoint m_pos;
    QPixmap m_sprite;
    QList<Tower *> m_attackTowerList;

    static const QSize m_fixedSize;

};

#endif // ENEMY_H
