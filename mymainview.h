#ifndef MYMAINVIEW_H
#define MYMAINVIEW_H

#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include <QTabWidget>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QDateTimeEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QFile>

class MyMainView : public QMainWindow
{
    Q_OBJECT

public:
    MyMainView(QWidget *parent = 0);
    ~MyMainView();
private:
    //tabwidget
    QTabWidget *mainTab;
    QWidget *recoWidget;
    QWidget *retrieve;
    /**
     * @brief 检索模块
     * @author JACO
     */
    QVBoxLayout *searchTotalLayout;
    QVBoxLayout *searchAboveLayout;
    QHBoxLayout *searchAboveSubLayout1;
    QHBoxLayout *searchAboveSubLayout2;
    QVBoxLayout *searchMediumLayout;
    QHBoxLayout *searchhBottomLayout;
    QLabel *themeLabel;
    QComboBox *themeComboBox;
    QComboBox *searchComboBox;
    QPushButton *searchPushButton;
    QLineEdit *searchLineEdit;
    QLabel *searchLabel;
    QListWidget *searchlistWidget;
    QWidget *searchContainer;
    QLabel *searchQbTitle;
    QPushButton *searchReadBtn;
    QListWidgetItem *searchQbItem;
    QHBoxLayout *checkBoxLayout;
    QCheckBox *allCheckBox;
    QCheckBox *checkBoxArray[4];
    //*************************


    QLabel *startTimeLabel;
    QLabel *endTimeLabel;
    QDateTimeEdit *startDateTimeEdit;
    QDateTimeEdit *endDateTimeEdit;
    QTableWidget *searchTableWidget;
    QVector<QString> result;


    QVBoxLayout *totalLayout;
    QHBoxLayout *aboveLayout;
    QLabel *lab_abox;
    QComboBox *cb_abox;
    QPushButton *btn_choose_abox;
    QPushButton *btn_refresh_abox;
    QVBoxLayout *mediumLayout;
    QLabel *lab_mbox;
    QLabel *lab_hint_mbox;
    QListWidget *qbListWidget;
    QWidget *wContainer;
    QHBoxLayout *bottomLayout;
    QLabel *qbTitle;
    QPushButton *readBtn;
    QListWidgetItem *qbItem;

    //style
    QString BUTTON_READ_STYLE ="QPushButton{height: 40px; width: 80px; background-color: rgb(46, 195, 231); font-family: 微软雅黑;font-size: 12pt; color: white; border-radius: 10px; border: 1px groove gray;border-style: outset;}""QPushButton:hover{background-color:white; color: black;}""QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset;}";
    QString LISTWIDGET_STYLE = "QListWidget{background-color:rgb(245, 245, 220);color:rgb(255, 250, 250);border: 1px solid rgb(63, 63, 60);}""QListWidget::item:hover{background-color:white;}""QListWidget::item:selected{background-color:rgb(85, 170, 255);}""QListWidget::item{border: 1px solid rgb(63, 63, 60);}";
    QString COMBOBOX_STYLE = "width: 80px;height: 35px;font-family: TimeNewRomans;font-size: 12pt;border: 1px solid black;background-color: rgb(255, 255, 250);color: rgb(48, 48, 48);";
    QString BTN_CHOOSE_STYLE = "QPushButton{height: 40px; width: 80px;background-color: rgb(46, 195, 231); font-family: 微软雅黑;font-size: 12pt;color: white; border-radius: 10px; border: 1px groove gray;border-style: outset;}""QPushButton:hover{background-color:white; color: black;}""QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset;}";
    QString BTN_REFRESH_STYLE = "QPushButton{height: 40px; width: 80px;background-color: rgb(46, 195, 231); font-family: 微软雅黑;font-size: 12pt;color: white; border-radius: 10px; border: 1px groove gray;border-style: outset;}""QPushButton:hover{background-color:white; color: black;}""QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset;}";
    /**
      *@author JACO
      */
    QString THEME_LABEL_STYLE = "color:white;min-width:25px; max-width:25px";
    QString comcoBoxStyle = "QComboBox{  min-width:6em; max-width:6em;height: 20px; border:1px solid gray;  border-radius:3px;  padding: 5px;\
                                        color:black; background-color:white}\
            QComboBox::drop-down{subcontrol-origin:padding; subcontrol-position:top right; width:20px; border-left-width:1px;\
                                 border-left-color:darkgray; border-left-style:solid; border-top-right-radius:3px;\
                                 border-bottom-right-radius:3px;color:black; background-color:white}\
            QComboBox QAbstractItemView{border: 2px solid #4E6D8C; color:black; background-color:white}\
            QComboBox::down-arrow{color: green}";
    QString TEXT_SEARCH_STYLE = "QLineEdit{width: 200px; height:40px; background-color: rgb(230, 230, 230); font-family: 微软雅黑; font-size: 12pt; color: black; border-radius: 10px; border: 1px groove gray; border-style: outset;}""QLineEdit:focus{background-color:white}";
    QString BTN_SEARCH_STYLE = "QPushButton{height: 40px; width: 80px;background-color: rgb(46, 195, 231); font-family: 微软雅黑;font-size: 12pt;color: white; border-radius: 10px; border: 1px groove gray;border-style: outset;}""QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset;}";
    QString SEARCH_LISTWIDGET_STYLE = "QListWidget{background-color:rgb(245, 245, 220);color:rgb(255, 250, 250);border: 1px solid rgb(63, 63, 60);}""QListWidget::item:hover{background-color:white;}""QListWidget::item:selected{background-color:rgb(85, 170, 255);}""QListWidget::item{border: 1px solid rgb(63, 63, 60);}";
    QString SEARCH_BUTTON_READ_STYLE ="QPushButton{height: 40px; width: 80px; background-color: rgb(46, 195, 231); font-family: 微软雅黑;font-size: 12pt; color: white; border-radius: 10px; border: 1px groove gray;border-style: outset;}""QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset;}";


    QString BTN_SEARCH_STYLE1 = "QPushButton {height: 30px; width: 80px;background-color: #2E2F30; font-family: 微软雅黑;font-size: 12pt;"
                                             "color: white; border-radius: 3px; border: 1px groove gray;border-style: outset;}"
                                "QPushButton:pressed {color: green;background-color:rgb(85, 170, 255);border-style: inset;}"
                                "QPushButton:hover {color: green ;background-color: white}"; // #2E2F30
    QString TEXT_SEARCH_STYLE1 = "QLineEdit{width: 200px; height:30px; background-color: rgb(230, 230, 230); font-family: 微软雅黑; font-size: 12pt; color: black; border-radius: 3px; border: 1px groove gray; border-style: outset;}""QLineEdit:focus{background-color:white}";
    QString LISTWIDGET_STYLE1 = "QListWidget{background-color: #2E2F30;color:rgb(255, 250, 250);border: 1px solid rgb(63, 63, 60);}" //rgb(245, 245, 220)
                            "QListWidget::item{border: 1px solid rgb(63, 63, 60);}"
                            "QListWidget::item:hover{background-color:white;}"
                            "QListWidget::item:selected{background-color:rgb(85, 170, 255);}"
                 "QScrollBar:vertical { background: #4A4B4D;}"
                 "QScrollBar::handle:vertical { background: #525456;}"
                 "QScrollBar::add-line:vertical {border: 2px solid blue; background: green; height: 20px; subcontrol-position: bottom;subcontrol-origin: margin;}"
                 "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical { border: 2px solid grey; width: 3px;height: 3px;background:}";
    QString SEARCH_BUTTON_READ_STYLE1 = "QPushButton {height: 20px; width: 60px;background-color: #2E2F30; font-family: 微软雅黑;font-size: 10pt;"
                                             "color: white; border-radius: 3px; border: 1px groove gray;border-style: outset;}"
                                "QPushButton:pressed {color: green;background-color:rgb(85, 170, 255);border-style: inset;}"
                                "QPushButton:hover {color: green ;background-color: white}"; // #2E2F30

private slots:
    void chooseAlgorithm();
    /**
     * @brief searchTypeChanged
     * @author JACO
     */
    void searchAction();
    void selectAllTypes(int state);
    void chkChanged();
    void filterTypes();
signals:

private:
    void initTab(); //initialize the tab
    void initRecoWidget();
    /**
     * @brief initSearchWidget
     * @author JACO
     */
    void initSearchWidget();


};

#endif // MYMAINVIEW_H
