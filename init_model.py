#!/usr/bin/env python
# -*- coding: utf-8 -*-
import random
import pymysql
'''
@功能：初始化 用户-隐类表user_class 和 条目-隐类表item_class
@参数：C代表隐类的个数
@参数：user_num 用户数， item_num 条目数
@作者：张家浩
@时间：2017-05-20-15：00
'''
def init_model (C, user_num, item_num) :
    user_class = dict()  # 用户-隐类关系表
    item_class = dict()  # 条目-隐类关系表
    # 读取每个用户的id，这里直接将 user_num 作为用户id
    # 随机生成用户-隐类关系表
    for x in range(1, user_num+1):
        user_class[x] = dict()
        # 随机生成用户和第y个隐类的相关度
        for y in range(1, C+1):
            r = round(random.random(), 2)
            user_class[x][y] = r
    # 随机生成信息-隐类关系表
    for x in range(1, item_num+1):
        item_class[x] = dict()
        for y in range(1, C+1):
            r = round(random.random(), 2)
            item_class[x][y] = r
    return [user_class, item_class]

'''
@功能：从数据库info_rating表中读取用户评价，初始化用户-条目评价表
@参数：user_num 用户数， item_num 条目数
@作者：张家浩
@时间：2017-06-20 16：00
'''
def init_user_item(user_num, item_num):
    # 初始化user_item, 全部赋值为0
    user_item = dict()
    for x in range(1, user_num+1):
        user_item[x] = dict()
        for y in range(1, item_num+1):
            user_item[x][y] = 0
    # 打开数据库
    db = pymysql.connect("127.0.0.1", "root", "1351", "qb_db")
    # 使用cursor() 方法创建一个游标对象
    my_cursor = db.cursor()
    select_all_sql = "SELECT userid, itemid, rating FROM info_rating"
    my_cursor.execute(select_all_sql)
    result = my_cursor.fetchall()
    for row in result:
        userid = int(row[0])
        itemid = int(row[1])
        rating = row[2]
        if rating == 1:
            user_item[userid][itemid] = 1
    db.commit()
    db.close()
    return user_item

# init_user_item(943, 1682)




