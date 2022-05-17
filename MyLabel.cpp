#include "MyLabel.h"
#include <QDebug>
#include<QMouseEvent>
MyLabel::MyLabel(QWidget* parent) : QLabel(parent)
{
    this->setMouseTracking(true);
}


//������

void MyLabel::enterEvent(QEvent*)
{

    this->setStyleSheet("color:red;"
                "border-style: solid;"
                                  "border-width: 2px;"
                                  "border-color: aqua;"
                                  "border-radius: 20px;");//������ʽ��->setStyleSheet("QLabel{background-color:rgb(200,101,102);}");  //������ʽ��
    QFont ft;
    ft.setPointSize(12);
    this->setFont(ft);
}

//����뿪
void MyLabel::leaveEvent(QEvent*)
{

    this->setStyleSheet("color:black;");
    QFont ft;
    ft.setPointSize(10);
    this->setFont(ft);
}


