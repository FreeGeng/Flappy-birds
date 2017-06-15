#ifndef BIRD_H
#define BIRD_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <math.h>

// Bird 類別
class Bird : public QWidget
{
    Q_OBJECT

public:
    Bird(QWidget *parent = 0); // no parent
    ~Bird();
    void setRale(int rale);	// 設定旋轉角度
    void play(); //啟動timer
    void stop(); //停止timer
signals:
    void fly();		//觸發抬頭的訊號
private slots:
    void updateRale();		//更新旋轉角度
protected:
    void paintEvent(QPaintEvent *);		//繪圖事件
private:
    double rale;		//角度參數
    double x;			//旋轉角度的單位偏移
    int zt;		// 一個30度夾角的flag, 用來替鳥旋轉提供更好的狀態處理
    double ztr;  //目前角度
    int co;		 //鳥的動作由三張圖片組成, 這是序號
    QTimer *timer;
    QString src[3];	// 圖片的路徑
};

#endif // BIRD_H
