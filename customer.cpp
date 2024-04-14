#include "customer.h"


Customer::Customer(){}

Customer::Customer(bool isVip,int temporaryNumber){
    this->isVip = isVip;
    this->temporaryNumber = temporaryNumber;
    this->waitTime = random(3,6)    //随机生成3~6秒的等待时间
}

void Customer::setIsVip(bool isVip){
    this->isVip = isVip;
}

void Customer::setTemporaryNumber(int temporaryNumber){
    this->temporaryNumber = temporaryNumber;
}

string Customer::getStringNumber(){
    return to_string(temporaryNumber);
}

int Customer::getNumber(){
    return temporaryNumber;
}

int Customer::getWaitTime(){
    return waitTime;
}
