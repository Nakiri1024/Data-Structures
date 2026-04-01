#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


typedef int ElementType;
typedef int Position;


// 通过顺序存储方式实现队列
typedef struct QNode{
   ElementType* Data; 
   Position Front;  // 队头
   Position Rear;   // 队尾
   int MaxSize;   // 队列的最大容量
} *Queue;



 
// 初始化队列
Queue CreateQueue(int maxsize){
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType*)malloc(maxsize * sizeof(ElementType));
    Q->Front = -1;
    Q->Rear = -1;
    Q->MaxSize = maxsize;
    return Q;
}

bool IsFull(Queue S){
    return (S->Rear + 1) % S->MaxSize == S->Front;
}

bool IsEmpty(Queue Q){
    return Q->Front == Q->Rear;
}

// 入队
bool Enqueue(Queue Q, ElementType X){
    if(IsFull(Q)){
        return false;
    }
    Q->Rear = (Q->Rear + 1) % Q->MaxSize;
    Q->Data[Q->Rear] = X;
    return true;
}

// 出队
bool Dequeue(Queue Q, ElementType* X){
    if(IsEmpty(Q)){
        return false;
    }
    Q->Front = (Q->Front + 1) % Q->MaxSize;
    *X = Q->Data[Q->Front];
    return true;
}