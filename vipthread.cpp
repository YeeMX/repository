#include "vipthread.h"

VipThread::VipThread(QObject *parent):QObject(parent)
{
}

VipThread::~VipThread(){}

void VipThread::transactionProcessing(Function *function)
{
    qDebug()<<"线程开始VIP";
    do{
        Customer *customer = function->vipWait->deQueue();
        if(customer == NULL){
            qDebug()<<"无等待人员，叫号失败";
            break;
        }
        function->vipWaitNumber--;
        emit sendNumOfLine(function->vipWaitNumber);
        function->vipWin->setCustomer(customer);
        emit sendNum(customer->getNumber());

        QThread::sleep(customer->getWaitTime());
        int evaluate = random(4,5);
        function->vipWin->setEvaluate(evaluate);



    }while(function->vipWait->getFront()->data != NULL);
    qDebug()<<"排队模拟完成";
    emit endSignal();
}
