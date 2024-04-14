#include "businesswindow.h"

BusinessWindow::BusinessWindow(){}

BusinessWindow::BusinessWindow(int isVip, int number, int evaluateTime, int evaluateSum){
    this->isVip = isVip;
    this->number = number;
    this->customer = NULL;
    this->isNull = true;
    this->evaluateSum = evaluateSum;
    this->evaluateTime = evaluateTime;
}

void BusinessWindow::setIsNull(bool isNull){this->isNull = isNull;}
void BusinessWindow::setNumber(int number){this->number = number;}
void BusinessWindow::setCustomer(Customer *customer){this->customer = customer;this->isNull = false;}
void BusinessWindow::setEvaluate(int evaluate){evaluateSum += evaluate;evaluateTime++;}
string BusinessWindow::getStringNumber(){return to_string(number);}
Customer* BusinessWindow::getCustomer(){return customer;}
bool BusinessWindow::getIsNull(){return isNull;}
int BusinessWindow::getEvaluateSum(){return this->evaluateSum;}
int BusinessWindow::getEvaluateTime(){return this->evaluateTime;}
string BusinessWindow::getEvaluate(){
    double sum = (double)evaluateSum;
    double time = (double)evaluateTime;
    double evaluate = sum/time;
    return to_string(evaluate).substr(0,3);}
