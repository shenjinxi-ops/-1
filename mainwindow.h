#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QString>

#include "towerposition.h"
#include "tower.h"
#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include "ui_mainwindow.h"
#include "selectbutton.h"
#include "selectbutton2.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class Bullet;
class Tower;
class Enemy;
class TowerPosition;
class selectButton;
class selectButton2;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadTowerPosition1();
    void addWayPoint1();

    void loadTowerPosition2();
    void addWayPoint2();

    void loadTowerPosition3();
    void addWayPoint3();



    bool canBuyTower1();
    bool canBuyTower2();
    bool canBuyTower3();

    bool canUpdate1();
    bool canUpdate2();


    void getHpDamage();
    void awardGlod();
    void drawHp(QPainter * painter)const;
    void drawGlod(QPainter * painter)const;
    void drawWaves(QPainter * painter)const;
    void doGameOver();
    void removeEnemy(Enemy * enemy);
    void removeBullet(Bullet * bullet);
    void removeButton(selectButton * button);
    void removeButton2(selectButton2 * button);
    void removeTower(Tower * tower);
    void addBullet(Bullet * bullet);

    QString getPath();
    void setPath(QString path);

    bool loadWaves();

    QList<Enemy *>  getEnemyList();

protected:
     void paintEvent(QPaintEvent *);
     void mousePressEvent(QMouseEvent *);

private slots:
     void updateMap();
     void gameStart();
private:
    Ui::mainwindow *ui;
    QList<TowerPosition > m_towerPositionList;
    QList<Tower *> m_towerList;
    QList<wayPoint*> m_wayPointList;
    QList<Enemy *> m_enemyList;
    QList<Bullet *>m_bulletList;
    QList<selectButton *> m_selectButtonList;
    QList<selectButton2 *> m_selectButton2List;

private:
    int m_waves;//当前的波数

    bool m_gameWin;
    bool m_gameEnd;

    int m_playerHp;
    int m_playerGlod;

    QString m_path;

};
#endif // MAINWINDOW_H
