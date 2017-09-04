#include "mylfmresult.h"
#include <iostream>
#include <qfile.h>
#include <QDebug>
#include <Python.h>

using namespace std;

mylfmresult::mylfmresult()
{

}
/**
 * @brief mylfmresult::recResult
 * @param userId
 * @功能：计算推荐准确度
 */
void mylfmresult::recResult(QString userId)
{
    qDebug() << "userId:" << userId;
    //初始化python模块
    Py_Initialize();
    if ( !Py_IsInitialized() )
    {
        cout << "init failed!!" << endl;
//        return -1;
    }
    //导入mymain.py模块
    PyObject *pModule = PyImport_ImportModule("mymain");
    if ( !pModule )
    {
        printf("can't open this python file\n");
//        return -1;
    }

    QFile file("ml-100k/result/eva.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file eva.txt!";
    }
    while(!file.atEnd()) {
        QByteArray line = file.readLine();
        QString str(line);
        str = str.replace("\n","");
        qDebug()<< str;
    }
    file.close();

    MyLFM myLFM;
    QVector<QString> result =  myLFM.findRec(userId);
    int len = result.length();
    QStringList recIdList;
    qDebug() << "推荐列表：";
    for(int i = 0; i < len; i++)
    {
        recIdList.append(result.at(i).split("**").at(1));
//        qDebug() << result.at(i).split("**").at(1);
    }
    QVector<QString> result2 =  myLFM.findTest(userId);
    int len2 = result2.length();
    QStringList testIdList;
    qDebug() << "测试列表：";
    for(int i = 0; i < len2; i++)
    {
        testIdList.append(result2.at(i).split("**").at(1));
//        qDebug() << result2.at(i).split("**").at(1);
    }
    int rightNum = 0;
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len2; j++)
        {
            if(QString::compare(recIdList.at(i), testIdList.at(j)) == 0)
            {
                qDebug() << "相同id" << recIdList.at(i);
                rightNum++;
            }
        }
    }
    //获取mymain模块中的latent_factor_model函数
    PyObject *pFunhello1 = PyObject_GetAttrString(pModule, "jisuan");
    if ( !pFunhello1 )
    {
        cout << "get function jisuan failed!" << endl;
//        return -1;
    }
    PyObject_CallFunction(pFunhello1, "ii",rightNum, len);
    Py_Finalize();
}
