#include "welcomewindow.h"
#include "ui_welcomewindow.h"
#include "mymainwindow.h"
#include "vipwindow.h"
#include <QMessageBox>
WelcomeWindow::WelcomeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWindow)
{
    ui->setupUi(this);

}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

void WelcomeWindow::on_pushButton_clicked()
{
    close();
    //问题对话框
       int ret1 = QMessageBox::question(this,tr("问题对话框"),
                           tr("你是vip吗"),QMessageBox::Yes,QMessageBox::No);
       if(ret1 == QMessageBox::No) {
           MyMainWindow *w = new MyMainWindow;

           w->show();
           qDebug()<<tr("普通用户");
       }else if(ret1 == QMessageBox::Yes){
           VipWindow *v = new VipWindow;
           v->show();
       }
}

void WelcomeWindow::on_pushButton_3_clicked()
{
    Function *function = new Function;
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("评价窗口");
    dialog->resize(400,100);
    QLabel *label1=new QLabel(dialog);
    QLabel *label2=new QLabel(dialog);



    label1->move(20,60);
    label1->setText("当前顾客编号");
    label2->move(20,20);
    label2->setText("窗口编号                  1              2              3              VIP");

    for(int i=0;i<3;i++){
        QLabel *number=new QLabel(dialog);
        number->resize(24,10);
        number->move(140+63*i,60);
        QString evaluation = QString("%1").arg((float)function->wins[i].getEvaluateSum()/(float)function->wins[i].getEvaluateTime());
        number->setText(evaluation);
    }
    QLabel *number=new QLabel(dialog);
    number->resize(24,10);
    number->move(140+63*3,60);
    QString evaluation = QString("%1").arg((float)function->vipWin->getEvaluateSum()/(float)function->vipWin->getEvaluateTime());
    number->setText(evaluation);
    dialog->show();
}
