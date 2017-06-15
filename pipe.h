#ifndef PIPE_H
#define PIPE_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
//  水管類別
class Pipe : public QWidget
{
    Q_OBJECT
public:
    Pipe(QWidget *parent = 0);
    ~Pipe();
    int getH1();  //取得H1值
    int getH2();  //取得H2值
    int getGap(); //取得Gap值
private:
    void setGapSize(int w); //設定縫隙寬度值
protected:
    void paintEvent(QPaintEvent *);
    int H1,H2; //H1:上水管原始長度,H2下水管原始長度
    int Gap; //水管縫隙寬度, 預設140
};








#endif // PIPE_H
