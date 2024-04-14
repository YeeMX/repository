#ifndef FUNCTION_H
#define FUNCTION_H

#include <QObject>
#include <QMutex>
#include "utils.h"
#include "customer.h"
#include "queue.h"
#include "businesswindow.h"
/*
* 排队功能实现类
*/
class Function : public QObject{
    Q_OBJECT
    friend class MyMainWindow;
    friend class WinsThread;
    friend class VipWindow;
    friend class VipThread;
    friend class WelcomeWindow;
    private:
    QMutex m_mutex;
    int number;  //编号
    int numberOfLine;//排队人数
    int waitTime;   //等待时间
    int vipNumber; //vip编号
    int vipWaitNumber; //vip排队人数
    int vipWaitTime;    //vip等待时间
    Queue<Customer> *wait = NULL;   //排队等待队列
    Queue<Customer> *vipWait = NULL; //vip等候队列
    BusinessWindow *vipWin = NULL;  //Vip窗口
    mutex m;    //创建互斥锁对象
    //vector<thread> wins_thread;//线程窗口 每个线程对应下标相同的窗口
    vector<BusinessWindow> wins;//窗口
    int numOfWindow = 3;    //窗口数量
    int firstWindow = -1;   //最先完成的窗口
    bool threadFlag;    //线程提前终止的标志
    bool threadFlag2;    //线程提前终止的标志
    bool countFlag;     //倒计时终止的标志
    int winflag; //窗口标志
    vector<bool> endflag;//窗口结束标志
    bool allEndFlag;
    public:
    Function();
    ~Function();
    void getNumber();   //取号
    void getVipNumber();    //vip取号
    Customer *getCustomerNumber();   //取号(返回Customer对象)
    void callNumber();  //叫号(柜台未满时)
    void callNumber(int num);  //叫号
    void callNumberAccordingToTime(); //根据时间叫号
    void callVipNumber();//叫vip号
    void createSimulation();  //创建模拟
    void transactionProcessing(int flag);   //事务处理
    void multithreading();   //多线程
    void progressBar(int win); //进度条
    void evaluate(int win);//评价
    void save();//保存评价
    void vipWindow();   //vip窗口
    void vipThread();   //vip线程
    void commentsView(); //查看评价
    void endMenu(); //终止菜单
    void countDown();//倒计时
    void countDownVip();//vip倒计时

signals:
    void changeLabel(int l,int num);
};
#endif // FUNCTION_H
