#include "startfrom.h"
#include "ui_startfrom.h"
#include "mainwindow.h"

class MainWindow;


StartFrom::StartFrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartFrom)
{
    ui->setupUi(this);
    this->resize(1500,750);    //设置窗口大小
    setWindowTitle("start from");
    //打开第一关
    connect(ui->pushButton,&QPushButton::clicked,[=]()
    {
        MainWindow * mainwindow=new MainWindow(parent);
        mainwindow->setPath(":/images/background12.jpg");
        mainwindow->loadTowerPosition1();
        mainwindow->addWayPoint1();
        mainwindow->show();
    });
    //打开第二关
    connect(ui->pushButton_2,&QPushButton::clicked,[=]()
    {
        MainWindow * mainwindow=new MainWindow(parent);
        mainwindow->setPath(":/images/background11.jpg");
        mainwindow->loadTowerPosition2();
        mainwindow->addWayPoint2();
        mainwindow->show();
    });
}

void StartFrom::paintEvent(QPaintEvent *)  //设置背景图片
{
    QPainter painter(this);
    QString path(":/images/background.jpg");
    painter.drawPixmap(0,0,1500,750,path);
}

StartFrom::~StartFrom()
{
    delete ui;
}
