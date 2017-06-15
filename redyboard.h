#ifndef REDYBOARD_H
#define REDYBOARD_H

#include <QWidget>
#include <QtGui>
#include <QPainter>
#include <QPixmap>
#include <QLabel>

// 準備狀態的公布欄的類別
class RedyBoard : public QWidget
{
    Q_OBJECT
public:
    RedyBoard(QWidget *parent = 0);
    ~RedyBoard();
protected:
    void paintEvent(QPaintEvent *);
private:
    QLabel *label;  //顯示操作訊息
    QLabel *versionLabel;	//顯示版本訊息
};















#endif // REDYBOARD_H
