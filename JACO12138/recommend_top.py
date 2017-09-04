import predict
import pymysql
import time
'''
@功能：计算每个用户的对每个条目的兴趣度，并按从高到底的顺序排序
@参数： result: user_class 和 item_class 结果
@参数： topN: 推荐topN个条目给用户
@参数： user_num 用户数  item_num 条目数
'''
def recommend_top(result:dict(), topN, user_num, item_num):
    user_item_r = dict()  # 推荐结果
    user_item = dict()  # 计算兴趣度结果
    user_class = result[0]
    item_class = result[1]
    fo = open("ml-100k/result/user_item_interest.txt", "w")
    for x in range(1, user_num+1):
        user_item[x] = dict()
        for y in range(1, item_num+1):
            user_item[x][y] = predict.predict(x, y, user_class[x], item_class[y])
            fo.write(str(x) + " " + str(y) + " " + str(user_item[x][y]))
            fo.write("\n")
    # 对每个用户按照对条目的兴趣度进行排序
    for x in user_item.keys():
        one_user_item = user_item[x].items()
        # sort_items = item_dict.items()
        backitems = [[v[1], v[0]] for v in one_user_item]
        backitems.sort()
        backitems.reverse()
        rec = list()
        rec = [backitems[i][1] for i in range(0, len(backitems))]
        user_item_r[x] = rec[0:topN]
    fo = open("ml-100k/result/user_item_rec.txt", "w")
    for x in user_item_r.keys():
        fo.write(str(x))
        fo.write("\n")
        for y in user_item_r[x]:
            fo.write(str(y) + ",")
        fo.write("\n")
    #  将推荐结果user_item_r存入数据库中
    # 打开数据库
    db = pymysql.connect("127.0.0.1", "root", "1351", "qb_db")
    # 使用cursor() 方法创建一个游标对象
    my_cursor = db.cursor()
    my_cursor.execute("DELETE FROM info_rec")
    rec_time = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    for x in user_item_r.keys():
        str(x)
        for y in user_item_r[x]:
            sql = "INSERT INTO info_rec (id, itemid, rec_time) VALUES ('%s', '%s', '%s')" % (str(x), str(y), str(rec_time))
            my_cursor.execute(sql)
    db.commit()
    return user_item_r
