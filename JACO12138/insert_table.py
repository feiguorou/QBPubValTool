import pymysql
import time
'''
@功能：数据库中插入 用户数 条目数 评价数目
'''
def insert_num_info():
    file_info = "ml-100k/u.info"
    fo = open(file_info, "r")
    # 用户数
    user_num = int(fo.readline().split(" ")[0])
    # 条目数
    item_num = int(fo.readline().split(" ")[0])
    # 评价数
    rating_num = int(fo.readline().split(" ")[0])
    # 打开数据库
    db = pymysql.connect("127.0.0.1", "root", "1351", "qb_db")
    # 使用cursor() 方法创建一个游标对象
    my_cursor = db.cursor()
    try:
        # 清空info_num表数据
        my_cursor.execute("DELETE FROM info_num")
        num_info = "INSERT INTO info_num (user_num, item_num, rating_num) VALUES ('%d','%d','%d')" % (user_num, item_num, rating_num)
        my_cursor.execute(num_info)
        db.commit()
        data = my_cursor.rowcount
        if data == 1:
            print("info_num插入成功")
        else:
            print("info_num插入失败")
    except Exception as myerr:
        print(myerr)
        db.rollback()
    db.close()
# insert_num_info()

'''
@功能：向数据库中插入训练集
'''
def insert_info_rating():
    # 打开数据库
    db = pymysql.connect("127.0.0.1", "root", "1351", "qb_db")
    # 使用cursor() 方法创建一个游标对象
    my_cursor = db.cursor()
    my_cursor.execute("DELETE FROM info_rating")
    file_base = "ml-100k/u1.base"
    fo = open(file_base, "r")
    line = fo.readline()
    sum_rating = 0
    while line:
        one_user_item_eva = line.split("	")
        userid = one_user_item_eva[0]  # 用户id
        itemid = one_user_item_eva[1]  # 条目id
        rating = int(one_user_item_eva[2])  # 评价
        if rating > 2:
            rating = 1
        else:
            rating = 0
        rating_time = float(one_user_item_eva[3])  #评价时间（以秒计）
        my_localtime = time.localtime(rating_time) #  时间转化为一般时间格式:
        # time.struct_time(tm_year=1998, tm_mon=3, tm_mday=1,
        # tm_hour=3, tm_min=1, tm_sec=5, tm_wday=6, tm_yday=60, tm_isdst=0)
        format_time = time.strftime("%Y-%m-%d %H:%M:%S", my_localtime)  # 一般时间格式转化为自定义格式
        #  生成sql语句
        insert_rating_info_sql = "INSERT INTO info_rating (userid, itemid, rating, rating_time) VALUES ('%s','%s','%d', '%s')" % (userid, itemid, rating, format_time)
        my_cursor.execute(insert_rating_info_sql)
        result = my_cursor.rowcount  # 插入结果：0失败 1成功
        if result != 1:
            print(insert_rating_info_sql)
        sum_rating += result
        line = fo.readline()
    db.commit()  # 提交
    print("info_rating插入条数：", sum_rating)
# insert_info_rating()

'''
@功能：向数据库中插入训练集
'''
def insert_info_rating_test():
    # 打开数据库
    db = pymysql.connect("127.0.0.1", "root", "1351", "qb_db")
    # 使用cursor() 方法创建一个游标对象
    my_cursor = db.cursor()
    my_cursor.execute("DELETE FROM info_rating_test")
    file_test = "ml-100k/u1.test"
    fo = open(file_test, "r")
    line = fo.readline()
    sum_ratirng = 0
    while line:
        one_user_item_eva = line.split("	")
        userid = one_user_item_eva[0]  # 用户id
        itemid = one_user_item_eva[1]  # 条目id
        rating = int(one_user_item_eva[2])  # 评价
        if rating > 2:
            rating = 1
        else:
            rating = 0
        rating_time = float(one_user_item_eva[3])  #评价时间（以秒计）
        my_localtime = time.localtime(rating_time) #  时间转化为一般时间格式:
        # time.struct_time(tm_year=1998, tm_mon=3, tm_mday=1,
        # tm_hour=3, tm_min=1, tm_sec=5, tm_wday=6, tm_yday=60, tm_isdst=0)
        format_time = time.strftime("%Y-%m-%d %H:%M:%S", my_localtime)  # 一般时间格式转化为自定义格式
        #  生成sql语句
        insert_rating_info_sql = "INSERT INTO info_rating_test (userid, itemid, rating, rating_time) VALUES ('%s','%s','%d', '%s')" % (userid, itemid, rating, format_time)
        my_cursor.execute(insert_rating_info_sql)
        result = my_cursor.rowcount  # 插入结果：0失败 1成功
        if result != 1:
            print(insert_rating_info_sql)
        sum_ratirng += result
        line = fo.readline()
    db.commit()  # 提交
    print("info_rating_test插入条数：", sum_ratirng)
# insert_info_rating_test()

def insert_info_item():
    # 打开数据库
    db = pymysql.connect("127.0.0.1", "root", "1351", "qb_db")
    # 使用cursor() 方法创建一个游标对象
    my_cursor = db.cursor()
    my_cursor.execute("DELETE FROM info_item")
    file_test = "ml-100k/u.item"
    fo = open(file_test, "r", encoding="ISO8859-1")
    line = fo.readline()
    one_item = ""
    while line:
        one_item = line.split("|")
        if "'" in one_item[1]:
            one_item[1] = one_item[1].replace("'", "''")
        sql = "INSERT INTO info_item (id ,name, time_pub) VALUES ('%s', '%s', '%s')" % (str(one_item[0]), str(one_item[1]), str(one_item[2]))
        my_cursor.execute(sql)
        line = fo.readline()
    db.commit()
    my_cursor.close()
    fo.close()
