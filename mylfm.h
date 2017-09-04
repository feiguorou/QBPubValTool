#ifndef MYLFM_H
#define MYLFM_H
#include <QString>

class MyLFM
{
public:
    MyLFM();
    //查找第一个人的推荐集，人员id，默认为第一个，返回其
    QVector<QString> findRec(QString  id);
    ////查找第一个人的测试集，人员id，默认为第一个，返回其
    QVector<QString> findTest(QString  id);

};

#endif // MYLFM_H
