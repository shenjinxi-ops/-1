#include "startfrom.h"
#include "ui_startfrom.h"
#include "mainwindow.h"

class MainWindow;


StartFrom::StartFrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartFrom)
{
    ui->setupUi(this);
    setWindowTitle("start from");
    //打开第一关
    connect(ui->pushButton,&QPushButton::clicked,[=]()
    {
        MainWindow * mainwindow=new MainWindow(parent);
        mainwindow->setPath(":/images/background1.jpg");
        mainwindow->loadTowerPosition1();
        mainwindow->addWayPoint1();
        mainwindow->show();
    });
    //打开第二关
    connect(ui->pushButton_2,&QPushButton::clicked,[=]()
    {
        MainWindow * mainwindow=new MainWindow(parent);
        mainwindow->setPath(":/images/background2.jpg");
        mainwindow->loadTowerPosition2();
        mainwindow->addWayPoint2();
        mainwindow->show();
    });
    //打开第三关
    connect(ui->pushButton_3,&QPushButton::clicked,[=]()
    {
        MainWindow * mainwindow=new MainWindow(parent);
        mainwindow->setPath(":/images/background4.jpg");
        mainwindow->loadTowerPosition3();
        mainwindow->addWayPoint3();
        mainwindow->show();
    });
}

void StartFrom::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QString path(":/images/background.jpg");
    painter.drawPixmap(0,0,750,375,path);
}

StartFrom::~StartFrom()
{
    delete ui;
}
