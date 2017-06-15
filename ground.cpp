#include "ground.h"

Ground::Ground(QWidget *parent)
    : QWidget(parent)
{
    this->setMaximumSize(380,600);
    this->setMinimumSize(380,600);
    sx=0;sy=0;

    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(groundM()));
    timer->start(8);
}

Ground::~Ground()
{

}

void Ground::groundM()
{
    sx=sx-1;//一直向左滾動
    if(sx<=-38)
    {
        sx=0;
    }
    update();
}

void Ground::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/Images/ground.png");
    painter.drawPixmap(sx,sy,450,60,pixmap);
}

void Ground::play()
{
    timer->start(8);
}

void Ground::stop()
{
    timer->stop();
}
