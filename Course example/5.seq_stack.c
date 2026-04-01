#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


typedef int ElementType;
typedef int Position;


// 通过顺序存储方式实现栈
typedef struct SNode{
   ElementType* Data; 
   Position Top;  // 栈顶
   int MaxSize;   // 栈的最大容量
} *Stack;



 
// 初始化栈
Stack CreateStack(int maxsize){
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Data = (ElementType*)malloc(maxsize * sizeof(ElementType));
    S->Top = -1;
    S->MaxSize = maxsize;
    return S;
}

bool IsFull(Stack S){
    return S->Top == S->MaxSize - 1;
}

bool IsEmpty(Stack S){
    return S->Top == -1;
}

// 入栈
bool Push(Stack S, ElementType X){
    if(IsFull(S)){
        return false;
    }
    S->Data[++(S->Top)] = X;
    return true;
}

// 出栈
bool Pop(Stack S, ElementType* X){
    if(IsEmpty(S)){
        return false;
    }
    *X = S->Data[(S->Top)--];
    return true;
}