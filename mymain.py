#!/usr/bin/env python
# -*- coding: utf-8 -*-
import init_model
import predict
import select_sample
import recommend_top
import sum_accuracy
import insert_table
import time
import pymysql

def jisuan(num1, num2):
    zhunquedu = num1 / num2;
    print("两个数",num1, num2)
    print("正确度",zhunquedu);
    return zhunquedu;

'''
@功能：损失函数的优化
@参数： F：计划分类数， N：计划训练的次数（迭代次数）， alpha：学习速率， lambda1：正则化参数
@参数：pos_num 正样本个数  neg_num 负样本个数  topN 选择topN个
'''
def latent_factor_model(F, N , alpha, lambda1, pos_num, neg_sum, topN):
    print("fuck")
    # 获取函数开始时间
    start_time = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    # 将测试数据集插入数据库中
    insert_table.insert_num_info()  # 插入用户，条目，评价个数
    insert_table.insert_info_rating()  # 插入训练集
    insert_table.insert_info_rating_test()  # 插入测试集
    insert_table.insert_info_item()  # 插入每个条目的具体信息
    # 首先获得用户数和item数
    # 打开数据库
    db = pymysql.connect("127.0.0.1", "root", "1351", "qb_db")
    # 使用cursor() 方法创建一个游标对象
    my_cursor = db.cursor()
    my_cursor.execute("SELECT * FROM info_num")
    data = my_cursor.fetchone()
    user_num = data[0]  # 用户数
    item_num = data[1]  # 条目数
    rating_num = data[2]  # 评价数

    # 初始化P Q矩阵，随机生成
    user_item_class = init_model.init_model(F, user_num, item_num)
    user_class = user_item_class[0]
    item_class = user_item_class[1]
    # 初始化用户-信息矩阵，将将其存入字典中
    user_item = dict()
    user_item = init_model.init_user_item(user_num, item_num)

    print("开始迭代训练。。。")
    for step in range(0, N):
        # 从数据集中依次取出user以及该user喜欢的items集
        my_time = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
        print("第", step, "次迭代，时间：", my_time)
        for user in user_item:
            user_positive = dict()
            # 得到用户的正样本，
            user_positive = select_sample.select_positive_sample(user_item[user], pos_num)
            # 得到用户的负样本,
            user_negative = select_sample.select_negative_sample(user_item[user], neg_sum, user_positive)
            # 将正负样本集合合并
            user_samples = dict()
            user_samples.clear()
            user_samples = user_positive.copy()
            user_samples.update(user_negative)
            # print("正负样本集：", len(user_samples))
            for item in user_samples:
                # predict(user, item, P, Q)
                eui = round(user_samples[item] - predict.predict(user, item, user_class[user], item_class[item]), 5)
                for f in range(1, F+1):
                    user_class[user][f] += alpha * (eui * item_class[item][f] - lambda1 * user_class[user][f])
                    item_class[item][f] += alpha * (eui * user_class[user][f] - lambda1 * item_class[item][f])
                    user_class[user][f] = round(user_class[user][f], 5)
                    item_class[item][f] = round(item_class[item][f], 5)
        alpha *= 0.9
    print("迭代训练完成。。。")
    print("开始将user_class 和 item_class写入文件")
    #将 user_class 和 item_class写入文件
    fo = open("ml-100k/result/user_class.txt", "w")
    for x in user_class.keys():
        for y in user_class[x].keys():
            one_user_class = str(x) + "  " + str(y) + "  " + str(user_class[x][y])
            fo.write(one_user_class)
            fo.write("\n")
    fo.close()
    fo = open("ml-100k/result/item_class.txt", "w")
    for x in item_class.keys():
        for y in item_class[x].keys():
            one_item_class = str(x) + "  " + str(y) + "  " + str(item_class[x][y])
            fo.write(one_item_class)
            fo.write("\n")
    fo.close()
    print("写入文件完成！")
    print("计算每个用户的推荐列表。。。", end=' ')
    recommend_top_result = recommend_top.recommend_top([user_class, item_class], topN, user_num, item_num)
    print("计算完成！")
    print("计算准确度和召回率。。。")
    sum_accuracy.sum_accuracy(recommend_top_result, topN)
    end_time = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    print("开始时间：", start_time, "；结束时间：", end_time)
    # return [user_class, item_class]









