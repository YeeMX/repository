#ifndef VIPTHREAD_H
#define VIPTHREAD_H
#include <QObject>
#include <QDebug>
#include <QThread>
#include "function.h"
class VipThread : public QObject
{
    Q_OBJECT
public:
    VipThread(QObject *parent = NULL);
    ~VipThread();
public slots:
    void transactionProcessing(Function* function);
signals:
    void sendNum(int num);
    void endSignal();
    void sendNumOfLine(int num);
};

#endif // VIPTHREAD_H
