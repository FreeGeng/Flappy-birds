#ifndef GROUND_H
#define GROUND_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
// 地板類別
class Ground : public QWidget
{
    Q_OBJECT
public:
    Ground(QWidget *parent = 0);
    ~Ground();
    void stop();  //停止timer
    void play();  //啟動timer
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void groundM();  //移動地板, 不斷向左移動
private:
    QTimer *timer;
    int sx,sy;  //地板圖片的x,y座標
};










#endif // GROUND_H
