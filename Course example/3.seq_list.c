#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>

#define MAXSIZE 100 
#define NotFound -1
typedef int ElementType;
typedef int Position;




// 通过顺序存储方式实现线性表
typedef struct LNode{
   ElementType Data[MAXSIZE]; 
   Position Last;  // 线性表的最后一个元素
} *List;



 
// 初始化顺序表
List MakeEmpty(){
    List L;
    L = (List)malloc(sizeof(struct LNode));
    L->Last = -1;
    return L;
}

// 查找 X 第一次出现的下标 
// 平均查找次数(n +1)/2，平均时间性能为 O(n)
Position Find(List L, ElementType X){
    Position i = 0;
    for(; i <= L->Last && L->Data[i] != X; i++);
    if(L->Last < i)  // 没找到
        return NotFound; 
    else    // 找到后返回下标 
        return i;
}

// 在下标为 i 的地方插入 X 
// 平均移动元素次数为 n/2，平均时间性能为 O(n)
bool Insert(List L, ElementType X,Position i){
    if(L->Last == MAXSIZE - 1){ 
        printf("表满");
        return false;
    }
    if(i < 0 || L->Last + 1 < i){  
        printf("位置不合法");
        return false;
    }
    for(Position j = L->Last; j >= i; j--)   // 从后往前
        L->Data[j + 1] = L->Data[j];   
    L->Data[i] = X;    // 插入
    L->Last++;    // Last指向表尾
    return true;
} 

// 删除下标为 i 的元素
// 平均移动元素次数为 (n-1)/2，平均时间性能为 O(n)
bool Delete(List L, Position i){
    if(i < 0 || L->Last <i){
        printf("L->Data[%d]不存在元素", i);
        return false;
    }
    for(Position j = i + 1; j <= L->Last; j++)   // 从前往后
        L->Data[j - 1] = L->Data[j];
    L->Last--;  // Last指向表尾
    return true;
}

// 顺序存储的线性表访问下标为 i 的元素：L->Data[i]
ElementType FindKth(List L, Position i){
	if(i < 0 || L->Last < i){
        printf("L->Data[%d]不存在元素", i);
        return;
    }
    return L->Data[i];
}

// 表长
// 顺序存储的线性表的长度：L->Last + 1
int Length(List L){
	return L->Last + 1;
} 