#include "mymainview.h"
#include <QApplication>
#include <Python.h>
#include <iostream>
#include <QDebug>
#include <exception>
#include <QDir>
#include <QTextCodec>
#include <mysql.h>
#include <mylfm.h>
#include <mylfmresult.h>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //初始化python模块
    Py_Initialize();
    if ( !Py_IsInitialized() )
    {
        cout << "init failed!!" << endl;
        return -1;
    }
    //导入mymain.py模块
    PyObject *pModule = PyImport_ImportModule("mymain");
    if ( !pModule )
    {
        printf("can't open this python file\n");
        return -1;
    }
    //获取mymain模块中的latent_factor_model函数
    PyObject *pFunhello = PyObject_GetAttrString(pModule, "latent_factor_model");
    if ( !pFunhello )
    {
        cout << "get function hello failed!" << endl;
        return -1;
    }
    //调用latent_factor_model函数
    //PyObject pyObject = PyObject_CallFunction(pFunhello, "iiffiii",30, 10, 0.06, 0.06, 30, 60, 15); //F, N , alpha, lambda1, pos_num, neg_sum, topN
    //PyObject_CallFunction(pFunhello, "iiffiii",30, 10, 0.06, 0.06, 30, 60, 15);


    //获取评估结果，并将指定的人的推荐结果和准确率等计算出来

    //中文支持
//    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//    QTextCodec::setCodecForCStrings(codec);

    mylfmresult fuck;
    fuck.recResult("308");



//    QFile file1("ml-100k/result/user_item_rec.txt");
//    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        qDebug()<<"Can't open the file!";
//    }
//    if(!file1.atEnd()) {
//        QByteArray line = file1.readLine();
//        QString str(line);
//        str = str.replace("\n","");
//        qDebug()<< str;
//    }
//    QStringList itemid;
//    MySql mySql;
//    QSqlQuery query = mySql.myConnet();
//    QString pre_sql_one = "SELECT * FROM info_item WHERE id = ";  //查询语句
//    QString sql_one = "";
//    QVector<QString> result;
//    if(!file1.atEnd()) {
//        QByteArray line = file1.readLine();
//        QString str(line);
//        str = str.replace("\n","");
//        qDebug() << str;
//        itemid = str.split(",");
//        qDebug() << itemid;
//        for(int i = 0; i < 15; i++)
//        {
//            sql_one = pre_sql_one + itemid.at(i);
//            result = mySql.myLFM(query, sql_one);
//            qDebug() << "查询结果";
//            qDebug()<< result.at(0).split("**").at(1);
//        }
//    }
//    file1.close();



    //查看当前路径：为debug下目录
//    QString path = QDir::currentPath();
//    qDebug() << path;

//    PyObject *pDict = PyDict_New();
//    PyDict_SetItemString(pDict, "F", Py_BuildValue("i", 30));
//    PyDict_SetItemString(pDict, "N", Py_BuildValue("i", 10));
//    PyDict_SetItemString(pDict, "alpha", Py_BuildValue("f", 0.06));
//    PyDict_SetItemString(pDict, "lambda1", Py_BuildValue("i", 0.06));
//    PyDict_SetItemString(pDict, "pos_num", Py_BuildValue("i", 30));
//    PyDict_SetItemString(pDict, "neg_sum", Py_BuildValue("i", 60));
//    PyDict_SetItemString(pDict, "topN", Py_BuildValue("i", 15));
//    PyObject *pArgs = PyTuple_New(1);
//    PyTuple_SetItem(pArgs, 0, pDict);
//    PyEval_CallObject(pFunhello, pArgs);
//    PyObject *pyResult = PyEval_CallObject(pFunhello, pArgs);
//    PyObject* pResultStr = PyObject_Repr(pyResult);
//    std::string returnedString = PyUnicode_AsUTF8(pResultStr);


//    PyObject F = new int(30);
//    PyObject N = new int(1);
//    PyObject alpha = new float(0.06);
//    PyObject lambda1 = new float(0.06);
//    PyObject pos_num = new int(30);
//    PyObject neg_sum = new int(60);
//    PyObject topN = new int(15);

//    PyTuple_SetItem(pArgs, 0, F);
//    PyTuple_SetItem(pArgs, 1, N);
//    PyTuple_SetItem(pArgs, 2, alpha);
//    PyTuple_SetItem(pArgs, 3, lambda1);
//    PyTuple_SetItem(pArgs, 4, pos_num);
//    PyTuple_SetItem(pArgs, 5, neg_num);
//    PyTuple_SetItem(pArgs, 6, topN);
//    PyObject *pyResult = PyEval_CallObject(pFunhello, pArgs);
//    PyObject *pResultStr = PyObject_Repr(pyResult);
//    std::string returnedString = PyUnicode_AsUTF8(pResultStr);
//    std::cout << returnedString << std::endl;
    //结束，释放python
    Py_Finalize();

    MyMainView v;
    v.show();
    return a.exec();
}
