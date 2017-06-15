#ifndef FBNUMLCD_H
#define FBNUMLCD_H

#include <QWidget>
#include <QtGui>
#include <QPainter>
#include <QPixmap>

// 用來顯示分數數字的類別
class FBNumLCD : public QWidget
{
    Q_OBJECT

public:
    FBNumLCD(QWidget *parent = 0);
    ~FBNumLCD();
    void setValue(int v);	// 設定值
    int value() const;		// 讀取值
    void setShowHead(bool s);	// 是否顯示多餘的數字
protected:
    void paintEvent(QPaintEvent *);
private:
    void runtime();		//更新得分
private:
    QString lcdList[11]; //儲存圖片路徑
    int data;
    enum{MaxSize=4}; // define constant value
    int num[MaxSize]; // the score when you play
    int len;
    bool showHead;
};

#endif // FBNUMLCD_H




