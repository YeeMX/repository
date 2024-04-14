#include "vipwindow.h"
#include "ui_vipwindow.h"

VipWindow::VipWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VipWindow)
{
    ui->setupUi(this);

    function = new Function();
    QObject::connect(function,&Function::changeLabel,this,&VipWindow::setNumber);
    //初始化view窗口
    winView = new QDialog();
    winView->resize(200,100);
    QLabel *label1 = new QLabel(winView);
    QLabel *label2 = new QLabel(winView);
    QLabel *label3 = new QLabel(winView);

    label1->move(20,60);
    label1->setText("当前顾客编号");
    label2->move(20,20);
    label2->setText("窗口编号");
    label3->move(140,20);
    label3->setText("VIP");

    customerNum = new QLabel(winView);
    customerNum->resize(15,10);
    customerNum->move(140,60);
}

VipWindow::~VipWindow()
{
    wthread->quit();
    wthread->wait();
    cthread->quit();
    cthread->wait();
    delete ui;
}

void VipWindow::on_enqueue_clicked()
{
    function->getVipNumber();
}

void VipWindow::on_dequeue_clicked()
{
    function->callVipNumber();
}

void VipWindow::on_windowsView_clicked()
{
    winView->show();
}

void VipWindow::setNumber(int num)
{
    customerNum->setNum(num);
}

void VipWindow::setWaitTime(int time)
{
    if(time == 0){
        ui->waitTime->setText("即将轮到您，请稍等");
    }else{
        ui->waitTime->setNum(time);
    }
}

void VipWindow::setNumOfLine(int num)
{
    ui->lineNum->setNum(num);
}

void VipWindow::on_start_clicked()
{
    function->createSimulation();
    ui->lineNum->setNum(function->vipWaitNumber);
    //function->callVipNumber();
    ui->queueNum->setNum(function->vipNumber);
    //开启倒计时线程
    cthread = new QThread();
    CountDownThread *countDownThread = new CountDownThread();
    countDownThread->moveToThread(cthread);
    connect(cthread,&QThread::finished,cthread,&QObject::deleteLater);
    connect(cthread,&QThread::finished,countDownThread,&QObject::deleteLater);
    connect(this,&VipWindow::countDownTime,countDownThread,&CountDownThread::countDown);
    connect(countDownThread,&CountDownThread::sendWaitTime,this,&VipWindow::setWaitTime);
    cthread->start();
    emit countDownTime((function->vipWaitTime));

    wthread = new QThread();
    VipThread *vipThread = new VipThread();
    vipThread->moveToThread(wthread);
    connect(wthread,&QThread::finished,wthread,&QObject::deleteLater);
    connect(wthread,&QThread::finished,vipThread,&QObject::deleteLater);
    connect(this,&VipWindow::workStart,vipThread,&VipThread::transactionProcessing);
    connect(vipThread,&VipThread::sendNum,this,&VipWindow::setNumber);
    connect(vipThread,&VipThread::endSignal,this,&VipWindow::endThread);
    connect(vipThread,&VipThread::sendNumOfLine,this,&VipWindow::setNumOfLine);
    wthread->start();
    emit workStart(function);

    //提示对话框
    int ret = QMessageBox::information(this,tr("提示"),
                            tr("您的排队号码为：")+QString::number(function->vipNumber)+tr("，请牢记！"),QMessageBox::Ok);
    if(ret == QMessageBox::Yes) qDebug()<<tr("提示！");

}
void VipWindow::progressBar()
{
    chooseBusiness->close();
    QProgressDialog dialog(tr("业务办理进度"),tr("取消"),0,100000,this);
        dialog.setWindowTitle(tr("进度对话框")); //设置窗口标题
        dialog.setWindowModality(Qt::WindowModal);  //将对话框设置为模态
        dialog.show();
        for(int i = 0; i < 100000; i++){ //演示进度
            dialog.setValue(i); //设置进度条的当前值
            QCoreApplication::processEvents();  //避免界面冻结
            if(dialog.wasCanceled()) break; //按下取消按钮则中断
        }
        dialog.setValue(100000); //补上for循环中漏掉的100000
        qDebug()<<tr("业务办理结束！");
        evaluate();
}
void VipWindow::evaluate(){
    evaluateWindow = new EvaluateWindow();
    connect(evaluateWindow,&EvaluateWindow::sendEvaluate,this,&VipWindow::setEvaluation);
    evaluateWindow->show();
}
void VipWindow::setEvaluation(int i)
{
    if(i > 0){
        function->vipWin->setEvaluate(i);
    }
    function->save();
    evaluateWindow->close();
    QMessageBox::about(this,tr("end"),
                       tr("谢谢合作，再见！"));
}

void VipWindow::endThread()
{
    this->close();
    winView->close();
    qDebug()<<"关闭";
    //提示对话框
    int ret2 = QMessageBox::information(this,tr("提示"),
                            tr("尊敬的")+QString::number(function->vipNumber)+tr("号顾客，请到VIP窗口办理业务"),QMessageBox::Ok);
    if(ret2 == QMessageBox::Ok) {
        qDebug()<<tr("选择业务！");
        chooseBusiness = new QDialog();
        chooseBusiness->resize(200,150);
        QLabel *label = new QLabel(chooseBusiness);
        QPushButton *b1 = new QPushButton(chooseBusiness);
        QPushButton *b2 = new QPushButton(chooseBusiness);
        connect(b1,&QPushButton::clicked,this,&VipWindow::progressBar);
        connect(b2,&QPushButton::clicked,this,&VipWindow::progressBar);

        label->setText("请选择您要办理的业务");
        b1->setText("存取款");
        b2->setText("办卡");

        label->move(20,20);
        b1->move(20,90);
        b2->move(100,90);

        chooseBusiness->show();
    }
}
