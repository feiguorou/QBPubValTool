#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
@功能：返回一个用户对一个条目的兴趣度
@参数：u 用户id， i条目id， p表示用户与隐类的关系表， q表示条目与隐类的关系表
@作者：张家浩
@时间： 2017-06-07 15：20
'''
def predict(u, i, p, q):
    r = 0
    for f in range(1, len(p)+1):
        # print(str(p[f]), " ", str(q[i][f]))
        r += p[f] * q[f]
    return r
