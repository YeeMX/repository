#include "winsthread.h"
#include <QDebug>

WinsThread::WinsThread(QObject *parent):QObject(parent)
{
}
WinsThread::~WinsThread(){}

void WinsThread::transactionProcessing(int identifier,Function* function)
{
    qDebug()<<"线程开始"<<identifier;
    do{
        QThread::sleep(function->wins[identifier].getCustomer()->getWaitTime());
        if(function->threadFlag) return;
        Customer *customer = NULL;
        {
            QMutexLocker locker(&function->m_mutex);
            qDebug()<<"线程正在出队"<<identifier;
            customer = function->wait->getFront()->data;//获取将要出队的顾客对象
            if(customer == NULL){
                //QMutexLocker locker(&m_mutex);
                qDebug()<<"无等待人员，叫号失败";
                if(function->firstWindow < 0){function->firstWindow = identifier;}

                break;
            }
            function->wait->deQueue();//出队
            qDebug()<<"线程出队完成"<<identifier;

        }

        if(function->numberOfLine>0) function->numberOfLine--;//排队人数减少
        emit setNumOfLine(function->numberOfLine);//发射信号

        int evaluate = random(2,5);//随机生成评价
        function->wins[identifier].setEvaluate(evaluate);
        function->wins[identifier].setCustomer(customer);
        {
            QMutexLocker locker(&function->m_mutex);
            qDebug()<<identifier<<"号窗口正在办理业务的顾客为"<<customer->getNumber();
        }
        emit setViewCustomer(identifier,customer->getNumber());
    }while(function->wait->getFront()->data!=NULL);

    if(function->endflag[identifier] == false){
        QMutexLocker locker(&function->m_mutex);
        function->endflag[identifier] = true;
        if(function->firstWindow < 0){function->firstWindow = identifier;}
    }
    {
        QMutexLocker locker(&function->m_mutex);
        if(function->endflag[0]
            &&function->endflag[1]
            &&function->endflag[2]
            &&!function->allEndFlag){
            function->allEndFlag = true;
            qDebug()<<"结束";
            emit endSignal();
        }
    }
}
