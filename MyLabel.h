#ifndef MYLABEL_H
#define MYLABEL_H
 
#include <QLabel>
 
class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);
 
 
    //�����¼�
    //������
 
    void enterEvent(QEvent *);
 
    //����뿪
    void leaveEvent(QEvent *);

 
};
 
#endif // MYLABEL_H