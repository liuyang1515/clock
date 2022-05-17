#include "memo.h"
#include"test.h"
#include <QApplication>
#include"connection.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //创建DB文件，创建表格
  //  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
      //  db.setDatabaseName("database.db");
      //  if(!db.open()) return false;
       // QSqlQuery query;
       // query.exec("create table reminderl (id integer PRIMARY KEY AUTOINCREMENT,主题 text,内容 text)");
       // query.exec("INSERT INTO reminderl(id, 主题,内容) "
                     //  "VALUES (1, 'zhuti', '初2-1班')");

 createConnection();
    test w;
    w.show();
    return a.exec();
}
