#ifndef MYSQL_H
#define MYSQL_H

#include <QSqlQuery>
#include <QVector>

class MySql
{
public:
    MySql();
    // 建立数据库连接
    QSqlQuery myConnet();
    QVector<QString> mySelect(QSqlQuery query,QString qs);
    QVector<QString> myLFM(QSqlQuery query,QString qs);
    QString mySelectOneItem(QSqlQuery query,QString qs);

};

#endif // MYSQL_H
