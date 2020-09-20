#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QSize>
#include <QPainter>
#include <QPixmap>

#include "tower.h"
#include "selectbutton.h"
#include "selectbutton2.h"

class Tower;
class selectButton;
class selectButton2;

class TowerPosition
{
public:
    TowerPosition(QPoint pos,const QPixmap & sprite =QPixmap(":/images/open_spot.png"));

    //我把下面的set部分的函数全都改了，原来的代码时
    //void setHasTower(bool hasTower =true)
    //我改成了需要自己去赋值
    //我那个bug可能就是这里的问题
    //不过我也不知道为什么这样改一下就好了
    void setHasTower(bool hasTower);//从19行到38行，是对三种防御塔的一种判断，就英文的字面意思
    bool hasTower();

    void setHasTower1(bool hasTower1);
    bool hasTower1();

    void setHasTower2(bool hasTower2);
    bool hasTower2();

    void setHasTower3(bool hasTower3);
    bool hasTower3();

    void setHasButton(bool hasButton);
    bool hasButton();

    void setHasButton2(bool hasButton);
    bool hasButton2();

    void setHasUpdate1(bool hasUpdate1);
    bool hasUpdate1();

    void setHasUpdate2(bool hasUpdate2);
    bool hasUpdate2();

    QPoint centerPos()const ;
    QPoint getPos();

    int getWidth();
    int getHeight();

    Tower * get_tower();//得到私有成员tower
    selectButton * getButton();//得到私有成员button
    selectButton2 * getButton2();//得到私有盛有button2

    void setTower(Tower * tower);//设置私有成员tower
    void setButton(selectButton * button);//设置私有成员button
    void setButton2(selectButton2 * button);//设置私有成员button2

    void setRemoveTower();//移除防御塔

    bool containPoint(const QPoint pos)const;

    void draw(QPainter * painter)const;
    bool m_hasTower;


private:
    //57到64，也是对三种防御塔的判断
    bool m_hasTower1;
    bool m_hasTower2;
    bool m_hasTower3;
    bool m_hasButton;
    bool m_hasButton2;

    bool m_hasUpdate1;
    bool m_hasUpdtae2;

    Tower * m_tower;
    selectButton * m_button;
    selectButton2 * m_button2;
    QPoint m_pos;
    QPixmap m_sprite;
    static const QSize m_fixedSize;
};

#endif // TOWERPOSITION_H
