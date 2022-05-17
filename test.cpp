#include "test.h"
#include"Date.h"
#include"qdebug.h"
#include"MyLabel.h"
#include<qlabel.h>
#include<vector>
#include<qdatetime.h>
#include<qpushbutton.h>
#include<QSystemTrayIcon>
#include<qmenu.h>
#include"memo.h"
#include"weather.h"
test::test(QWidget* parent)
    : QMainWindow(parent)
{
//;
   // int sumofwidget=0;
    this->resize(520, 420);
    QPixmap pixmap = QPixmap(":/images/background.png").scaled(this->size());
        QPalette palette(this->palette());
        palette.setBrush(QPalette::Background, QBrush(pixmap));
        this->setPalette(palette);
 QLabel*testlabel2=new QLabel(this);
 testlabel2->setGeometry(410,30,180,80);
   QTimer *timer = new QTimer(this);
   connect(timer,&QTimer::timeout,[=](){
       QDateTime time = QDateTime::currentDateTime();
       testlabel2->setFont(QFont("Microsoft YaHei",10,75));
           QString str = time.toString("yyyy-MM-dd\n hh:mm:ss\n dddd");
           testlabel2->setText(str);
   });
       timer->start(1000);
    QLabel*testlabel=new QLabel(this);
    //testlabel->setpo
testlabel->setText((Date:: getLunarTime(2022)));
testlabel->setGeometry(200,0,60,30);
    Clock*templ=new  Clock;
    memo* temp2=new memo;
         temp2->hide();
    //templ->show();
    templ->hide();
    setWindowTitle(QString::fromLocal8Bit("大学生时间管理系统"));
    // sonclok->hide();
    setWindowIcon(QIcon(":/souce/clock.png"));
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint); setFixedSize(this->width(), this->height());
    MyLabel* allLabel[6][7];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++)
        {
            allLabel[i][j] = new MyLabel(this);

            allLabel[i][j]->setGeometry(j * 60, i * 60+60, 60, 60);
            QFont ft;
            ft.setPointSize(10);
            allLabel[i][j]->setFont(ft);
        }
    }
 QLabel* zhou0=new QLabel(this);
   zhou0->setText(QString::fromLocal8Bit("周一"));
   zhou0->setGeometry(0,0,60,60);
   zhou0->setFont(QFont ("Microsoft YaHei",10, 75));
   QLabel* zhou1=new QLabel(this);
  zhou1->setText(QString::fromLocal8Bit("周二"));
  zhou1->setGeometry(60,0,60,60);
     zhou1->setFont(QFont ("Microsoft YaHei",10, 75));
  QLabel* zhou2=new QLabel(this);
 zhou2->setText(QString::fromLocal8Bit("周三"));
 zhou2->setGeometry(120,0,60,60);
    zhou2->setFont(QFont ("Microsoft YaHei",10, 75));
 QLabel* zhou3=new QLabel(this);
zhou3->setText(QString::fromLocal8Bit("周四"));
zhou3->setGeometry(180,0,60,60);
   zhou3->setFont(QFont ("Microsoft YaHei",10, 75));
QLabel* zhou4=new QLabel(this);
zhou4->setText(QString::fromLocal8Bit("周五"));
zhou4->setGeometry(240,0,60,60);
   zhou4->setFont(QFont ("Microsoft YaHei",10, 75));
QLabel* zhou5=new QLabel(this);
zhou5->setText(QString::fromLocal8Bit("周六"));
zhou5->setGeometry(300,0,60,60);
   zhou5->setFont(QFont ("Microsoft YaHei",10, 75));
QLabel* zhou6=new QLabel(this);
zhou6->setText(QString::fromLocal8Bit("周日"));
zhou6->setGeometry(360,0,60,60);
  zhou6->setFont(QFont ("Microsoft YaHei",10, 75));

    // 首先判断当前月的第一天是星期几
    int nWeek = Date::getFirstDayOfWeek(QDate::currentDate().year(), QDate::currentDate().month());
   // int nMonthDays = Date::getMonthDays(QDate::currentDate().year(), QDate::currentDate().month());
    //上月天数
    int aa = Date::getMonthDays(QDate::currentDate().year(), QDate::currentDate().month());
  //  int nPreMonDays = Date::getMonthDays(1 == QDate::currentDate().month() ? QDate::currentDate().year() - 1 : QDate::currentDate().year(), 1 == QDate::currentDate().month() ? 12 : QDate::currentDate().month() - 1);
    // 显示上月剩余天数、
    for (int tempi = nWeek, tempt = 1; tempi < (nWeek + aa); tempi++, tempt++) {
        int row = tempi / 7 + 1;
        int col = tempi % 7 - 1;
        allLabel[row][col]->setStyleSheet("color:black;");
        QString templ = QString::number(tempt);
        QString temp2 = Date::getLunarDate(QDate::currentDate().year(), QDate::currentDate().month(), tempt);
        allLabel[row][col]->setText(templ + "\n" + temp2);

    }
    QPushButton *button1=new QPushButton(this);
    button1->move(400, 150);
    QPushButton* button2 = new QPushButton(this);
    button2->move(400, 200);
    QPushButton* button3 = new QPushButton(this);
    button3->move(400, 250);
    button1->setText(QString::fromLocal8Bit("待办事项"));
     button2->setText(QString::fromLocal8Bit("闹钟"));
     button3->setText(QString::fromLocal8Bit("备忘录"));
    connect(button1, &QPushButton::pressed, [=]() {
        this->hide();
        sontext->show();
        });
    connect(button2, &QPushButton::pressed, [=]() {
        this->hide();
       templ->show();
        });
    connect(button3, &QPushButton::pressed, [=]() {
         this->hide();
        temp2->show();
        });

    QSystemTrayIcon* systemtrayicon = new  QSystemTrayIcon(this);  //系统托盘
   // QIcon icon = QIcon(":/souce/clock.png");
    systemtrayicon->setIcon(QIcon("://images/clock.png"));//设置图标

    systemtrayicon->setToolTip(weather());     //当鼠标悬浮，显示文字menu = new QMenu(this);
    systemtrayicon->show();
    QMenu* menu = new QMenu();
    QAction* m_pShowAction = new QAction(QString::fromLocal8Bit("打开主界面"));
    QAction* m_pCloseAction = new QAction(QString::fromLocal8Bit("退出"));
    QAction* function_1 = new QAction(QString::fromLocal8Bit("待办事项"));
    QAction* function_2 = new QAction(QString::fromLocal8Bit("闹钟"));
    QAction* function_3 = new QAction(QString::fromLocal8Bit("备忘录"));

    menu->addAction(function_1);
    menu->addAction(function_2);
    menu->addAction(function_3);
    menu->addSeparator();

    menu->addAction(m_pShowAction);
    menu->addSeparator();
    menu->addAction(m_pCloseAction);
    systemtrayicon->setContextMenu(menu);

    connect(function_1, &QAction::triggered, [=]() {
        this->hide();
        sontext->show();

        });
   //connect(sontext,&QWidget::hide &, [=]() {


   //    });
    connect(function_2, &QAction::triggered, [=]() {
        this->hide();
       templ->show();
        });
    connect(function_3, &QAction::triggered, [=]() {
        this->hide();
       temp2->show();
        });
    connect(m_pShowAction, &QAction::triggered, [=]() {
        this->show();
        });
    connect(m_pCloseAction, &QAction::triggered, [=]() {
        closesignal = 1;
        this->close();
        });
    connect(sontext,&CToDoList::function,[=](){
        this->show();
    });
    connect( templ,&Clock::function,[=](){
        this->show();
    });
    connect(  temp2,&memo::function,[=](){
        this->show();
    });

}

void test::closeEvent(QCloseEvent* event)
{
    if (closesignal == 1) {
        int ret1 = QMessageBox::question(this,QString::fromLocal8Bit("提示"),
                                            QString::fromLocal8Bit("你确认退出吗"), QMessageBox::Yes, QMessageBox::No);
        if(ret1==QMessageBox::Yes){

        }
        else{
            closesignal=0;
            this->show();
            event->ignore();
        }
    }
    else {
        this->hide();
        event->ignore();
    }
}
