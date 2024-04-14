#ifndef QUEUE_H
#define QUEUE_H

/*
* 队列
*/
template<class T>
struct Qnode{//结点
    T *data;//数据域
    Qnode<T> *next;//指针域
};
template<class T>
class Queue{    //队列
    private:
    Qnode<T> *front;    //头指针
    Qnode<T> *rear;     //尾指针
    public:
    Queue();
    void enQueue(T *data);  //入队
    T *deQueue(); //出队
    void printQueue();
    Qnode<T> *getFront(){return front;} //获取头指针
};
#endif // QUEUE_H
