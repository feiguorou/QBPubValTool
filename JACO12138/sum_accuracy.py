#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pymysql
'''
@功能：计算准确度
@参数： test_file 测试文件
@参数： recommend_top_result 推荐列表
@参数： topN个推荐结果
'''
def sum_accuracy(recommend_top_result:dict(), topN):
    right_num = 0
    right_rate = 0
    test_user_item = dict()
    # 打开数据库
    db = pymysql.connect("127.0.0.1", "root", "1351", "qb_db")
    # 使用cursor() 方法创建一个游标对象
    my_cursor = db.cursor()
    my_cursor.execute("SELECT * FROM info_rating_test")
    data = my_cursor.fetchone()
    while data:
        user_id = data[0]
        item_id = data[1]
        eva = data[2]
        if int(eva) > 0:
            if user_id not in test_user_item.keys():
                test_user_item[user_id] = list()
                test_user_item[user_id].append(str(item_id))
            else:
                test_user_item[user_id].append(str(item_id))
        data = my_cursor.fetchone()
    all_user_like_item = 0
    for x in test_user_item.keys():
        all_user_like_item += len(test_user_item[x])
        for y in test_user_item[x]:
            # print("用户",x,";条目",y)
            if int(y) in recommend_top_result[int(x)]:
                right_num += 1

    print("命中条目数", right_num)
    print("用户数目", len(test_user_item))
    print("topN", topN)
    right_rate = right_num / (len(test_user_item) * topN)
    call_rate = right_num / all_user_like_item
    print("准确度：", right_rate)
    print("召回率：", call_rate)

    fo = open("ml-100k/result/eva.txt", "w")
    fo.write(str(len(test_user_item)) + "\n")  # 用户数目
    fo.write(str(len(test_user_item) * topN) + "\n")  # 推荐条目数
    fo.write(str(right_num) + "\n")  # 命中条目数
    fo.write(str(all_user_like_item) + "\n")  # 实际用户喜欢条目数
    fo.write(str(right_rate) + "\n")  # 准确率
    fo.write(str(call_rate) + "\n")  # 召回率
    fo.close()


