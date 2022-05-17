#ifndef TODOLIST_H
#define TODOLIST_H
#include <QMainWindow>
#include<QListView>
#include<QStringListModel>
#include<qevent.h>

 class CToDoList:public QMainWindow
 {
     Q_OBJECT
 public:
     CToDoList();
     void closeEvent(QCloseEvent* event);
signals:
     void  function();

 protected slots:
     void onAdd();
     void onRemove();
 private:
     QListView*m_pwPending=nullptr;
     QListView*m_pwCompleted=nullptr;

     QAction*m_pActAdd=nullptr;
     QAction*m_pActRemove=nullptr;
 };

#endif // TODOLIST_H
