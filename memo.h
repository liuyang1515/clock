#ifndef MEMO_H
#define MEMO_H

#include <QMainWindow>
#include <QSqlDatabase> //数据库类
#include <QSqlQuery>    //执行语句类
#include <QtSql>
#include <QApplication>
#include <QMessageBox>
#include<QTextEdit>
#include <iostream>
#include<qpushbutton.h>
#include<qevent.h>
QT_BEGIN_NAMESPACE
namespace Ui { class memo; }
QT_END_NAMESPACE

class memo : public QMainWindow
{
    Q_OBJECT

public:
    memo(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent* event);
    ~memo();
signals:
    void function();
private slots:

   void on_save_clicked();

   void on_del_clicked();

   void select();

   void on_search_clicked();

   void on_back_clicked();

 // void on_search_released();

private:
    Ui::memo *ui;
     QSqlDatabase db;            //声明数据库类
};
#endif // MEMO_H
