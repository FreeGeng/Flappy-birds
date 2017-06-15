#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QLCDNumber>
#include "fbnumlcd.h"

// 計分板, 用來顯示成績的類別
class ScoreBoard : public QWidget
{
    Q_OBJECT
public:
    ScoreBoard(QWidget *parent = 0);
    ~ScoreBoard();
    void setScore(int score,int top);	// 設定顯示的分數、最高分
protected:
    void paintEvent(QPaintEvent *);
private:
    int Score;		 //得分
    int top;		 //排行
    QString medal[3];	 //獎牌圖片的路徑
    FBNumLCD *scoreLcd;	 //得分的LCD
    FBNumLCD *topLcd;		//排行的LCD
};











#endif // SCOREBOARD_H
