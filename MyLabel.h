#ifndef MYLABEL_H
#define MYLABEL_H
 
#include <QLabel>
 
class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);
 
 
    //捕获事件
    //鼠标进入
 
    void enterEvent(QEvent *);
 
    //鼠标离开
    void leaveEvent(QEvent *);

 
};
 
#endif // MYLABEL_H