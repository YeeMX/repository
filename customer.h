#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "utils.h"


/*
* 顾客类
*/
class Customer
{
private:
    bool isVip;          //是否为vip
    int temporaryNumber; //临时编号
    int waitTime;   //等待时间
public:
    Customer();
    Customer(bool isVip,int temporaryNumber);
    void setIsVip(bool isVip);
    void setTemporaryNumber(int temporaryNumber);
    string getStringNumber();
    int getNumber();
    int getWaitTime();
};

#endif // CUSTOMER_H
