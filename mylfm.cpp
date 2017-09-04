#include "mylfm.h"
#include <mysql.h>
#include <QDebug>

MyLFM::MyLFM()
{

}

/**
 * @brief MyLFM::findRec
 * @param id
 * @return 查找某用户的推荐列表
 */
QVector<QString> MyLFM::findRec(QString id)
{
    // 建立连接
    MySql mySql;
    QSqlQuery query = mySql.myConnet();
    QString Sql_one = "SELECT * FROM info_rec WHERE id = '" + id + "'";  //查询语句
    // 获取结果
    QVector<QString> result;
    result = mySql.myLFM(query, Sql_one);
    QVector<QString> result1;
    int len = result.length();
    QString itemId = "";
    QString itemName = "";
    for(int i = 0; i < len; i++)
    {
        itemId = result.at(i).split("**").at(1);
        Sql_one = "SELECT * FROM info_item WHERE id = '" + itemId + "'";
        itemName = mySql.mySelectOneItem(query, Sql_one);
        result1.append(result.at(i) + itemName);
    }
    query.finish();
    return result1;
}

/**
 * @brief MyLFM::findTest
 * @param id
 * @return  查找某用户的测试列表
 */
QVector<QString> MyLFM::findTest(QString id)
{
    // 建立连接
    MySql mySql;
    QSqlQuery query = mySql.myConnet();
    QString Sql_one = "SELECT * FROM info_rating_test WHERE userid = '" + id + "'";  //查询语句
    // 获取结果
    QVector<QString> result;
    result = mySql.myLFM(query, Sql_one);
    QVector<QString> result1;
    int len = result.length();
    QString itemId = "";
    QString itemName = "";
    for(int i = 0; i < len; i++)
    {
        itemId = result.at(i).split("**").at(1);
        Sql_one = "SELECT * FROM info_item WHERE id = '" + itemId + "'";
        itemName = mySql.mySelectOneItem(query, Sql_one);
        result1.append(result.at(i) + itemName);
    }
    query.finish();
    return result1;
}
