#ifndef UTILLS_H
#define UTILLS_H
#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <vector>
#include <thread>
#include <mutex>
#define random(a,b) (rand() % (b-a+1))+ a;  //获取[a,b]的随机整数
using namespace std;


/*
* 工具类
*/
class Utils{
private:
    static int line;
public:
    void static writeChar(short x, short y, string pchar, char color);//输出
    void static cleanConsole(short xStart,short xEnd, short y);//清空指定内容
    void static printLog(string log);//打印日志
    void static chooseUtil(int &option, int &key, bool &flag, int x, int y, vector<string> &options);
};


#endif // UTILLS_H
