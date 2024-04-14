#ifndef VIPWINDOW_H
#define VIPWINDOW_H

#include <QMainWindow>
#include "function.h"
#include <QDialog>
#include <QLabel>
#include <QThread>
#include <QMessageBox>
#include <QProgressDialog>
#include "evaluatewindow.h"
#include "countdownthread.h"
#include "vipthread.h"

namespace Ui {
class VipWindow;
}

class VipWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VipWindow(QWidget *parent = nullptr);
    ~VipWindow();

    void evaluate();

private slots:
    void on_enqueue_clicked();

    void on_dequeue_clicked();

    void on_windowsView_clicked();

    void on_start_clicked();


public slots:
    void setNumber(int num);
    void setWaitTime(int time);
    void setNumOfLine(int num);
    void progressBar();
    void setEvaluation(int i);
    void endThread();
private:
    Ui::VipWindow *ui;

    QDialog *winView;
    QDialog *chooseBusiness;
    QLabel *customerNum;
    Function *function;

    EvaluateWindow *evaluateWindow;
    QThread *cthread;
    QThread *wthread;
signals:
    void countDownTime(int time);
    void workStart(Function *function);
};

#endif // VIPWINDOW_H
