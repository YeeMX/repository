#ifndef WINSTHREAD_H
#define WINSTHREAD_H

#include <QObject>
#include "function.h"
#include <QMutex>
#include <QMutexLocker>
#include <QThread>

class WinsThread : public QObject
{
    Q_OBJECT
private:
    QMutex m_mutex;
public:
    WinsThread(QObject *parent = NULL);
    ~WinsThread();

public slots:
    void transactionProcessing(int identifer,Function* function);
signals:
    void setNumOfLine(int num);
    void setViewCustomer(int l,int num);
    void endSignal();
};

#endif // WINSTHREAD_H
