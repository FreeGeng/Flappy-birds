#include "redyboard.h"

RedyBoard::RedyBoard(QWidget *parent)
    : QWidget(parent)
{
    this->setGeometry(0,0,380,500);
    label=new QLabel(tr("<font color=red>控制：滑鼠左右鍵 or 空白鍵 or 方向上鍵</font>"),this);
    label->move(80,480);
    versionLabel=new QLabel(tr("Version:1.1.1"),this);
    versionLabel->move(145,320);
}

RedyBoard::~RedyBoard()
{

}

void RedyBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    painter.setWindow(0,0,380,500);
    pix.load(":/Images/ready.png");
    painter.drawPixmap(0,0,380,500,pix);
}
