#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QTimer>
#include<qevent.h>
class QDialog;
class QSpinBox;
class QComboBox;
class QLabel;
class QFont;
class QPushButton;
class QMediaPlayer;
class QMediaPlaylist;
class QSqlTableModel;
class QTimer;

namespace Ui {
class Clock;
}

class Clock : public QWidget
{
    Q_OBJECT

public:
    explicit Clock(QWidget *parent = 0);
    ~Clock();
    QPointF rotateAngle(int angle, int len);
     void closeEvent(QCloseEvent* event);
signals:
    void  function();
protected:
    void paintEvent(QPaintEvent *);


private slots:
    void timerUpdate();
    void setAlarmClock();
    void sureAlarmClock();
    void cancelAlarmClock();
    void updateAlarmClock();
    void stopPlayMusic();
    void selectMusic();
    void deleteAlarm();
    void rePlayMusic();

private:
    Ui::Clock *ui;
    QDialog *dialog;
    int alarmHour;
    int alarmMinute;
    int cPauseTime;
    QSpinBox *hourBox;
    QSpinBox *minuteBox;
    QComboBox *pauseTime;
    QPushButton *addAlarmBtn;
    QPushButton *closeAlarmBtn;
    QPushButton *deleteAlarmBtn[5];
    QLabel *alarmLabel[5];
    QLabel *clockLabel;
    QLabel *cTimeLabe;
    //QLabel *hourLabel;
    //QLabel *minuteLabel;
    QLabel *secondLabel;
    QPixmap bgPixmap;
    QPixmap clockPixmap;
    QPixmap hourPixmap;
    QPixmap minutePixmap;
    QPixmap secondPixmap;
    QPixmap delBtnPixmap;
    QMatrix matrix;
    QFont alarmFont;
    QMediaPlayer *player;
    QMediaPlaylist *mediaList;
    QSqlTableModel *model;
    QString musicPath;
    //QTimer *waitTimer[5];
};

#endif // CLOCK_H
