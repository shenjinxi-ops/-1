#ifndef STARTFROM_H
#define STARTFROM_H

#include <QWidget>
#include <mainwindow.h>


namespace Ui {
class StartFrom;
}

class StartFrom : public QWidget
{
    Q_OBJECT

public:
    explicit StartFrom(QWidget *parent = nullptr);
    ~StartFrom();
    void paintEvent(QPaintEvent *);

private:
    Ui::StartFrom *ui;
};

#endif // STARTFROM_H
