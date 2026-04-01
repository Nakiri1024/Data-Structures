#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

/*
本题要求实现一个函数，将两个链表表示的递增整数序列合并为一个非递减的整数序列。
L1和L2是给定的带头结点的单链表，其结点存储的数据是递增有序的；
函数Merge要将L1和L2合并为一个非递减的整数序列。
应直接使用原序列中的结点，返回归并后的带头结点的链表头指针。
*/
/* 你的代码将被嵌在这里 */
List Merge( List L1, List L2 ){
    List merged = (List)malloc(sizeof(struct Node));
    merged->Next = NULL;
    List tail = merged;
    List p1 = L1->Next, p2 = L2->Next;
    while(p1 && p2){
        if(p1->Data <= p2->Data){
            tail->Next = p1;
            tail = p1;
            p1 = p1->Next;
        }
        else{
            tail->Next = p2;
            tail = p2;
            p2 = p2->Next;
        }
    }
    if(p1)
        tail->Next = p1;
    if(p2)
        tail->Next = p2;
    L1->Next = NULL;
    L2->Next = NULL;
    return merged;
}