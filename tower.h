//类外
#include <QTimer>
#include "enemy.h"
class Enemy;
class QTimer;

//类内
public:
    void attackEnemy();//攻击敌人
    void targetKilled();//当目标被击杀后
    void chooseEnemyFromAttack(Enemy * enemy);//从可以攻击的敌人中，选出攻击的敌人

    void removeBullet();//移除防御塔产生的子弹
    void lostSightOfEnemy();//丢失攻击目标的视野
    void checkEnemyInRange();//检查敌人是否在攻击范围内
    Enemy * getAttackedEnemy();//得到正在攻击的敌人

private slots:
    void shootWeapon();//私有信号槽，实现和子弹类的连接

private:
    bool m_attacking;//是否在攻击
    int m_damage;//防御塔的攻击力
    int m_fireRate;//射速
    Enemy * m_chooseEnemy;//正在攻击的敌人
    QTimer * m_fireRateTime;
