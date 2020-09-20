#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "enemy.h"
#include "tower.h"
#include "waypoint.h"
#include "utility"
#include "selectbutton.h"
#include "selectbutton2.h"
#include "startfrom.h"

#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>
#include <QPoint>
#include <QTimer>
#include <QString>

static const int tower1Cost=300;//第一种塔的价钱
static const int tower2Cost=400;//第二种
static const int tower3Cost=500;//第三种

static const int towerupdate1Cost=300;//塔第一次升级的价钱
static const int towerupdate2Cost=400;//第二次升级


MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent),
     ui(new Ui::mainwindow),
     m_waves(0),
     m_gameWin(false),
     m_gameEnd(false),
     m_playerHp(5),
     m_playerGlod(1000)
{
    this->setFixedSize(750,375);
    ui->setupUi(this);
    QTimer * timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMap()));
    timer->start(30);
    QTimer::singleShot(300,this,SLOT(gameStart()));
}

void MainWindow::gameStart()
{
    loadWaves();
}


void MainWindow::updateMap()
{
    foreach(Enemy * enemy,m_enemyList)
        enemy->move();
    foreach(Tower * tower,m_towerList)
        tower->checkEnemyInRange();
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(m_gameEnd || m_gameWin)
    {
        QString text=m_gameEnd ? "YOU LOST":"YOU WIN";
        QPainter painter(this);
        painter.setPen(Qt::red);
        painter.drawText(rect(),Qt::AlignCenter,text);
        return ;
    }
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),getPath());
    foreach(const TowerPosition & towerPos,m_towerPositionList)
    {
        if(!towerPos.m_hasTower)
        {
            towerPos.draw(&painter);//把hastower改成了公有成员，这样可以再类外使用，实现了有防御塔时防御塔坑的隐藏
        }
    }
    foreach(const Tower * tower,m_towerList)
        tower->draw(&painter);

    foreach(const wayPoint * waypoint,m_wayPointList)
        waypoint->draw(&painter);

    foreach(const Enemy * enemy,m_enemyList)
        enemy->draw(&painter);

    foreach(const Bullet * bullet,m_bulletList)
        bullet->draw(&painter);

    foreach(const selectButton * button,m_selectButtonList)
        button->draw(&painter);

    foreach(const selectButton2 * button2,m_selectButton2List)
        button2->draw(&painter);

    drawHp(&painter);
    drawGlod(&painter);
    drawWaves(&painter);
}

void MainWindow::loadTowerPosition1()//预先加载防御塔坑的位置
{
    QPoint pos[]=
    {
        QPoint(86,98),
        QPoint(226,98),
        QPoint(439,98),
        QPoint(105,215),
        QPoint(186,215),
        QPoint(314,215),
        QPoint(105,321),
        QPoint(223,323),
        QPoint(365,319)
    };
    int len=sizeof(pos)/sizeof(pos[0]);
    for(int i=0;i<len;i++)
    {
        m_towerPositionList.push_back(pos[i]);
    }
}

void MainWindow::addWayPoint1()
{
    wayPoint * waypoint1=new wayPoint(QPoint(79,6));
    m_wayPointList.push_back(waypoint1);

    wayPoint * waypoint2=new wayPoint(QPoint(79,55));
    waypoint1->setNextWayPoint(waypoint2);
    m_wayPointList.push_back(waypoint2);

    wayPoint * waypoint3=new wayPoint(QPoint(407,55));
    waypoint2->setNextWayPoint(waypoint3);
    m_wayPointList.push_back(waypoint3);

    wayPoint * waypoint4=new wayPoint(QPoint(407,175));
    waypoint3->setNextWayPoint(waypoint4);
    m_wayPointList.push_back(waypoint4);

    wayPoint * waypoint5=new wayPoint(QPoint(83,175));
    waypoint4->setNextWayPoint(waypoint5);
    m_wayPointList.push_back(waypoint5);

    wayPoint * waypoint6=new wayPoint(QPoint(83,292));
    waypoint5->setNextWayPoint(waypoint6);
    m_wayPointList.push_back(waypoint6);

    wayPoint * waypoint7=new wayPoint(QPoint(473,292));
    waypoint6->setNextWayPoint(waypoint7);
    m_wayPointList.push_back(waypoint7);
}

void MainWindow::loadTowerPosition2()
{
    QPoint pos[]=
    {
        QPoint(171,240),
        QPoint(251,240),
        QPoint(325,240),
        QPoint(270,170),
        QPoint(345,170),
        QPoint(420,170),
        QPoint(245,100),
        QPoint(520,170),
    };
    for(int i=0;i<8;i++)
    {
        m_towerPositionList.push_back(pos[i]);
    }
}

void MainWindow::addWayPoint2()
{
    wayPoint * waypoint1=new wayPoint(QPoint(177,371));
    m_wayPointList.push_back(waypoint1);

    wayPoint * waypoint2=new wayPoint(QPoint(177,292));
    waypoint1->setNextWayPoint(waypoint2);
    m_wayPointList.push_back(waypoint2);

    wayPoint * waypoint3=new wayPoint(QPoint(388,292));
    waypoint2->setNextWayPoint(waypoint3);
    m_wayPointList.push_back(waypoint3);

    wayPoint * waypoint4=new wayPoint(QPoint(388,222));
    waypoint3->setNextWayPoint(waypoint4);
    m_wayPointList.push_back(waypoint4);

    wayPoint * waypoint5=new wayPoint(QPoint(248,222));
    waypoint4->setNextWayPoint(waypoint5);
    m_wayPointList.push_back(waypoint5);

    wayPoint * waypoint6=new wayPoint(QPoint(248,151));
    waypoint5->setNextWayPoint(waypoint6);
    m_wayPointList.push_back(waypoint6);

    wayPoint * waypoint7=new wayPoint(QPoint(481,151));
    waypoint6->setNextWayPoint(waypoint7);
    m_wayPointList.push_back(waypoint7);

    wayPoint * waypoint8=new wayPoint(QPoint(481,223));
    waypoint7->setNextWayPoint(waypoint8);
    m_wayPointList.push_back(waypoint8);

    wayPoint * waypoint9=new wayPoint(QPoint(598,223));
    waypoint8->setNextWayPoint(waypoint9);
    m_wayPointList.push_back(waypoint9);

    wayPoint * waypoint10=new wayPoint(QPoint(598,149));
    waypoint9->setNextWayPoint(waypoint10);
    m_wayPointList.push_back(waypoint10);
}
void MainWindow::loadTowerPosition3()
{

}

void MainWindow::addWayPoint3()
{
    wayPoint * waypoint1=new wayPoint(QPoint(2,236));
    m_wayPointList.push_back(waypoint1);

    wayPoint * waypoint2=new wayPoint(QPoint(105,236));
    m_wayPointList.push_back(waypoint2);
    waypoint1->setNextWayPoint(waypoint2);

    wayPoint * waypoint3=new wayPoint(QPoint(105,360));
    m_wayPointList.push_back(waypoint3);
    waypoint2->setNextWayPoint(waypoint3);

    wayPoint * waypoint4=new wayPoint(QPoint(292,360));
    m_wayPointList.push_back(waypoint4);
    waypoint3->setNextWayPoint(waypoint4);

    wayPoint * waypoint5=new wayPoint(QPoint(292,142));
    m_wayPointList.push_back(waypoint5);
    waypoint4->setNextWayPoint(waypoint5);

    wayPoint * waypoint6=new wayPoint(QPoint(354,142));
    m_wayPointList.push_back(waypoint6);
    waypoint5->setNextWayPoint(waypoint6);

    wayPoint * endPoint=new wayPoint(QPoint(354,100));
    m_wayPointList.push_back(endPoint);
    waypoint6->setNextWayPoint(endPoint);


    wayPoint * waypoint7=new wayPoint(QPoint(720,236));
    m_wayPointList.push_back(waypoint7);

    wayPoint * waypoint8=new wayPoint(QPoint(610,236));
    m_wayPointList.push_back(waypoint8);
    waypoint7->setNextWayPoint(waypoint8);

    wayPoint * waypoint9=new wayPoint(QPoint(610,360));
    m_wayPointList.push_back(waypoint9);
    waypoint8->setNextWayPoint(waypoint9);

    wayPoint * waypoint10=new wayPoint(QPoint(420,360));
    m_wayPointList.push_back(waypoint10);
    waypoint9->setNextWayPoint(waypoint10);

    wayPoint * waypoint11=new wayPoint(QPoint(420,142));
    m_wayPointList.push_back(waypoint11);
    waypoint10->setNextWayPoint(waypoint11);

    waypoint11->setNextWayPoint(waypoint6);
}

bool MainWindow::canBuyTower1()
{
    if(m_playerGlod>=tower1Cost)
    {
        return true;
    }
    return false;
}

bool MainWindow::canBuyTower2()
{
    if(m_playerGlod>=tower2Cost)
    {
        return true;
    }
    return false;
}

bool MainWindow::canBuyTower3()
{
    if(m_playerGlod>=tower3Cost)
    {
        return true;
    }
    return false;
}

bool MainWindow::canUpdate1()
{
    if(m_playerGlod>=towerupdate1Cost)
    {
        return true;
    }
    return false;
}

bool MainWindow::canUpdate2()
{
    if(m_playerGlod>=towerupdate2Cost)
    {
        return true;
    }
    return false;
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{
    QPoint pressPos=event->pos();
    auto it=m_towerPositionList.begin();
    while(it!=m_towerPositionList.end())
    {
        if(Qt::LeftButton==event->button())//如果是鼠标左键点击
        {//左键点击的情况下，可以实现防御塔选择button的出现和防御塔的选择,或者是在有button2的情况下，进行升级或移除的操作
            if(it->containPoint(pressPos) && !it->hasButton() && !it->hasTower() && !it->hasButton2())//在没有按钮的情况下点击，会出现button1
            {
                QPoint tmp(it->getPos().x()-35,it->getPos().y()-35);//向左上角移动35 35，得到选择框的端点
                selectButton * button=new selectButton(tmp,this);//构造一个选择框
                m_selectButtonList.push_back(button);//类似防御塔的放置，把这个button放到MainWindow的一个list中
                it->setButton(button);//设置这个防御塔坑处的button
                it->setHasButton(true);//这个坑有了button
                update();//更新mainwindow，主要是更新paintevent
                break;
            }
            //下面的判断语句，要先判断hasbutton2，不能先判断containPos.因为如果没有button2，在进入这个判断框的时候，会先getbutton2，但是button2是NULL，程序会异常结束。
            else if(it->hasButton2() && it->getButton2()->containPos(pressPos) && !it->hasButton() && !it->containPoint(pressPos) &&it->hasTower())
            {//在有button2的情况下，点击button2的内部
                if(pressPos.y()<(it->getButton2()->getPos().y()+25))//我直接设置了第一个选择框的height是25，这里就直接用25了
                {//对防御塔进行升级
                    if(canUpdate1() && !it->hasUpdate1() && it->hasTower())
                    {
                        it->setHasUpdate1(true);
                        m_playerGlod-=towerupdate1Cost;
                        it->get_tower()->reSetDamage(it->get_tower()->getDamgae()+10);
                        it->get_tower()->levelChange();
                        //update();
                    }
                    else if(canUpdate2() && it->hasUpdate1() && !it->hasUpdate2())
                    {
                        it->setHasUpdate2(true);
                        m_playerGlod-=towerupdate2Cost;
                        it->get_tower()->reSetDamage(it->get_tower()->getDamgae()+20);
                        it->get_tower()->levelChange();
                        //update();
                    }
                }
                else if(pressPos.y()>it->getButton2()->getPos().y()+25)
                {//对防御塔进行移除
                    awardGlod();//移除防御塔奖励200
                    it->get_tower()->getRemoved();//这个移除和前面写的几个移除都是一样的
                    it->setRemoveTower();
                }
                //点击了button2的内部，button2就要被移除
                it->getButton2()->getRemoved();
                it->setButton2(NULL);
                it->setHasButton2(false);
                update();
                break;
            }
            else if(it->hasButton() && !it->hasTower() && it->getButton()->containPos(pressPos))//在有button的情况下，选择三种炮台.其实这里代码有点重复了。如果用继承的方法，那就应该不要这么多的重复代码
            {
                if(pressPos.x()<it->getButton()->getPos().x()+35)//鼠标点在选择框中的第一个防御塔内
                {
                    if(canBuyTower1())
                    {
                        it->setHasTower1(true);
                        m_playerGlod-=tower1Cost;
                        QString path=":/images/tower1.jpg";
                        Tower * tower=new Tower(it->centerPos(),this,path,10);//四个参数，分别是防御塔的中心点；主界面；防御塔图片路径；防御塔的攻击力。其实这里还可以有很多的发挥，比如防御塔的攻击速度也放在构造函数的参数中
                        it->setTower(tower);
                        m_towerList.push_back(tower);
                        update();
                        //这里不要先break跳出while循环，详情见后面
                    }
                }
                else if(pressPos.x()>it->getButton()->getPos().x()+35 && pressPos.x()<it->getButton()->getPos().x()+70)//鼠标点在第二个防御塔的图片中
                {
                    if(canBuyTower2())
                    {
                        it->setHasTower2(true);
                        m_playerGlod-=tower2Cost;
                        QString path=":/images/tower2.png";
                        Tower * tower=new Tower(it->centerPos(),this,path,15);
                        it->setTower(tower);
                        m_towerList.push_back(tower);
                        update();
                    }
                }
                else if(pressPos.x()>it->getButton()->getPos().x()+70 && pressPos.x()<it->getButton()->getPos().x()+105)//第三个图片
                {
                    if(canBuyTower3())
                    {
                        it->setHasTower3(true);
                        m_playerGlod-=tower3Cost;
                        QString path=":/images/tower3.png";
                        Tower * tower=new Tower(it->centerPos(),this,path,20);
                        it->setTower(tower);
                        m_towerList.push_back(tower);
                        update();
                    }
                }
                //不能跳出循环是因为要执行下面的代码
                //下面的代码是对button的一个删除
                it->getButton()->getRemoved();
                it->setButton(NULL);
                it->setHasButton(false);
                update();
                break;
            }
        }
        else if(Qt::RightButton==event->button())//如果是鼠标右键点击
        {//在有防御塔的情况下，右键会出现选择框，升级还有移除
            if(it->containPoint(pressPos) && (!it->hasButton2()) && it->hasTower())
            {
                it->setHasButton2(true);
                QPoint tmp(it->getPos().x()+35,it->getPos().y());//我是把防御塔坑的右上顶点当作button2的端点
                selectButton2 * button2=new selectButton2(tmp,this,100,50);
                button2->setTower(it->get_tower());//我写这个setTower()的目的是得到防御塔的等级，不同等级的updatecost不一样，具体的你可以看button2的draw方法
                m_selectButton2List.push_back(button2);
                it->setButton2(button2);
                update();
                break;
            }
        }
        ++it;
    }
}

void MainWindow::setPath(QString path)
{
    m_path=path;
}

QString MainWindow::getPath()
{
    return m_path;
}

void MainWindow::getHpDamage()
{
    m_playerHp-=1;
    if(m_playerHp<=0)
    {
        doGameOver();
    }
}

void MainWindow::doGameOver()
{
    if(!m_gameEnd)
    {
        m_gameEnd=true;
    }
}

void MainWindow::removeTower(Tower * tower)
{
    Q_ASSERT(tower);
    m_towerList.removeOne(tower);
    delete tower;
}

void MainWindow::removeEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);
    m_enemyList.removeOne(enemy);
    delete enemy;
    if(m_enemyList.empty())
    {
        ++m_waves;
        if(!loadWaves())
        {
            m_gameWin=true;
        }
    }
}

void MainWindow::removeButton(selectButton *button)//仿造enemy的移除
{
    Q_ASSERT(button);
    m_selectButtonList.removeOne(button);
    delete button;
}

void MainWindow::removeButton2(selectButton2 *button)
{
    Q_ASSERT(button);
    m_selectButton2List.removeOne(button);
    delete button;
}

bool MainWindow::loadWaves()
{
    if(m_waves>=6)
    {
        return false;
    }

    int enemyStartInterval[]={100,500,600,1000,3000,6000};
    for(int i=0;i<6;++i)
    {
        wayPoint * startWayPoint;
        if(getPath()==":/images/background4.jpg")
        {
            int a=rand()%100;
            if(a<50)
            {
                startWayPoint=m_wayPointList.first();
            }
            if(a>=50)
            {
               startWayPoint=m_wayPointList[7];
            }
        }
        else
        {
            startWayPoint=m_wayPointList.first();
        }
        Enemy * enemy=new Enemy(startWayPoint,this);
        m_enemyList.push_back(enemy);
        enemy->reSetHp(40+20*(0+m_waves));//波数增加，怪物的血量增加，一次加20点
        QTimer::singleShot(enemyStartInterval[i],enemy,SLOT(doActive()));
    }
    return true;
}

QList<Enemy *> MainWindow::getEnemyList()
{
    return m_enemyList;
}

void MainWindow::removeBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.removeOne(bullet);
    delete bullet;
}

void MainWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.push_back(bullet);
}

void MainWindow::awardGlod()
{
    m_playerGlod+=200;
    update();
}

void MainWindow::drawWaves(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(500,5,100,25),QString("WAVES: %1").arg(m_waves+1));
    painter->restore();
}

void MainWindow::drawHp(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(30,5,100,25),QString("HP: %1").arg(m_playerHp));
    painter->restore();
}

void MainWindow::drawGlod(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(300,5,100,25),QString("GLOD: %1").arg(m_playerGlod));
}
