#include "memo.h"
#include"test.h"
#include <QApplication>
#include"connection.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //����DB�ļ����������
  //  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
      //  db.setDatabaseName("database.db");
      //  if(!db.open()) return false;
       // QSqlQuery query;
       // query.exec("create table reminderl (id integer PRIMARY KEY AUTOINCREMENT,���� text,���� text)");
       // query.exec("INSERT INTO reminderl(id, ����,����) "
                     //  "VALUES (1, 'zhuti', '��2-1��')");

 createConnection();
    test w;
    w.show();
    return a.exec();
}
