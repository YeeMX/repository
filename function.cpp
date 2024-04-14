#include "function.h"
#include <QtCore>
#include <queue.cpp>

Function::Function(){
    number = 1; //初始化排队编号
    vipNumber = 1;  //初始化vip编号
    numberOfLine = 0;   //初始化排队人数
    waitTime = 0;   //初始化等待时间
    vipWaitTime = 0; //初始化vip等待时间
    vipWaitNumber = 0;  //初始化vip排队人数
    wait = new Queue<Customer>; //初始化队列
    vipWait = new Queue<Customer>;//初始化vip队列
    threadFlag = false;
    threadFlag2 = false;
    countFlag = false;
    winflag = 0;
    allEndFlag = false;
    //初始化窗口
    int evaluateTime = 0; //评价次数
    int evaluateSum = 0; //评价总分

    QFile inputFile("://data/evaluation.txt");    // 指定文件

    if(!inputFile.open(QIODevice::ReadOnly)){
        qDebug()<<"文件读取失败";
    }else{
        QTextStream stream(&inputFile);
        for(int i=0;i<numOfWindow;i++){
                stream >> evaluateTime >> evaluateSum;//读取
                qDebug()<<"窗口编号"<<i+1;
                qDebug()<<"评价次数"<<evaluateTime;
                qDebug()<<"评价总分"<<evaluateSum;
                BusinessWindow w(false, i, evaluateTime, evaluateSum);
                wins.emplace_back(w);
        }
        stream >> evaluateTime >> evaluateSum;//
        qDebug()<<"窗口编号 vip";
        qDebug()<<"评价次数"<<evaluateTime;
        qDebug()<<"评价总分"<<evaluateSum;
        vipWin = new BusinessWindow(true, -1, evaluateTime, evaluateSum);
        inputFile.close();
    }

}
Function::~Function(){
    delete(wait);
    delete(vipWin);
}



//取号
void Function::getNumber(){
    Customer *customer = new Customer(false,number);    //创建Customer对象
    int num = customer->getNumber();
    qDebug()<<"创建顾客"<<QString::number(num);
    number++;   //number递增
    numberOfLine++; //排队人数增加
    //Utils::cleanConsole(14,20,8);//清除上一个数据
    //Utils::writeChar(15, 8, to_string(numberOfLine), 15);//打印排队人数
    wait->enQueue(customer);   //入等待队列
}

//vip取号
void Function::getVipNumber(){
    Customer *customer = new Customer(true,vipNumber);    //创建Customer对象
    int num = customer->getNumber();
    qDebug()<<"创建vip"<<QString::number(num);
    vipNumber++;   //number递增
    vipWaitNumber++; //排队人数增加
    //Utils::cleanConsole(47,53,8);//清除上一个数据
    //Utils::writeChar(48, 8, to_string(vipWaitNumber), 15);//打印排队人数
    vipWait->enQueue(customer);   //入等待队列
}

//取号(返回Customer对象)
Customer *Function::getCustomerNumber(){
    Customer *customer = new Customer(false,number);    //创建Customer对象
    number++;   //number递增
    numberOfLine++; //排队人数增加
    //Utils::cleanConsole(14,20,8);//清除上一个数据
    //Utils::writeChar(15, 8, to_string(numberOfLine), 15);//打印排队人数
    wait->enQueue(customer);   //入等待队列
    return customer;
}

//叫号(窗口未满时)
void Function::callNumber(){
    bool flag = false;//判断窗口是否未满的标志
    //判断窗口是否已满
    for(int i=0;i<numOfWindow;i++)
        {
            if(wins[i].getIsNull()){
                flag = true;
            }
        }
    if(flag == true){
        Customer *customer = wait->deQueue(); //出队
        if(customer == NULL){
            qDebug()<<"无等待人员，叫号失败";
            return;
        }
    numberOfLine--; //排队人数减少
    for(int i=0;i<numOfWindow;i++)
        {
            if(wins[i].getIsNull()){
                wins[i].setCustomer(customer);
                emit changeLabel(i,customer->getNumber());
                //Utils::writeChar(5+i*10, 12, customer->getStringNumber(), 15);
                break;
            }
        }

    }else{
        Customer *customer = wait->getFront()->data; //
        qDebug()<<"窗口已满,退出";
        if(customer!=NULL){
            callNumber(winflag);
            ++winflag;
            if(winflag == 3) winflag = 0;
        }
    }
}

//叫号
void Function::callNumber(int flag){
    Customer *customer = wait->deQueue(); //出队
    if(customer == NULL){
        qDebug()<<"无等待人员，叫号失败";
        return;
    }
    numberOfLine--; //排队人数减少
    wins[flag].setCustomer(customer);
    emit changeLabel(flag,customer->getNumber());
    //Utils::writeChar(5+flag*10, 12, customer->getStringNumber(), 15);

}

//vip叫号
void Function::callVipNumber(){
    Customer *customer = vipWait->deQueue();
    if(customer == NULL){
        qDebug()<<"无等待人员，叫号失败";
        return;
    }
    vipWaitNumber--;
    vipWin->setCustomer(customer);
    emit changeLabel(customer->getNumber(),0);


}

//创建模拟
void Function::createSimulation(){
    int wait = random(10,20);  //随机生成10~20个排队等待人员
    for(int i = 0; i < wait; i++){
        getNumber();    //取号
        waitTime += random(3,6);    //随机生成3~6秒的等待时间
    }
    int waitVip = random(2,5);  //随机生成2~5个排队等待人员
    for(int i = 0; i < waitVip; i++){
        getVipNumber();    //取号
        vipWaitTime += random(3,6);    //随机生成3~6秒的等待时间
    }

}
 //进度条
void Function::progressBar(int win){
    Utils::writeChar(5, 3, "正在", 15);
    Utils::writeChar(9, 3, to_string(win+1), 15);
    Utils::writeChar(10, 3, "号窗口办理业务中", 15);

    Utils::writeChar(5, 5, "[", 15);
    Utils::writeChar(35, 5, "]", 15);
    for(int i = 6; i <35;i++){
        Utils::writeChar(i, 5, "#", 15);
        Sleep(100);
    }
    Utils::writeChar(5, 7, "办理成功", 15);
    Sleep(2000);
}


//事务处理
void Function::transactionProcessing(int identifier){
    qDebug()<<"线程开始:"<<identifier;
    do{
    //lock_guard<mutex> guard(m);  //创建lock_guard的类对象guard，用互斥量m来构造
    //默认开始时柜台已满

    //等待当前柜台人员办理业务
    Sleep(1000*wins[identifier].getCustomer()->getWaitTime());
    if(threadFlag) return;
    Customer *customer = NULL;
    {
        customer = wait->getFront()->data;    //获取将要出队的顾客对象
        if(customer == NULL){
            lock_guard<mutex> guard(m);  //创建lock_guard的类对象guard，用互斥量m来构造
            //Utils::printLog("无等待人员，叫号失败");
            //Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "无等待人员，叫号失败",identifier);
            if(firstWindow < 0){firstWindow = identifier;}
            break;
        }
        wait->deQueue();//出队
    }

    if(numberOfLine>0) numberOfLine--; //排队人数减少
    {
        lock_guard<mutex> guard(m);  //创建lock_guard的类对象guard，用互斥量m来构造
        Utils::cleanConsole(14,20,8);//清除上一个数据
        Utils::writeChar(15, 8, to_string(numberOfLine), 15);//打印排队人数
    }
    int evaluate = random(2,5);
    wins[identifier].setEvaluate(evaluate);//随机设置评分
    wins[identifier].setCustomer(customer);
    {
        lock_guard<mutex> guard(m);  //创建lock_guard的类对象guard，用互斥量m来构造
        Utils::writeChar(5+10*identifier, 12, customer->getStringNumber(), 15);
        qDebug()<<identifier<<"号窗口正在办理业务的顾客为"<<customer->getNumber();
    }
    }while(wait->getFront()->data != NULL);
}

//评价
void Function::evaluate(int win)
{
    system("cls");
    vector<string> options = {
        "☆",
        "☆☆",
        "☆☆☆",
        "☆☆☆☆",
        "☆☆☆☆☆",
        "不作评价"
        };
    Utils::writeChar(5, 1, "请对"+to_string(win+1)+"号窗口的服务进行评价", 15);
    Utils::writeChar(3, 3, "→", 15);
    for (int i = 0; i < (int)options.size(); i++)
    {
        Utils::writeChar(5, 3 + i, options[i], 15);
    }
    int key = 0;
    int option = 0;
    bool flag = false;
    Utils::chooseUtil(option, key, flag, 3, 3, options);
    if (key >= 0 && key < 5)
    {
        wins[win].setEvaluate(key+1);
    }
    else if (key == 5){}
    else
    {
        exit(-1);
    }

}

//保存评价
void Function::save(){
    QFile outputFile("D:\\forlearning\\QtProject\\BankQueueSystem\\data\\evaluation.txt");

    if(!outputFile.open(QIODevice::WriteOnly)){
        qDebug()<<"文件打开失败";
    }else{
        qDebug()<<"文件打开成功";
        QTextStream stream(&outputFile);
        for(int i=0;i<numOfWindow;i++){
            stream << wins[i].getEvaluateTime() <<" "<< wins[i].getEvaluateSum() << "\n" ;//写入
        }
        qDebug()<<"普通窗口写入成功";
        stream<<vipWin->getEvaluateTime()<<" "<<" "<<vipWin->getEvaluateSum()<<"\n";
        qDebug()<<"vip窗口写入成功";
        outputFile.close();
    }
//    ofstream win_outfile("../data/evaluation.txt",ios::out);
//    if(!win_outfile){
//        qDebug()<<"文件写入失败";
//    }
//    vector<BusinessWindow>::iterator t;
//    for(t = wins.begin();t != wins.end();++t){
//        win_outfile<<t->getEvaluateTime()<<" "<<t->getEvaluateSum()<<"\n";
//    }
//    qDebug()<<"普通窗口写入成功";
//    win_outfile<<vipWin->getEvaluateTime()<<" "<<vipWin->getEvaluateSum()<<"\n";
//    qDebug()<<"vip窗口写入成功";
//    win_outfile.close();
}

//多线程实现
//void Function::multithreading(){
//    threadFlag2 = true;
//    createSimulation();//创建模拟
//    for (int i = 0; i < numOfWindow; i++)
//    {
//        Function::callNumber();
//    }
//        for (int i = 0; i < numOfWindow; i++)
//    {
//        wins_thread.emplace_back(std::thread(&Function::transactionProcessing,this,i));

//    }
//        wins_thread.emplace_back(std::thread(&Function::vipThread,this));
//        wins_thread.emplace_back(std::thread(&Function::countDown,this));
//        wins_thread.emplace_back(std::thread(&Function::countDownVip,this));
//    //中止线程
//        for (int i = 0; i < (int)wins_thread.size(); i++)
//    {
//        wins_thread[i].join();

//    }
//    countFlag = true;//终止倒计时
//    Sleep(1000);
//    system("cls");
//    progressBar(firstWindow);
//    evaluate(firstWindow);//评价
//    sava();//保存评价
//    endMenu();
//    exit(0);

//}

//vip窗口
//void Function::vipWindow(){
//    createSimulation();//创建模拟

//    for (int i = 0; i < numOfWindow; i++)
//    {
//        Function::callNumber();
//    }
//        for (int i = 0; i < numOfWindow; i++)
//    {
//        wins_thread.emplace_back(std::thread(&Function::transactionProcessing,this,i));

//    }
//    wins_thread.emplace_back(std::thread(&Function::countDown,this));
//    wins_thread.emplace_back(std::thread(&Function::countDownVip,this));
//    vipThread();

//}
//vip线程
void Function::vipThread(){

    Utils::cleanConsole(47,53,9);//清除上一个数据
    Utils::writeChar(48, 9, to_string(vipWaitTime), 15);//打印等待时间
    {
        lock_guard<mutex> guard(m);  //创建lock_guard的类对象guard，用互斥量m来构造
        qDebug()<<"vip窗口开始";
    }

    do{
    Customer *customer = vipWait->deQueue(); //出队
    if(customer == NULL){
        lock_guard<mutex> guard(m);  //创建lock_guard的类对象guard，用互斥量m来构造
        qDebug()<<"无等待人员，叫号失败";
        return;
    }
    vipWaitNumber--; //排队人数减少
    {
        lock_guard<mutex> guard(m);  //创建lock_guard的类对象guard，用互斥量m来构造
        Utils::cleanConsole(47,53,8);//清除上一个数据
        Utils::writeChar(48, 8, to_string(vipWaitNumber), 15);//打印排队人数
        Utils::writeChar(35, 12, 'V'+customer->getStringNumber(), 15);
    }
    vipWin->setCustomer(customer);
    Sleep(1000*customer->getWaitTime());
    int evaluate = random(4,5);
    vipWin->setEvaluate(evaluate);//随机设置评分
    }while(vipWait->getFront()->data != NULL);
    if(threadFlag2)  return;
    threadFlag = true;//终止线程
    countFlag = true;//终止倒计时
    Sleep(1000);
    system("cls");
    Utils::writeChar(5, 3, "正在VIP窗口办理业务中", 15);

    Utils::writeChar(5, 5, "[", 15);
    Utils::writeChar(35, 5, "]", 15);
    for(int i = 6; i <35;i++){
        Utils::writeChar(i, 5, "#", 15);
        Sleep(100);
    }
    Utils::writeChar(5, 7, "办理成功", 15);
    Sleep(2000);
        system("cls");
    vector<string> options = {
        "☆",
        "☆☆",
        "☆☆☆",
        "☆☆☆☆",
        "☆☆☆☆☆",
        "不作评价"
        };
    Utils::writeChar(5, 1, "请对VIP窗口的服务进行评价", 15);
    Utils::writeChar(3, 3, "→", 15);
    for (int i = 0; i < (int)options.size(); i++)
    {
        Utils::writeChar(5, 3 + i, options[i], 15);
    }
    int key = 0;
    int option = 0;
    bool flag = false;
    Utils::chooseUtil(option, key, flag, 3, 3, options);
    if (key >= 0 && key < 5)
    {
        vipWin->setEvaluate(key+1);
    }
    else if (key == 5){}
    else
    {
        exit(-1);
    }

    save();//保存评价
    endMenu();

}
//终止菜单
void Function::endMenu()
{
    do{
        qDebug()<<"进入结束菜单";
    system("cls");
    vector<string> options = {
        "查看评价",
        "退出",
        };
    Utils::writeChar(3, 3, "→", 15);
    for (int i = 0; i < (int)options.size(); i++)
    {
        Utils::writeChar(5, 3 + i, options[i], 15);
    }
    int key = 0;
    int option = 0;
    bool flag = false;
    Utils::chooseUtil(option, key, flag, 3, 3, options);
    if (key == 0)
    {
        commentsView();
    }
    else if (key == 1){
        system("cls");
        Utils::writeChar(5, 1, "感谢合作，再见！", 15);
        Sleep(3000);
        exit(0);}
    else
    {
        exit(-1);
    }
    }while(1);
}
//查看评价
void Function::commentsView(){
    system("cls");
    qDebug()<<"进入评价列表";
    Utils::writeChar(5, 3, "一号柜台", 15);
    Utils::writeChar(15, 3, "二号柜台", 15);
    Utils::writeChar(25, 3, "三号柜台", 15);
    Utils::writeChar(35, 3, "VIP柜台", 15);
        for (int i = 0; i < numOfWindow; i++)
    {
        Utils::writeChar(5+10*i, 4, wins[i].getEvaluate(), 15);
    }
    Utils::writeChar(35, 4, vipWin->getEvaluate()+"\n", 15);
    system("pause");
}

//倒计时
void Function::countDown(){
    for(int i = waitTime/3; i > 0; i--){
        Sleep(1000);
        if(countFlag) return;
        {
        lock_guard<mutex> guard(m);  //创建lock_guard的类对象guard，用互斥量m来构造
        Utils::cleanConsole(18,24,9);//清除上一个数据
        Utils::writeChar(19, 9, to_string(i-1), 15);//打印等待时间
        }
    }
}
//vip倒计时
void Function::countDownVip(){
     qDebug()<<"进入打印";
    for(int i = vipWaitTime; i > 0; i--){
        Sleep(1000);
        if(countFlag) return;
        {
        qDebug()<<"打印等待时间"<<i-1;
        lock_guard<mutex> guard(m);  //创建lock_guard的类对象guard，用互斥量m来构造
        Utils::cleanConsole(47,53,9);//清除上一个数据
        Utils::writeChar(48, 9, to_string(i-1), 15);//打印等待时间
        }
    }
}
