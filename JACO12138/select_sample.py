#!/usr/bin/env python
# -*- coding: utf-8 -*-
import random
import init_model
'''
@功能：对某个用户采集正样本,返回正样本集
@参数：one_user_item代表某个用户对所有条目的信息
@参数：pos_num代表需要采集的正样本数目
@作者：张家浩
@时间： 2017-05-27-15：05
'''
def select_positive_sample(one_user_item : dict(), pos_num):
    x = 1  # 记录user中的条目数
    my_key = dict()  # 记录每个用户的条目
    ret = dict()  # 返回随机采集的结果
    y = 0
    for key in one_user_item.keys():
        my_key[x] = key
        x += 1
    # 循环，找到pos_num个正样本集
    for n in range(0, 3*len(my_key)):
        if y >= pos_num:
            break
        x = random.randint(1, len(my_key))
        if my_key[x] not in ret.keys() and one_user_item[my_key[x]] > 0:
            # print(x+1, my_key[x+1], ret[my_key[x+1]], end=' ')
            ret[my_key[x]] = 1
            y += 1
    # print (ret)
    return ret

'''
@功能：对某个用户采集负样本过程，返回负样本集
@参数：one_user_item代表某个用户对所有条目的信息
@参数：neg_num代表需要采集的正样本数目
@参数：item_pool 代表备选条目池，备选条目的筛选可以有不同的实现，如选取最受欢迎的条目加入备选池
@作者：张家浩
@时间：2017=06-07 11：00
'''
def select_negative_sample(one_user_item:dict(), neg_num, item_pool:dict()):
    x = 1  # 记录user中的条目数
    my_key = dict()  # 记录每个用户的条目
    ret = dict()  # 返回随机采集的结果
    y = 0
    for key in one_user_item.keys():
        my_key[x] = key
        x += 1
    # 循环，找到neg_num个负样本集
    for n in range(0, 3 * len(my_key)):
        if y >= neg_num:
            break
        x = random.randint(1, len(my_key))
        if my_key[x] not in ret.keys() and one_user_item[my_key[x]] == 0:
            # print(x+1, my_key[x+1], ret[my_key[x+1]], end=' ')
            ret[my_key[x]] = 0
            y += 1
    # print (ret)
    return ret
'''
@功能：对某个用户采集负样本过程，返回正负样本集
@参数：user_positive代表某个用户的正样本集
@参数：neg_num代表需要采集的正样本数目
@参数：item_pool 代表备选条目池，备选条目的筛选可以有不同的实现，如选取最受欢迎的条目加入备选池
@参数：item_pool_len 个数
@作者：张家浩
@时间：2017-06-07 11：00
'''
def select_negative_sample2(user_positive:dict(), neg_num, item_pool, item_pool_len):
    my_key = dict()  # 记录每个用户的条目
    ret = dict()  # 返回随机采集的结果
    y = 0
    # print("item_pool")
    # print(item_pool)
    for k in range(0, item_pool_len):
        # print(y, end=' ')
        if y >= neg_num:
            break
        x = random.randint(0, item_pool_len-1)
        if item_pool[x] not in user_positive.keys() and item_pool[x] not in ret.keys():
            ret[item_pool[x]] = 0
            y += 1
    return ret
    # train_file = "C:\\Users\\JACO\\Desktop\\ml-100k\\u1.base"
    # item_num = 1682
    # sample_num = 500
    # itemselect_item_pool(train_file, item_num, sample_num)

'''
@功能：采集负样本池，如果 评分 >= 3，就认为用户对该条目有兴趣
@参数：train_file 文件 训练集
@参数：item_num 条目总和
@参数：sample_num 负样本集合元素个数(池子中元素个数)
'''
def select_item_pool(train_file, item_num, sample_num):
    # 初始化每个条目被用户青睐的个数，初始化为0
    item_dict = dict()
    for x in range(1, item_num + 1):
        item_dict[x] = 0
    # 读取文件（训练集）中每个条目
    fo = open(train_file, "r")
    line = fo.readline()
    while line:
        str = line.split("	")
        # x = int(str[0])  # 用户id
        y = int(str[1])  # 条目id
        z = int(str[2])  # 评价
        if z >= 3:
            item_dict[y] += 1
        line = fo.readline()
    fo.close()

    # 对条目按照青睐数（受欢迎度）进行排序
    sort_items = item_dict.items()
    backitems = [[v[1], v[0]] for v in sort_items]
    backitems.sort()
    backitems.reverse()
    my_list = [backitems[i][1] for i in range(0, len(backitems))]

    ret = list()
    ret = my_list[0 : sample_num]

    return ret
'''
测试
'''
# result = init_model.init_user_item("C:\\Users\\JACO\\Desktop\\ml-100k\\u1.base", 943, 1682)
# print(select_item_pool("C:\\Users\\JACO\\Desktop\\ml-100k\\u1.base", 1682, 10))

'''
测试：
'''
'''
result = dict()
result = init_model.init_user_item("C:\\Users\\JACO\\Desktop\\ml-100k\\u1.base", 943, 1682)
dict1 = dict()
dict1 = select_positive_sample(result[1], 20)

dict2 = dict()
dict2 = select_negative_sample(result[1], 20, result[2])

dict3 = dict()
dict3 = dict1.copy()
dict3.update(dict2)
print (dict3)
'''


