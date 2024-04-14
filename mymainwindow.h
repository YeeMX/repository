#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include "utils.h"
#include "queue.h"
#include "function.h"
#include <QLabel>
#include "winsthread.h"
#include <QThread>
#include <QProgressDialog>
#include "evaluatewindow.h"
#include "countdownthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MyMainWindow; }
QT_END_NAMESPACE

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();
    void businessWork();

private slots:
    void on_enqueue_clicked();
    void on_dequeue_clicked();
    void on_windowsView_clicked();
    void on_start_clicked();
    void progressBar();
    void evaluate();//评价


public slots:
    void windowViewChange(int l,int num);
    void viewNumOfLine(int num);
    void endThread();
    void setEvaluation(int i);
    void setWaitTime(int time);
signals:
    void workStart(int identifer,Function* function);
    void countDownTime(int time);
private:
    vector<QThread*> wthreads;
    vector<WinsThread*> winsthreads;
    QThread *cthread;
    QMutex m_mutex;

    Ui::MyMainWindow *ui;
    Queue<Customer> *wait;   //排队等待队列
    vector<BusinessWindow> wins;//窗口
    QDialog *dialog;
    QVector<QLabel*> customerNumber;
    QDialog *chooseBusiness;
    EvaluateWindow *evaluateWindow;

    Function *function;

};
#endif // MYMAINWINDOW_H
