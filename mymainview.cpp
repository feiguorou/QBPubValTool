#include "mymainview.h"
#include <iostream>
#include <QIcon>
#include <QListView>
#include <QSize>
#include <QFont>
#include <Qt>
#include <mysql.h>
#include <QDebug>

MyMainView::MyMainView(QWidget *parent)
    : QMainWindow(parent)
{
//    setGeometry(100, 100, 500, 500);
//    this->setStyleSheet("border-image: url(:/icon/background.jpg)");
    this->setStyleSheet("background-color: #222222");
    initTab();

}

MyMainView::~MyMainView()
{

}

void MyMainView::initTab()
{
    mainTab = new QTabWidget();

    QFile file(":/myqss/qtab.css");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
//    qDebug() << "样式：" << stylesheet;
    file.close();

    mainTab->setStyleSheet(stylesheet);
    //create first tab view
    initRecoWidget();
    initSearchWidget();

    QLabel *pubsub = new QLabel("pubsub tab");
    QLabel *evaluate = new QLabel("evaluate tab");

    mainTab->addTab(retrieve, "信息检索(S)");
    mainTab->addTab(pubsub, "发布/订阅(D)");
    mainTab->addTab(recoWidget, "智能推送(R)");
    mainTab->addTab(evaluate, "模块评估(E)");

    this->setCentralWidget(mainTab);
    this->resize(800, 600);
    this->setMinimumWidth(500);
    this->setWindowTitle("情报分发模型分析设计验证工具");
    this->setWindowIcon(QIcon(":/icon/icon.png"));
}

/**
 * @brief MyMainView::initSearchWidget 初始化检索模块
 */
void MyMainView::initSearchWidget()
{
   retrieve = new QWidget();
   searchTotalLayout = new QVBoxLayout();  //总布局
   searchAboveLayout = new QVBoxLayout();  //上部布局
   searchAboveSubLayout1 = new QHBoxLayout();  //上部布局第一行
   checkBoxLayout = new QHBoxLayout();  //上部布局第二行
   searchAboveSubLayout2 = new QHBoxLayout();  //上部布局第三行
   searchTableWidget = new QTableWidget();  //下部布局（table布局）
   //************上部布局第一行
   //主题
   themeLabel = new QLabel("主题");
   themeComboBox = new QComboBox();
   themeComboBox->setView(new QListView);
   themeComboBox->addItem("全部");
   themeComboBox->addItem("战斗机");
   themeComboBox->addItem("燃料");
   themeComboBox->addItem("气候");
   themeComboBox->addItem("武器");
   //设置“主题”组件的格式
   themeLabel->setStyleSheet(THEME_LABEL_STYLE);
   themeComboBox->setStyleSheet(comcoBoxStyle);
   //起始时间
   startTimeLabel = new QLabel("起始时间");
   startDateTimeEdit = new QDateTimeEdit();
   startDateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
   //设置“起始时间”组件格式
   startTimeLabel->setStyleSheet("color:white;min-width:50px; max-width:50px;");
   startDateTimeEdit->setMaximumWidth(150);
   //结束时间
   endTimeLabel = new QLabel("结束时间");
   endDateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime());
   endDateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
   //设置“结束时间”组件格式
   endTimeLabel->setStyleSheet("color:white;min-width:50px; max-width:50px;");
   endDateTimeEdit->setMaximumWidth(150);
   //将第一行组件加入searchAboveSubLayout1布局中
   searchAboveSubLayout1->addWidget(themeLabel);
   searchAboveSubLayout1->addWidget(themeComboBox);
   searchAboveSubLayout1->addWidget(startTimeLabel);
   searchAboveSubLayout1->addWidget(startDateTimeEdit);
   searchAboveSubLayout1->addWidget(endTimeLabel);
   searchAboveSubLayout1->addWidget(endDateTimeEdit);
   //*************上部布局第二行
   //“全部”按钮复选框
   allCheckBox = new QCheckBox("全部");
   allCheckBox->setChecked(true);
   checkBoxArray[0] = new QCheckBox("文字");
   checkBoxArray[1] = new QCheckBox("图片");
   checkBoxArray[2] = new QCheckBox("音频");
   checkBoxArray[3] = new QCheckBox("视频");
   //allCheckBox复选框信号槽
   connect(allCheckBox, SIGNAL(stateChanged(int)), this, SLOT(selectAllTypes(int)));
   //其他按钮复选框信号槽
   for(int i = 0; i < 4; i++)
   {
        connect(checkBoxArray[i], SIGNAL(clicked()), this, SLOT(chkChanged()) );
   }
   //将第二行组件加入checkBoxLayout布局中
   checkBoxLayout->addWidget(checkBoxArray[0]);
   checkBoxLayout->addWidget(checkBoxArray[1]);
   checkBoxLayout->addWidget(checkBoxArray[2]);
   checkBoxLayout->addWidget(checkBoxArray[3]);
   checkBoxLayout->addWidget(allCheckBox);
   //设置布局格式
   checkBoxLayout->setContentsMargins(70,0,70,10);
   //**********上部布局第三行
   //搜索
   //检索类型
   searchComboBox = new QComboBox();
   searchComboBox->setView(new QListView);
   searchComboBox->addItem("全面检索");
   searchComboBox->addItem("标题");
   searchComboBox->addItem("内容");
   searchComboBox->addItem("发布源");
   //设置格式
   searchComboBox->setMinimumWidth(100);
   searchComboBox->setMaximumWidth(100);
   searchComboBox->setStyleSheet(comcoBoxStyle);  //  COMBOBOX_STYLE
   //搜索框
   searchLineEdit = new QLineEdit(this);
   //搜索按钮
   searchPushButton = new QPushButton("检索");
   searchPushButton->setCursor(QCursor(Qt::PointingHandCursor));
   //搜索按钮信号槽
   connect(searchPushButton, SIGNAL(clicked()), this, SLOT(searchAction()));
   //设置格式
   searchLineEdit->setStyleSheet(TEXT_SEARCH_STYLE1);
   searchPushButton->setStyleSheet(BTN_SEARCH_STYLE1);
   //将第三行组件加入checkBoxLayout布局中
   searchAboveSubLayout2->addWidget(searchComboBox);
   searchAboveSubLayout2->addWidget(searchLineEdit);
   searchAboveSubLayout2->addWidget(searchPushButton);
   searchAboveSubLayout2->setContentsMargins(50,10,50,10);
   //将三行布局加入到searchAboveLayout布局中
   searchAboveLayout->addLayout(searchAboveSubLayout1);
   searchAboveLayout->addLayout(checkBoxLayout);
   searchAboveLayout->addLayout(searchAboveSubLayout2);
   //****************下部布局
   //设置表格
   searchTableWidget->setColumnCount(6);
   for(int i = 0; i < 6; i++)
   {
    searchTableWidget->setColumnWidth(i,125);
   }
   //设置表头
   QStringList header;
   header << tr("主题") << tr("标题") << tr("时间") << tr("情报来源") << tr("情报形式") << tr("浏览");
   searchTableWidget->setHorizontalHeaderLabels(header);
   searchTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格内容不可以修改
   searchTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//表格选择为整行
   //***************全部布局
   searchTotalLayout->addLayout(searchAboveLayout);
   searchTotalLayout->addWidget(searchTableWidget);
   retrieve->setLayout(searchTotalLayout);
}


/**
 * @brief MyMainView::searchAction查询功能，没有对异常进行处理
 * @author jaco
 * @date 2017-06-07 09:30
 */
void MyMainView::searchAction()
{
    //建立连接
    MySql mySql;
    QSqlQuery query = mySql.myConnet();
    QString Sql_one = "SELECT * FROM qb_basic";  //查询语句前缀
    QString themeText = themeComboBox->currentText();  //主题
    QString searchTypeText = searchComboBox->currentText();  //查询形式
    QString startTime = startDateTimeEdit->text();  //起始时间
    QString endTime = endDateTimeEdit->text();  //终止时间
    QStringList qStringList = searchLineEdit->text().split(" "); //检索框内容

    //主题
    QString myThemeQuery = "";
    if(themeText != "全部")
    {
        myThemeQuery = " AND theme = '" + themeText + "' ";
    }
    //时间
    QString myTimeQuery = " AND time >= '" + startTime + "' AND time <= '" + endTime + "' ";
    //多选框
    QString formCheckBoxQuery = "";
    //没有选择“全部”复选框
    if(!allCheckBox->checkState())
    {
        formCheckBoxQuery = " AND ";
        if(checkBoxArray[0]->checkState())
        {
            formCheckBoxQuery += " form = 'doc' OR ";
        }
        if(checkBoxArray[1]->checkState())
        {
            formCheckBoxQuery += " form = 'image' OR ";
        }
        if(checkBoxArray[2]->checkState())
        {
            formCheckBoxQuery += " form = 'audio' OR ";
        }
        if(checkBoxArray[3]->checkState())
        {
            formCheckBoxQuery += " form = 'video' OR ";
        }
        formCheckBoxQuery = formCheckBoxQuery.left(formCheckBoxQuery.length()-3);

    }
    //第三行：检索形式
    if(searchTypeText == "标题")
    {
        QString myTitleQuery = "";
        myTitleQuery = " WHERE title like '%" + qStringList.at(0) + "%' ";
        int titleLen = qStringList.length();
        for(int i = 1; i < titleLen; i++)
        {
            myTitleQuery += " OR title like '%" + qStringList.at(i) + "%'";
        }
        Sql_one += myTitleQuery + myThemeQuery + myTimeQuery + formCheckBoxQuery;
    }
    else if(searchTypeText == "发布源")
    {
        QString myAuthorQuery = "";
        myAuthorQuery = " WHERE author like '%" + qStringList.at(0) + "%' ";
        int authorLen = qStringList.length();
        for(int i = 1; i < authorLen; i++)
        {
            myAuthorQuery += " OR author like '%" + qStringList.at(i) + "%'";
        }
        Sql_one += myAuthorQuery + myThemeQuery + myTimeQuery + formCheckBoxQuery;
    }
    else if(searchTypeText == "内容")
    {

       //*********基于内容的搜索，使用分词工具每一条情报进行分词，并存储在相应的数据库表中进行查询
    }
    else if(searchTypeText == "全面检索")
    {
        //标题
        QString myTitleQuery = " WHERE (title like '%" + qStringList.at(0) + "%'";
        int myTitleLen = qStringList.length();
        for(int i = 1; i < myTitleLen; i++)
        {
            myTitleQuery += " OR title like '%" + qStringList.at(i) + "%'";
        }
        //作者（发布源）
        QString myAuthorQuery = " OR author like '%" + qStringList.at(0) + "%'";
        int myAuthorLen = qStringList.length();
        for(int i = 1; i < myAuthorLen; i++)
        {
            myAuthorQuery += " OR author like '%" + qStringList.at(i) + "%'";
        }
        myAuthorQuery += " ) ";
        Sql_one += myTitleQuery + myAuthorQuery + myThemeQuery + myTimeQuery + formCheckBoxQuery;
    }
    //获取查询结果
    result = mySql.mySelect(query, Sql_one);
    //结果个数
    int len = result.length();
    int myTableCount = searchTableWidget->rowCount();
    //将之前的查询结果删除
    for(int i = 0; i < myTableCount; i++)
    {
        searchTableWidget->removeRow(i);
    }
    //列数
    int rowNum = result.size();
    //设置表格列数
    searchTableWidget->setRowCount(rowNum);
    //在表格中添加查询内容
    QStringList oneList;
    for(int i = 0; i < len; i++)
    {
        searchReadBtn = new QPushButton(QIcon(":/icon/icon.png"),tr("浏览"));
        searchReadBtn->setStyleSheet(SEARCH_BUTTON_READ_STYLE1);
        searchReadBtn->setCursor(QCursor(Qt::PointingHandCursor));
        //**********************添加整行
        oneList = result[i].split(" ");
        searchTableWidget->setItem(i, 0, new QTableWidgetItem(oneList[5]));
        searchTableWidget->setItem(i, 1, new QTableWidgetItem(oneList[1]));
        searchTableWidget->setItem(i, 2, new QTableWidgetItem(oneList[2]));
        searchTableWidget->setItem(i, 3, new QTableWidgetItem(oneList[3]));
        searchTableWidget->setItem(i, 4, new QTableWidgetItem(oneList[4]));
        searchTableWidget->setCellWidget(i, 5, searchReadBtn);
    }
}
/**
 * @brief MyMainView::selectAllTypes上部布局第二行 槽：对“全部”复选框
 * @param state
 */
void MyMainView::selectAllTypes(int state)
{

    if(state == 0)
    {
        qDebug() << "没有选择全部";
    }
    else
    {
        qDebug() << "选择了全部";
        for(int i = 0; i < 4; i++)
        {
            checkBoxArray[i]->setChecked(false);
        }
    }
}
/**
 * @brief MyMainView::chkChanged上部布局第二行 槽：对其余“复选框”
 */
void MyMainView::chkChanged()
{
    allCheckBox->setChecked(false);
    //int len = sizeof(checkBoxArray);
    //int len = result.length();
    for(int i = 0; i < 4; i++)
    {
        if(checkBoxArray[i]->checkState())
        {

            qDebug() << "选择复选框：" << checkBoxArray[i]->text();
        }
    }
}
/**
 * @brief MyMainView::filterTypes
 * @弃用
 */
void MyMainView::filterTypes()
{
    QStringList typeList;
    QVector<QString> filterResult;
    if(allCheckBox->checkState())
    {
        qDebug() << "全部，不用筛选";
    }
    else
    {
        for(int i = 0; i < 4; i++)
        {
            if(checkBoxArray[i]->checkState())
            {
                switch (i)
                {
                    case 0:  typeList.append("doc");
                        break;
                    case 1:  typeList.append("image");
                        break;
                    case 2:  typeList.append("audio");
                        break;
                    case 3:  typeList.append("video");
                        break;
                    default:
                        break;
                }
            }
        }

        qDebug() << typeList;
    }
}

void MyMainView::initRecoWidget()
{
    recoWidget = new QWidget();
    //the total layout
    totalLayout = new QVBoxLayout();

    //the first horizontal layout
    aboveLayout = new QHBoxLayout();
    lab_abox = new QLabel("选择您想使用的推荐算法：");
    lab_abox->setFont(QFont("微软雅黑", 15));
    cb_abox = new QComboBox();
    cb_abox->setStyleSheet(COMBOBOX_STYLE);
    cb_abox->setView(new QListView());
    cb_abox->addItem("UserCFAlgorithm");
    cb_abox->addItem("ItemCFAlgorithm");
    cb_abox->addItem("LFMAlgorithm");
    btn_choose_abox = new QPushButton("选定");
    btn_refresh_abox = new QPushButton("刷新");
    connect(btn_choose_abox, SIGNAL(clicked()), this, SLOT(chooseAlgorithm()));
    btn_choose_abox->setStyleSheet(BTN_CHOOSE_STYLE);;
    btn_refresh_abox->setStyleSheet(BTN_REFRESH_STYLE);
    aboveLayout->addWidget(lab_abox);
    aboveLayout->addWidget(cb_abox);
    aboveLayout->addWidget(btn_choose_abox);
    aboveLayout->addWidget(btn_refresh_abox);

    //the second vertical layout
    mediumLayout = new QVBoxLayout();
    lab_mbox = new QLabel("当前使用的推荐算法： " + cb_abox->currentText());
    lab_mbox->setFont(QFont("微软雅黑", 15));
    lab_hint_mbox = new QLabel("推荐结果：根据您选定的推荐算法，您可能想要阅读以下情报信息");
    lab_hint_mbox->setFont(QFont("微软雅黑", 15));
    mediumLayout->addWidget(lab_mbox);
    mediumLayout->addWidget(lab_hint_mbox);

    //the third bottom layout
    qbListWidget = new QListWidget();
    qbListWidget->setResizeMode(QListView::Adjust);
    qbListWidget->setAutoScroll(true);

    int margin = qbListWidget->width() / 10;

    for(int i = 0; i < 20; i++){
        wContainer = new QWidget();
        bottomLayout = new QHBoxLayout(wContainer);
        qbListWidget->setStyleSheet(LISTWIDGET_STYLE);
        qbTitle = new QLabel(tr("【这是一条推荐的情报】"));
        qbTitle->setFont(QFont("微软雅黑", 15));
        readBtn = new QPushButton(QIcon(":/icon/icon.png"),tr("阅读"));
        readBtn->setStyleSheet(BUTTON_READ_STYLE);
        bottomLayout->addWidget(qbTitle);
        bottomLayout->addStretch(1);//split the blank space into mean pieces
        bottomLayout->addWidget(readBtn);
        bottomLayout->setContentsMargins(margin,0,margin,0);
        qbItem = new QListWidgetItem(qbListWidget);
        qbItem->setSizeHint(QSize(50, 50));
        qbListWidget->setItemWidget(qbItem, wContainer);
    }

    //add all layout into totalLayout
    totalLayout->addLayout(aboveLayout);
    totalLayout->addLayout(mediumLayout);
    totalLayout->addWidget(qbListWidget);
    totalLayout->setStretchFactor(aboveLayout, 2);
    totalLayout->setStretchFactor(mediumLayout, 2);
    totalLayout->setStretchFactor(qbListWidget, 6);
    recoWidget->setLayout(totalLayout);
}

void MyMainView::chooseAlgorithm()
{
    lab_abox->setText(cb_abox->currentText());
}
