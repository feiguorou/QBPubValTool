#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pymysql
def mytest():
    print("mytest函数！！")
    # 打开数据库
    db = pymysql.connect("127.0.0.1", "root", "1351", "qb_db")
    # 使用cursor() 方法创建一个游标对象
    my_cursor = db.cursor()
    my_cursor.execute("SELECT * FROM info_num")
    data = my_cursor.fetchone()
    user_num = data[0]  # 用户数
    item_num = data[1]  # 条目数
    rating_num = data[2]  # 评价数
    print("用户数目", user_num)
