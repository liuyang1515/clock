#pragma once
#include <QtWidgets/QMainWindow>
#include<qevent.h>
#include"todolist/todolist.h"
#include"clock.h"
class QSqlTableModel;
class test : public QMainWindow
{
    Q_OBJECT

public:
    test(QWidget *parent = Q_NULLPTR);
    void closeEvent(QCloseEvent* event);

private:
    CToDoList *sontext= new  CToDoList;

    QSqlTableModel* model;
    bool closesignal = 0;
};
