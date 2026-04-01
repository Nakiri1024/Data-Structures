#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElementType;

// 通过链式存储方式实现栈
typedef struct SNode {
    ElementType data;
    struct SNode* next;
} SNode, *Stack;

// 初始化，创建头结点
Stack CreateStack(){
    Stack S = (Stack)malloc(sizeof(SNode));
    S->next = NULL;
    return S;
}

// 判栈空
bool IsEmpty(Stack S) {
    return S->next == NULL;
}

// 入栈
bool Push(Stack S, ElementType x) {
    SNode* node = (Stack)malloc(sizeof(SNode));
    node->data = x;
    node->next = S->next;
    S->next = node;
    return true;
}

// 出栈
bool Pop(Stack S, ElementType* x) {
    if (IsEmpty(S)) {
        return false;
    }
    SNode* temp = S->next;
    *x = temp->data;
    S->next = temp->next;
    free(temp);
    return true;
}