#include "clock.h"
#include "ui_clock.h"
#include <QPainter>
#include <math.h>
#include <QTimerEvent>
#include <QTime>
#include <QTimer>
#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QMatrix>
#include <QFont>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QUrl>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QModelIndex>
#include <QSqlQuery>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QDebug>
#include "debug.h"

const double PI=3.141592;

Clock::Clock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Clock)
{
    ui->setupUi(this);
   // temp->show();
this->setFixedSize(580, 360);
    //设置窗口属性
    setWindowFlags(Qt::CustomizeWindowHint);//Qt::CustomizeWindowHint: 关闭默认的窗口标题提示
    //setWindowFlags(Qt::FramelessWindowHint);//Qt::FramelessWindowHint: 产生一个无窗口边框的窗口，此时用户无法移动该窗口和改变它的大小
    setWindowFlags(Qt::WindowCloseButtonHint | Qt:: WindowMinimizeButtonHint);
    //Qt::WindowCloseButtonHint:为窗口添加一个“关闭”按钮
    //Qt::WindowMinimizeButtonHint: 为窗口添加一个“最小化”按钮
    setWindowTitle("桌面闹钟");//设置窗口名称


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    timer->start(1000);

    alarmFont.setPointSize(13);//设置字体大小
    alarmFont.setFamily("宋体");//设置字体样式

    cTimeLabe = new QLabel(this);
    cTimeLabe->move(20, 280);
    cTimeLabe->setFixedSize(300, 50);
    cTimeLabe->setFont(alarmFont);
    //添加闹钟Button
    addAlarmBtn = new QPushButton( QString( "添加闹钟"), this);
    addAlarmBtn->setFixedSize(110, 50);//设置Button大小
    addAlarmBtn->setFont(alarmFont);
    addAlarmBtn->move(330, 270);//设置Button左上角的点位
    connect( addAlarmBtn, SIGNAL(clicked()), this, SLOT(setAlarmClock()) );
    //删除闹钟Button
    closeAlarmBtn = new QPushButton("关闭闹钟", this);
    closeAlarmBtn->setFixedSize(110, 50);
    closeAlarmBtn->setFont(alarmFont);
    closeAlarmBtn->move(440, 270);
    connect( closeAlarmBtn, SIGNAL(clicked()), this, SLOT(stopPlayMusic()) );

    player = new QMediaPlayer(this);
    mediaList = new QMediaPlaylist(this);

    model = new QSqlTableModel(this);
    model->setTable("clock");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select(); //选取整个表的所有行
    //不显示name属性列,如果这时添加记录，则该属性的值添加不上
    //model->removeColumn(1);
    //使其不可编辑
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    bgPixmap = QPixmap(":/images/background.png").scaled(size());
    //clockPixmap = QPixmap("clock.png");
    delBtnPixmap = QPixmap(":/images/deleteBtn.png");

    //clockLabel = new QLabel(this);
    //clockLabel->setPixmap(clockPixmap);
    //clockLabel->move(30, 30);

    updateAlarmClock();
}

Clock::~Clock()
{
    delete ui;
}


QPointF Clock::rotateAngle(int angle, int len)
{
    int x, y;

    x = 150+len*sin(angle*PI/180);
    y = 150-len*cos(angle*PI/180);

    return QPointF(x, y);
}

//绘制时钟界面
void Clock::paintEvent(QPaintEvent *)
{
    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();
    int timeS = time.second();

    QDateTime dateTime = QDateTime::currentDateTime();
    cTimeLabe->setText(dateTime.toString("yyyy-MM-dd hh:mm:ss ddd"));

    QPainter painter(this);
    QPen pen;
    //设置界面背景
    painter.drawPixmap(this->rect(), bgPixmap);
    //绘制钟面
    //绘制最小刻度
    pen.setWidth(1);
    pen.setColor("#333");
    painter.setPen(pen);
    for(int i=0; i<60; i++)
    {
        painter.drawLine(rotateAngle(6*i, 100), rotateAngle(6*i, 95));
    }
    //绘制圆盘
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawEllipse(QPoint(150, 150), 100, 100);
    //绘制12小时大刻度
    pen.setWidth(3);
    painter.setPen(pen);
    for(int i=0; i<12; i++)
    {
        painter.drawLine(rotateAngle(30*i, 100), rotateAngle(30*i, 90));
    }

    //绘制指针
    //秒针
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(QPointF(150, 150), rotateAngle(6*timeS, 80));
    //分针
    pen.setWidth(6);
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.drawLine(QPointF(150, 150), rotateAngle(6*timeM, 60));
    //时针
    pen.setWidth(8);
    pen.setColor(Qt::green);
    painter.setPen(pen);
    painter.drawLine(QPointF(150, 150), rotateAngle(0.5*(timeH*60+timeM), 40));
}
//时钟更新函数
void Clock::timerUpdate()
{
    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();
    int timeS = time.second();

    int rowNum = model->rowCount();
    for(int i=0; i<rowNum; i++)
    {
        if(timeH == model->index(i, 0).data().toInt()
                && timeM == model->index(i, 1).data().toInt()
                && timeS == 0)
        {
            mediaList->addMedia(QUrl::fromLocalFile(model->index(i, 2).data().toString()));
            mediaList->setCurrentIndex(i);
            player->setPlaylist(mediaList);
            player->play();

            /*waitTimer[i] = new QTimer(this);
            connect( waitTimer[i], SIGNAL(timeout), this, SLOT(rePlayMusic()) );
            waitTimer[i]->start(60*1000);*/
        }
    }

    update();
}

//闹钟设置窗口
void Clock::setAlarmClock()
{
    dialog = new QDialog(this);
    hourBox = new QSpinBox(dialog);
    minuteBox = new QSpinBox(dialog);
    pauseTime = new QComboBox(dialog);
    QLabel *label1 = new QLabel(dialog);
    QLabel *label2 = new QLabel(dialog);
    QLabel *label3 = new QLabel(dialog);
    QLabel *label4 = new QLabel(dialog);
    QPushButton *selectMusicBtn = new QPushButton(dialog);

    label1->setText("闹铃时间：");
    label1->setFont(alarmFont);
    label1->move(20, 30);
    label2->setText("暂停时间：");
    label2->setFont(alarmFont);
    label2->move(20, 80);
    label3->setText("分钟");
    label3->setFont(alarmFont);
    label3->move(170, 80);
    label4->setText("选择闹铃：");
    label4->setFont(alarmFont);
    label4->move(20, 130);

    //pauseTime->setEditable(true);
    pauseTime->move(120, 80);
    pauseTime->addItem("5");
    pauseTime->addItem("10");
    pauseTime->addItem("15");
    pauseTime->addItem("20");
    pauseTime->addItem("25");
    pauseTime->addItem("30");
    pauseTime->setFont(alarmFont);

    //设置时间框
    hourBox->setPrefix("H: ");
    hourBox->setRange(0, 23);
    hourBox->setFixedSize(80, 30);
    hourBox->move(QPoint(120, 30));
    hourBox->setFont(alarmFont);
    minuteBox->setPrefix("M: ");
    minuteBox->setRange(0, 59);
    minuteBox->setFixedSize(80, 30);
    minuteBox->move(QPoint(200, 30));
    minuteBox->setFont(alarmFont);

    selectMusicBtn->move(120, 130);
    selectMusicBtn->setFixedSize(120, 30);
    connect( selectMusicBtn, SIGNAL(clicked()), this, SLOT(selectMusic()));

    QPushButton *sureBtn = new QPushButton("确定", dialog);
    QPushButton *cancelBtn = new QPushButton("取消", dialog);

    sureBtn->move(50, 180);
    sureBtn->resize(80, 30);
    sureBtn->setFont(alarmFont);
    cancelBtn->move(170, 180);
    cancelBtn->resize(80, 30);
    cancelBtn->setFont(alarmFont);

    connect( sureBtn, SIGNAL(clicked()), this, SLOT(sureAlarmClock()) );
    connect( cancelBtn, SIGNAL(clicked()), this, SLOT(cancelAlarmClock()) );

    dialog->setWindowTitle("添加闹钟");
    //dialog->setWindowFlags(Qt::FramelessWindowHint);
    //设置固定窗口大小
    dialog->setFixedSize(300, 240);
    //模态对话框
    dialog->exec();
}

void Clock::updateAlarmClock()
{
    int rowNum = model->rowCount();

    for(int alarmNum=0; alarmNum<rowNum; alarmNum++)
    {
        alarmLabel[alarmNum] = new QLabel(this);
        alarmLabel[alarmNum]->move(300, 30+40*alarmNum);
        alarmLabel[alarmNum]->setFixedSize(240, 30);
        alarmLabel[alarmNum]->setFont(alarmFont);
        alarmLabel[alarmNum]->setText(model->index(alarmNum, 0).data().toString()
                             + " : "
                             + model->index(alarmNum, 1).data().toString()
                             + "   "
                             + QFileInfo( model->index(alarmNum, 2).data().toString() ).fileName());
        alarmLabel[alarmNum]->setVisible(true);

        deleteAlarmBtn[alarmNum] = new QPushButton(this);
        deleteAlarmBtn[alarmNum]->move(260, 30+40*alarmNum);
        deleteAlarmBtn[alarmNum]->setFixedSize(30, 30);
        deleteAlarmBtn[alarmNum]->setIcon(delBtnPixmap);
        deleteAlarmBtn[alarmNum]->setFlat(true);
        deleteAlarmBtn[alarmNum]->setVisible(true);
        connect( deleteAlarmBtn[alarmNum], SIGNAL(clicked()), this, SLOT(deleteAlarm()) );
    }
}

void Clock::sureAlarmClock()
{
    alarmHour = hourBox->value();
    alarmMinute = minuteBox->value();

    cPauseTime = pauseTime->currentText().toInt();

    int rowNum = model->rowCount();
    if(rowNum < 5)
    {
        model->insertRow(rowNum);
        model->setData(model->index(rowNum, 0), alarmHour);
        model->setData(model->index(rowNum, 1), alarmMinute);
        model->setData(model->index(rowNum, 2), musicPath);
        model->submitAll();
        model->setTable("clock");
        model->select();

        for(int i=0; i<rowNum; i++)
        {
            delete alarmLabel[i];
            delete deleteAlarmBtn[i];
        }

        qDebug() << model->index(rowNum, 0).data().toString()
                    << model->index(rowNum, 1).data().toString()
                       << QFileInfo( model->index(rowNum, 2).data().toString() ).fileName();

        updateAlarmClock();
    }
    else
    {
        QMessageBox::warning(this, "警告", "闹钟数量已达上限！", QMessageBox::Yes);
    }

    dialog->close();
}

void Clock::cancelAlarmClock()
{
    dialog->close();
}

void Clock::stopPlayMusic()
{
    player->stop();
}

void Clock::selectMusic()
{
    musicPath = QFileDialog::getOpenFileName(this, "选择铃声",
                                             "G:/歌曲", "*.mp3");
}

void Clock::rePlayMusic()
{
    player->play();

    /*QTimer *timer = qobject_cast<QTimer*>(QObject::sender());

    int i = 1;
    if(i == 5)
    {
        i = 1;
        if(timer->isActive())
            timer->stop();
    }*/
}

void Clock::deleteAlarm()
{
    int rowNum = model->rowCount();

    qDebug() << rowNum;

    //QObject::sender()返回发送信号的对象的指针
    QPushButton *btn = qobject_cast<QPushButton*>(QObject::sender());

    if( btn == deleteAlarmBtn[0] )
    {
        model->removeRows(0, 1);
        qDebug() << "delete 0";
    }
    else if( btn == deleteAlarmBtn[1] )
    {
        model->removeRows(1, 1);

        qDebug() << "delete 1";
    }
    else if( btn == deleteAlarmBtn[2] )
    {
        model->removeRows(2, 1);
        qDebug() << "delete 2";
    }
    else if( btn == deleteAlarmBtn[3] )
    {
        model->removeRows(3, 1);
    }
    else if( btn == deleteAlarmBtn[4])
    {
        model->removeRows(4, 1);
    }

    int ok = QMessageBox::warning(this, "删除当前闹钟！",
                                   "您确定删除当前闹钟吗？",
                                  QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        model->revertAll();   //如果不删除, 则撤销

        qDebug() << rowNum;
    }
    else
    {
        for(int i=0; i<rowNum; i++)
        {
            delete alarmLabel[i];
            delete deleteAlarmBtn[i];
        }

        model->submitAll();   //否则提交, 在数据库中删除该行

        updateAlarmClock();

        rowNum = model->rowCount();

        qDebug() << rowNum;
    }
}
void Clock::closeEvent(QCloseEvent* event)
{
    emit function();
        this->hide();
     event->ignore();
}
