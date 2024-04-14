#ifndef BUSINESSWINDOW_H
#define BUSINESSWINDOW_H


#include "utils.h"
#include "customer.h"
/*
* 业务窗口类
*/
class BusinessWindow
{
private:
    bool isVip;   //是否为VIP
    bool isNull; //是否为空
    int number; //窗口编号
    Customer *customer; //正在办理业务的顾客
    int evaluateSum; //评价总分
    int evaluateTime; //评价次数
public:
    BusinessWindow();
    BusinessWindow(int isVip, int number, int evaluateTime, int evaluateSum);
    void setIsNull(bool isNull);
    void setNumber(int number);
    void setCustomer(Customer *customer);
    void setEvaluate(int evaluate);
    string getStringNumber();
    Customer* getCustomer();
    bool getIsNull();
    int getEvaluateSum();
    int getEvaluateTime();
    string getEvaluate();
};

#endif // BUSINESSWINDOW_H
