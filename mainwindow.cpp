#include "mainwindow.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <ctime>
#include <iostream>
#include <QTime>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    //初始化整個遊戲介面與Timer

    this->setFixedSize(380,500);	//設定視窗的大小为380x500
    this->setWindowIcon(QIcon(":/Images/bird1.png"));
    this->move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2);
    //上面一行可以讓視窗在螢幕中間顯示，需要include QDesktopWidget
    for(int i=0;i<pipeCount;i++)	//新增水管
        pipe[i]=new Pipe(this);

    createPipe(); //初始化水管參數
    pipeTimer =new QTimer(this);	//新增水管的Timer 以下的三個connect說明了一次處理三個動作
    connect(pipeTimer,SIGNAL(timeout()),this,SLOT(pipeAction()));
    connect(pipeTimer,SIGNAL(timeout()),this,SLOT(collisDete()));
    connect(pipeTimer,SIGNAL(timeout()),this,SLOT(scoreDete()));
    pipeTValue=8;  // pipeTimer interval

    birds=new Bird(this);
    birds->move(60,250);
    // 設定飛行速度值
    this->fpV[0]=-3;
    this->fpV[1]=-4;
    this->fpV[2]=-3;
    this->fpV[3]=-2;
    this->fpV[4]=-1;
    this->fpV[5]=-1;
    this->fpV[6]=-1;
    this->fpV[7]=0;
    this->fpV[8]=1;
    this->fpV[9]=1;
    this->fpV[10]=2;
    this->fpV[11]=2;
    this->fpV[12]=2;
    this->fpV[13]=3;
    this->fpV[14]=3;

    this->fpp=0;


    birdTimer=new QTimer(this);
    connect(birdTimer,SIGNAL(timeout()),this,SLOT(birdAction()));

    birdV=0;
    gamemod=redy;		//遊戲狀態初始化為 redy

    score=0;
    top=0;
    loadTop();		//載入得分紀錄

    scoreLCD=new FBNumLCD(this);	//新增計分板
    scoreLCD->setShowHead(false);	//不顯示多餘的位數
    scoreLCD->setValue(0);          //初始化分數顯示為0
    scoreLCD->move(140,-100);

    scoreBoard=new ScoreBoard(this);
    scoreBoard->move(-350,100);
    scobTimer=new QTimer(this);
    connect(scobTimer,SIGNAL(timeout()),this,SLOT(scbAction()));


    thisGround=new Ground(this);
    thisGround->move(0,450);

    myredyBoard=new RedyBoard(this);
    myredyBoard->setFixedSize(380,500);
    myredyBoard->move(0,0);

    replay=new QLabel(this);		//replay按鈕, 實際上它不是一個button, 而是用label來實作
    QPixmap pix;
    pix.load(":/Images/replay.png");		//應用程式所需要的圖片資源都在.qrc file裡面, 使用file裡面的資源使用 ":"即可
    replay->setPixmap(pix);
    replay->setFixedSize(140,80);
    replay->move(120,-400);

    //sound
    playList=new QMediaPlaylist;
    QFileInfo info;
    info.setFile("sounds/sfx_wing.mp3");
    playList->addMedia(QUrl::fromLocalFile(info.absoluteFilePath()));
    info.setFile("sounds/sfx_point.mp3");
    playList->addMedia(QUrl::fromLocalFile(info.absoluteFilePath()));
    info.setFile("sounds/sfx_die.mp3");
    playList->addMedia(QUrl::fromLocalFile(info.absoluteFilePath()));
    info.setFile("sounds/sfx_hit.mp3");
    playList->addMedia(QUrl::fromLocalFile(info.absoluteFilePath()));
    info.setFile("sounds/sfx_swooshing.mp3");
    playList->addMedia(QUrl::fromLocalFile(info.absoluteFilePath()));

    playList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    playList_wing=new QMediaPlaylist;
    info.setFile("sounds/sfx_wing.mp3");
    playList_wing->addMedia(QUrl::fromLocalFile(info.absoluteFilePath()));
    playList_wing->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    playList_wing->setCurrentIndex(1);

    media=new QMediaPlayer;
    media->setVolume(100);
    media->setPlaylist(playList_wing);
    media2=new QMediaPlayer;
    media2->setPlaylist(playList);
    media2->setVolume(100);

    isHit=0;
    isFlag=-1;
    this->setWindowTitle("Qt FlappyBird");		//設定視窗標題
}
void MainWindow::stupid(){
    for(int i=0;i<1000000;i++){
        qDebug("test");
    }
}

void MainWindow::createPipe()		//初始化管道。使其以一定次序排在地圖之外
{
    stupid();
    int startx=500+380;		//第一个管道的位置
    pipeXgap=200;		//間距
    int pipR;			//產生一個垂直位置的隨機數字
    qsrand(time(NULL));

    for(int i=0;i<pipeCount;i++)
    {
        pipR=qrand()%200; //qrand是Qt用來產生隨機數字

        pipe[i]->move(startx+i*pipeXgap,-200+pipR);
        lastPipe=i;		//很重要 記錄最後一根水管的編號 為之後水管的循環奠定基礎
    }
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *)		//繪圖事件, 用来產生背景
{
    /*QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/Images/bg.png");
    painter.drawPixmap(0,0,380,450,pixmap);*/
}

void MainWindow::mousePressEvent(QMouseEvent *event)	//滑鼠事件
{
    //左右鍵都能控制鳥的行動 為了防止鳥飛出第圖 增加了 birds->pos().y()>0 的判斷
    if((event->button()==Qt::LeftButton||event->button()==Qt::RightButton)&&birds->pos().y()>0)
    {
        qDebug("test");
        if(gamemod==stop)
        {
            if(isScobOk)   //遊戲已經失敗並且計分牌動畫跑完才會跑以下程式
                if((event->pos().x()>=120&&event->pos().x()<=260)&&(event->pos().y()>=400&&event->pos().y()<=480))
                {
                    // 點到replay的範圍內才會觸發重新開始
                    gameRedy();
                    playSound(s_sw);
                }

        }
        else
        {
            mainAction();
        }

    }
}



void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //可利用空白鍵或是向上方向鍵控制鳥飛行, 或是ALT重新開始遊戲
    if((event->key()==Qt::Key_Space||event->key()==Qt::Key_Up)&&birds->pos().y()>0)
    {
        mainAction();
        playWingSound();
    }
    if(isScobOk && gamemod==stop){
        if(event->key()==Qt::Key_Alt){
            gameRedy();
            playSound(s_sw);
        }
    }
}

void MainWindow::mainAction()
{
    // 主要的處理事件
    if(gamemod==redy)	//如果是redy則開始遊戲，鳥與水管開始移動
    {
        gameStart();
        timedata=8;
        birdTimer->start(timedata);
        pipeTimer->start(pipeTValue);
        fpp=0.0;
        birdV=fpV[int(fpp)];		//每次觸發 鳥都會向上飛 因此一開始的速度是負數。
        emit birds->fly();	//此信號用來觸發抬頭
    }
    else if(gamemod==start)	//如果遊戲已經開始，只處理鸟的飛行
    {
        fpp=0.0;
        birdV=fpV[int(fpp)];
        emit birds->fly();
    }
    playWingSound();
}

void MainWindow::birdAction()
{
    //這邊是設定鳥飛行速度與操作難易度的地方
    birds->move(birds->pos().x(),birds->pos().y()+birdV);

    if(fpp<14.0)
        fpp+=0.2;
    else
        fpp=14.0;
    birdV=fpV[int(fpp)];

    if(birds->pos().y()+birds->height()>=450)
    {
        birds->move(birds->pos().x(),450-birds->height()+5);
        birdTimer->stop();
        isHit=true;
        playSound(s_hit);
        gameLose();
        birds->setRale(90);
    }

}

void MainWindow::pipeAction()
{
    //水管的動畫，重點是水管離開地圖之後將會重新回到最右邊並接在lastPipe的後面，並產生一个新的高度
    int pipR;
    for(int i=0;i<pipeCount;i++)
    {
        pipe[i]->move(pipe[i]->pos().x()-1,pipe[i]->pos().y());  //每個timer往左移動一格
        if(pipe[i]->pos().x()<-100)   // 判斷管子已經消失, 準備移動到最右邊
        {
            pipR=qrand()%200; //隨機產生水管的Y座標
            pipe[i]->move(pipe[lastPipe]->pos().x()+pipeXgap,-200+pipR);
            lastPipe=i;
        }
    }
}

void MainWindow::collisDete()
{
    // 判斷鳥是否撞到管子
    int birdRx=birds->pos().x()+30;
    int birdDy=birds->pos().y()+30;
    for(int i=0;i<pipeCount;i++)
    {
        if(birdRx>=pipe[i]->x()&&birds->pos().x()<=pipe[i]->pos().x()+pipe[i]->width()-10)
        {
            if(birds->y() <= (pipe[i]->y()+pipe[i]->getH1()) || birdDy >= (pipe[i]->y()+pipe[i]->getH1()+pipe[i]->getGap()))
                gameLose();
        }
    }
}

void MainWindow::scoreDete()
{
    // 偵測分數, 通過一個水管加一分
    for(int i=0;i<pipeCount;i++)
    {
        if(birds->pos().x()+birds->width()>=pipe[i]->pos().x()+35 && birds->pos().x()+birds->width()<=pipe[i]->pos().x()+40 && cx)
        {
            playSound(s_point);
            this->score+=1;
            scoreLCD->setValue(score);

            if(score>=1000)
            {
                scoreLCD->move(90+14*3,50);
            }
            else if(score>=100)
            {
                scoreLCD->move(90+14*2,50);
            }
            else if(score>=10)
            {
                scoreLCD->move(90+14,50);
            }
            cx=0;
        }
        if(birds->pos().x()>=pipe[i]->pos().x()+68 && birds->pos().x()<=pipe[i]->pos().x()+73){
            cx=1;
        }
    }
}


void MainWindow::scbAction()
{
    //失敗時計分牌的動畫
    scoreBoard->move(scoreBoard->pos().x()+1,scoreBoard->pos().y());
    if(scoreBoard->pos().x()>=40)
    {
        scoreBoard->move(40,scoreBoard->pos().y());
        scobTimer->stop();
        replay->move(120,400);
        isScobOk=1;
    }
}

void MainWindow::gameRedy()
{

    //遊戲準備開始, 初始化好一些參數
    myredyBoard->show();
    scoreBoard->move(-350,100);
    birds->move(60,250);
    replay->move(120,-400);
    createPipe();
    birds->setRale(-50);
    gamemod=redy;
    scoreLCD->setValue(0);
    thisGround->play();
    birds->play();
}

void MainWindow::gameLose()
{
    //遊戲失敗時的處理：首先出現計分牌, 遊戲狀態更改為stop, 地板停止移動, timer停止計時, 計算得分
    isScobOk=0;
    gamemod=stop;
    birds->stop();
    pipeTimer->stop();
    thisGround->stop();
    if(!isHit)
    {
        playSound(s_die);
    }
    else
        isHit=false;

    if(score>top)	//如果此次得分高於最高分, 則更新紀錄
    {
        top=score;
        saveTop();
    }
    scoreBoard->setScore(score,top);
    scobTimer->start(3);
    scoreLCD->move(140,-100);

}

void MainWindow::gameStart()
{
    //開始遊戲進行的動作
    gamemod=start;
    myredyBoard->close();
    cx=1;
    score=0;
    scoreLCD->move(90,50);

}

void MainWindow::saveTop()
{
    //儲存最高分紀錄, 使用二進位來存, 存在top.d file裡
    QFile file("top.d");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out<<this->top;
}

void MainWindow::loadTop()
{
    //讀取記錄
    QFile file("top.d");
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        in>>this->top;
    }
    else
        top=0;
}

void MainWindow::playWingSound()
{
    //播放飛行時的音效
    media->stop();

    media->play();
}

void MainWindow::playSound(int flag)
{
    //播放其他音效, 根據傳入的flag值決定撥放哪一個
    if(isFlag!=flag)
    {
        playList->setCurrentIndex(flag);
    }
    media2->play();
}
