#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>

#define NotFound NULL
typedef int ElementType;


// 通过链式存储方式实现线性表，带头结点
typedef struct LNode{
   ElementType Data; 
   struct LNode* next;
} *List, *Position;



 
// 初始化线性表， 返回头结点
List MakeEmpty(){
    List L;
    L = (List)malloc(sizeof(struct LNode));
    L->next = NULL;
    return L;
}

// 按值查找
Position Find(List L, ElementType X){
    Position p = L->next;
    for(; p && p->Data != X; p = p->next);
    if(!p)  // 没找到
        return NotFound; 
    else    // 找到后返回指针
        return p;
}

// 按序查找
Position Find(List L, int i){
    Position p = L->next;
    int cnt = 0;
    for(; p && cnt < i; cnt++, p = p->next);
    if(p && cnt == i)  // 找到后返回指针
        return p; 
    else    // 没找到
        return NotFound;
}

// 在下标 i 处插入 X 
bool Insert(List L, ElementType X,int i){
    if(i == 0){ // 在头结点后插入
        Position p = (Position)malloc(sizeof(struct LNode));
        p->Data = X;
        p->next = L->next;
        L->next = p;
        return true;
    }
    Position p = Find(L, i - 1); // 找到第 i-1 个结点
    if(i < 0 || !p){  
        printf("位置不合法");
        return false;
    }
    // 在第 i-1 个结点后插入
    Position newNode = (Position)malloc(sizeof(struct LNode));
    newNode->Data = X;
    newNode->next = p->next;
    p->next = newNode;
    return true;
} 

// 删除下标为 i 的元素
bool Delete(List L, int i){
    Position pre = Find(L, i - 1); // 找到第 i-1 个结点
    if(i < 0 || !pre || !pre->next){
        printf("位置不合法");
        return false;
    }
    // 删除第 i 个结点
    Position toDelete = pre->next; // 第 i 个结点
    pre->next = toDelete->next;
    free(toDelete);
    return true;
}


// 表长
int Length(List L){
    int len = 0;
    for(Position p = L->next; p; p = p->next, len++);
    return len;
} 