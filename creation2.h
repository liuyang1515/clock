#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection2()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");

    if(!db.open()) return false;

    QSqlQuery query;
    query.exec(QString(
      "create table clock (Hour int, Minute int, Music QString)")); //鎻愮ず锛氫富閿笉鑳界浉鍚�

    return true;
}

#endif // CONNECTION_H
