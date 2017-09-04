#include "mysql.h"
#include <QtSql/QSql>
#include <iostream>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlRecord>
/**
 * @brief MySql类，主要负责连接数据库 和 数据库的 查询等操作
 * @author JACO
 * @version 1.0
 */
using namespace std;
MySql::MySql()
{

}
/**
 * @brief MySql::myConnet 和数据库简历连接
 * @date 2017-06-05 15:00
 * @return 返回QSqlQuery
 */
QSqlQuery MySql::myConnet()
{
    QSqlDatabase db;
    QSqlQuery query;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("qb_db");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("1351");
//    query.exec("set Names UTF-8");

    query = QSqlQuery::QSqlQuery(db);

    if(!db.open())
    {
        qDebug() << "连接失败" << endl;
    }
    else
    {
        qDebug() << "连接成功" << endl;
    }
    return query;
}
/**
 * @brief MySql::mySelect 根据查询语句返回结果
 * @date 2017-06-05 15:00
 * @param query
 * @param qs
 * @return QVector<QString>
 */
QVector<QString> MySql::mySelect(QSqlQuery query, QString qs)
{
//    qDebug() << "查询语句" << qs;
//    qDebug() << "是否查询成功" << query.exec(qs) << endl;
    query.exec(qs);
    int i = 0;
    QVector<QString> resultVector;
    QString item = "";
    while(query.next())
    {
        while(query.value(i).toString() != "")
        {
//            qDebug() << query.value(i).toString();
            item += query.value(i).toString() + " ";
            i++;
        }
//        qDebug() << item;
        resultVector.push_back(item);
        item = "";
        i = 0;
    }
    return resultVector;
}

/**
 * @brief MySql::myLFM
 * @param query
 * @param qs
 * @return
 */
QVector<QString> MySql::myLFM(QSqlQuery query,QString qs)
{
//    qDebug() << "查询语句" << qs;
//    qDebug() << "是否查询成功" << query.exec(qs) << endl;
    query.exec(qs);
    QVector<QString> resultVector;
    QString item = "";
    int colNum = query.record().count();
    while(query.next())
    {
        for(int i = 0; i < colNum; i++)
        {
            item += query.value(i).toString() + "**";
        }
        resultVector.push_back(item);
        item = "";
    }
    return resultVector;
}

/**
 * @brief MySql::mySelectOneItem
 * @param query
 * @param qs
 * @return 查询对应id的电影名称
 */
QString MySql::mySelectOneItem(QSqlQuery query, QString qs)
{
//    qDebug() << "查询语句" << qs;
//    qDebug() << "是否查询成功" << query.exec(qs) << endl;
    query.exec(qs);
    query.next();
    QString result;
    result = query.value(1).toString();
    return result;
}
