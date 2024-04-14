#include "mymainwindow.h"
#include "./ui_mymainwindow.h"
#include "queue.h"
#include "queue.cpp"
#include <QMessageBox>


MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    //初始化Function
    function = new Function();
    QObject::connect(function,&Function::changeLabel,this,&MyMainWindow::windowViewChange);
    ui->setupUi(this);
    wait = new Queue<Customer>;


    //初始化view窗口
    dialog = new QDialog(this);
    dialog->setWindowTitle("view窗口");
    dialog->resize(400,100);
    QLabel *label1 = new QLabel(dialog);
    QLabel *label2 = new QLabel(dialog);



    label1->move(20,60);
    label1->setText("当前顾客编号");
    label2->move(20,20);
    label2->setText("窗口编号                  1              2              3");

    for(int i=0;i<function->numOfWindow;i++){
        QLabel *number = new QLabel(dialog);
        number->resize(15,10);
        number->move(140+63*i,60);
        customerNumber.emplace_back(number);

    }



}

MyMainWindow::~MyMainWindow()
{
    for(int i = 0; i < function->numOfWindow; i++){
        wthreads[i]->quit();
        wthreads[i]->wait();
    }
    cthread->quit();
    cthread->wait();
    delete ui;
}

void MyMainWindow::businessWork()
{
    close();
    dialog->close();
    qDebug()<<"关闭";
    //提示对话框
    int ret2 = QMessageBox::information(this,tr("提示"),
                            tr("尊敬的")+QString::number(function->number)+tr("号顾客，请到")+QString::number(function->firstWindow+1)+tr("号窗口办理业务"),QMessageBox::Ok);
    if(ret2 == QMessageBox::Ok) {
        qDebug()<<tr("选择业务！");
        chooseBusiness = new QDialog();
        chooseBusiness->resize(200,150);
        QLabel *label = new QLabel(chooseBusiness);
        QPushButton *b1 = new QPushButton(chooseBusiness);
        QPushButton *b2 = new QPushButton(chooseBusiness);
        connect(b1,&QPushButton::clicked,this,&MyMainWindow::progressBar);
        connect(b2,&QPushButton::clicked,this,&MyMainWindow::progressBar);

        label->setText("请选择您要办理的业务");
        b1->setText("存取款");
        b2->setText("办卡");

        label->move(20,20);
        b1->move(20,90);
        b2->move(100,90);

        chooseBusiness->show();
    }

}


void MyMainWindow::on_enqueue_clicked()
{
    function->getNumber();
}

void MyMainWindow::on_dequeue_clicked()
{
    function->callNumber();
}
void MyMainWindow::on_windowsView_clicked()
{
    dialog->show();
}

void MyMainWindow::windowViewChange(int l,int num){

    QMutexLocker locker(&m_mutex);
    customerNumber[l]->setNum(num);

}

void MyMainWindow::viewNumOfLine(int num)
{

    QMutexLocker locker(&m_mutex);
    ui->lineNum->setNum(num);

}

void MyMainWindow::endThread()
{
    //for(int i = 0; i < function->numOfWindow; i++){
        //wthreads[i]->quit();
        //wthreads[i]->wait();
    //}
    //cthread->quit();
    //cthread->wait();
    qDebug()<<"排队模拟完成";
    this->businessWork();
}

void MyMainWindow::setEvaluation(int i)
{
    if(i > 0){
        function->wins[function->firstWindow].setEvaluate(i);
    }
    function->save();
    evaluateWindow->close();
    QMessageBox::about(this,tr("end"),
                       tr("谢谢合作，再见！"));
}

void MyMainWindow::setWaitTime(int time)
{
    if(time == 0){
        ui->waitTime->setText("即将轮到您，请稍等");
    }else{
        ui->waitTime->setNum(time);
    }
    }

void MyMainWindow::on_start_clicked()
{
    function->threadFlag2 = true;
    function->createSimulation();
    for(int i = 0;i<function->numOfWindow;i++){
        function->callNumber();
    }
    ui->lineNum->setNum(function->numberOfLine);
    ui->queueNum->setNum(function->number);

    //开启线程
    for(int i = 0; i < function->numOfWindow; i++){

        function->endflag.emplace_back(false);

        QThread *wthread = new QThread();
        WinsThread *winsthread = new WinsThread;
        winsthreads.emplace_back(winsthread);
        wthreads.emplace_back(wthread);
        winsthread->moveToThread(wthread);
        connect(wthread,&QThread::finished,wthread,&QObject::deleteLater);
        connect(wthread,&QThread::finished,winsthread,&QObject::deleteLater);
        connect(this,&MyMainWindow::workStart,winsthread,&WinsThread::transactionProcessing);
        connect(winsthread,&WinsThread::setNumOfLine,this,&MyMainWindow::viewNumOfLine);
        connect(winsthread,&WinsThread::setViewCustomer,this,&MyMainWindow::windowViewChange);
        connect(winsthread,&WinsThread::endSignal,this,&MyMainWindow::endThread);
        wthread->start();
        if(wthread->isRunning()){
            qDebug()<<"线程"<<i<<"已开启";
        }else{
            qDebug()<<"线程"<<i<<"未启动";
        }
        emit workStart(i,function);
    }
    //开启倒计时线程
    cthread = new QThread();
    CountDownThread *countDownThread = new CountDownThread();
    countDownThread->moveToThread(cthread);
    connect(cthread,&QThread::finished,cthread,&QObject::deleteLater);
    connect(cthread,&QThread::finished,countDownThread,&QObject::deleteLater);
    connect(this,&MyMainWindow::countDownTime,countDownThread,&CountDownThread::countDown);
    connect(countDownThread,&CountDownThread::sendWaitTime,this,&MyMainWindow::setWaitTime);
    cthread->start();
    emit countDownTime((function->waitTime/3));

    //提示对话框
    int ret = QMessageBox::information(this,tr("提示"),
                            tr("您的排队号码为：")+QString::number(function->number)+tr("，请牢记！"),QMessageBox::Ok);
    if(ret == QMessageBox::Yes) qDebug()<<tr("提示！");


}

void MyMainWindow::progressBar()
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

void MyMainWindow::evaluate()
{
    evaluateWindow = new EvaluateWindow();
    connect(evaluateWindow,&EvaluateWindow::sendEvaluate,this,&MyMainWindow::setEvaluation);
    evaluateWindow->show();

}

