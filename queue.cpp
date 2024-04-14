#include "queue.h"
#include "utils.h"
#include <QtCore>
//初始化链队列
template<class T>
Queue<T>::Queue(){
    Qnode<T> *node = new Qnode<T>;//初始化结点
    node->next = NULL;
    node->data = NULL;
    front = node;
    rear = node;

}

//入链队列
template<class T>
void Queue<T>::enQueue(T *data){
    //判断队列是否为空
    if(front == rear && front->data == NULL){//如果队列为空
        front->data = data;

    }else{//如果队列不为空

        Qnode<T> *node = new Qnode<T>;//初始化结点
        node->next = NULL;
        node->data = data;
        rear->next = node;
        rear = node;
    }
    qDebug()<<"入队成功";

}

//出链队列
template<class T>
T *Queue<T>::deQueue(){
    //判断队列是否为空
    if(this->front == this->rear && this->front->data == NULL){//如果队列为空
        qDebug()<<"队列为空，出队失败";
        return NULL;
    }else if(this->front == this->rear){//只有一个结点时
        T *customer = this->front->data;
        this->front->data = NULL;
        qDebug()<<"出队成功（单结点";
        return customer;
    }else{//有多个结点时
        Qnode<T> *node = this->front;
        this->front = this->front->next;//出队
        T *customer = node->data;
        delete node;
        qDebug()<<"出队成功";
        return customer;
    }
    return NULL;
}

//遍历队列
template<class T>
void Queue<T>::printQueue(){
        //判断队列是否为空
    if(front == rear && front->data == NULL){//如果队列为空
        cout<<"队列为空"<<endl;
    }else{
        cout<<"------------------"<<endl;
        Qnode<T> *node = front;
        do{
        if(node->data != NULL){
            cout<<*(node->data)<<endl;
        }
        if(node->next!=NULL){
            node = node->next;
        }else{
            break;
        }
        }while(1);
        cout<<"--------------------"<<endl;
    }
}
