#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>

#include <QTimer>
#include <QDataStream>
#include <QLabel>
#include <QPainter>
#include <QPixmap>

#include "bird.h"
#include "ground.h"
#include "pipe.h"
#include "scoreboard.h"
#include "fbnumlcd.h"
#include "redyboard.h"

#include <QtGui>
#include <QMouseEvent>
#include "math.h"

#include <QDataStream>
#include <QFile>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia>
#include <QUrl>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);    //繪製背景圖
    void mousePressEvent(QMouseEvent *event);	//滑鼠點下事件
    void keyPressEvent(QKeyEvent *event);	//鍵盤事件

private slots:				
    void birdAction();			//鳥的動作
    void pipeAction();			//綠色管子的動作
    void collisDete();			//碰撞偵測
    void scoreDete();			//計分偵測
    void scbAction();			//計分板動畫
    void playWingSound();       //播放飛行時音效
    void playSound(int flag);   //播放其他音效

private:
    void mainAction();			// 主要的觸發事件, 點下滑鼠或是空白或是上鍵時觸發
    void createPipe();			// 產生水管
    void gameLose();			 //遊戲結束
    void gameStart();			 //遊戲開始
    void gameRedy();         //遊戲預備
    void saveTop();			 //儲存最高分
    void loadTop();			 //讀取最高分
    void stupid();
private:	
    Bird *birds;
    double birdV;			// 鳥的速度
    double timedata;			// birdTimer interval
    QTimer *birdTimer;			// bird's timer
    double fpV[15];  // 飛行速度
    double fpp;

    enum{stop=0,start=1,redy=2};
    int gamemod;		// game state

    RedyBoard *myredyBoard;

    enum{pipeCount=5};		// # pipe
    Pipe *pipe[pipeCount];
    QTimer *pipeTimer;
    int pipeTValue;     // pipeTimer interval
    int pipeXgap;		// 管子間距
    int lastPipe;		// the flag of rightest pipe

    Ground *thisGround;

    ScoreBoard *scoreBoard;
    bool isScobOk;		// 計分板的顯示狀態
    int score;			//分數
    int top;			//最高紀錄
    bool cx;			//用來避免重複計分的flag
    QTimer *scobTimer;		// 處理計分板, 當遊戲結束時觸發
    FBNumLCD *scoreLCD;		//小記分牌
    QLabel *replay;		// replay按鈕

    QMediaPlayer *media;
    QMediaPlayer *media2;
    enum{s_wing=0,s_point=1,s_die=2,s_hit=3,s_sw=4};  
    QMediaPlaylist *playList;
    QMediaPlaylist *playList_wing;
    int isFlag; //播放陣列裡哪一個音效
    bool isHit; //用來標誌是否撞到地面
};

#endif // MAINWINDOW_H
