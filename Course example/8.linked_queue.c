#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElementType;

// 通过链式存储方式实现队列
typedef struct QNode {
    ElementType data;
    struct QNode* next;
} QNode, *Position;

typedef struct {
    Position front;  // 队头
    Position rear;   // 队尾
} *Queue;

// 判空
bool IsEmpty(Queue Q) {
    return Q->front == NULL;
}

// 入队
bool Enqueue(Queue Q, ElementType x) {
    QNode* node = (QNode*)malloc(sizeof(QNode));
    node->data = x;
    node->next = NULL;
    if (IsEmpty(Q)) {
        Q->front = Q->rear = node;
    } else {
        Q->rear->next = node;
        Q->rear = node;
    }
    return true;
}

// 出队
bool Dequeue(Queue Q, ElementType* x) {
    if (IsEmpty(Q)) {
        return false;
    }
    QNode* temp = Q->front;
    *x = temp->data;
    if (Q->front == Q->rear) { // 只有一个元素，出队后队列变空
        Q->front = Q->rear = NULL;
    }
    free(temp);
    return true;
}
