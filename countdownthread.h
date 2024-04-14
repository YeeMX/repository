#ifndef COUNTDOWNTHREAD_H
#define COUNTDOWNTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
class CountDownThread : public QObject
{
    Q_OBJECT
public:
    CountDownThread(QObject *parent = NULL);
    ~CountDownThread();
public slots:
    void countDown(int time);
signals:
    void sendWaitTime(int time);
};

#endif // COUNTDOWNTHREAD_H
