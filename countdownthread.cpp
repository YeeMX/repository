#include "countdownthread.h"

CountDownThread::CountDownThread(QObject *parent):QObject(parent)
{
}

CountDownThread::~CountDownThread(){}

void CountDownThread::countDown(int time){

    for(int i = time;i >= 0;i--){
        qDebug()<<"倒计时："<<i;
        emit sendWaitTime(i);
        QThread::sleep(1);
    }
}
