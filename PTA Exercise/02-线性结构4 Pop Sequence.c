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
bool Pop(Stack S){
    if(IsEmpty(S)){
        return false;
    }
    (S->Top)--;
    return true;
}

// 栈顶
ElementType Peek(Stack S){
    if(IsEmpty(S)){
        // printf("栈空");
        return -1; // 返回-1表示栈空
    }
    return S->Data[S->Top];
}

void judge(Stack S, int nums[], int seq[], int N){
    int cur = 1;
    for(int i = 1; i <=N; i++){
        if(Push(S, nums[i])){
            while(Peek(S) == seq[cur]){ // 如果栈顶元素等于当前序列元素，出栈
                Pop(S);
                cur++;
            }
        }else{ // 如果入栈失败，说明栈满了，无法继续入栈，直接返回
            printf("NO\n");
            S->Top = -1;
            return;
        }
    }
    if(IsEmpty(S)) // 如果栈空了，说明序列合法
        printf("YES\n");
    else // 否则说明序列不合法
        printf("NO\n");
    S->Top = -1; // 重置栈顶，准备下一次判断
}

void readSeq(int seq[], int N){
    for(int i = 1; i <= N; i++){
        scanf("%d", &seq[i]);
    }
}

int main(){
    int M, N, K;
    scanf("%d %d %d", &M, &N, &K);
    Stack S = CreateStack(M);
    int seq[N+1];
    int nums[N+1];
    for(int i = 1; i <= N; i++){
        nums[i] = i;
    }
    for(int i = 0; i < K; i++){
        readSeq(seq, N);
        judge(S, nums, seq, N);
    }
    return 0;
}