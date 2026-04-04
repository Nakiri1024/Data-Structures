#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

const int MaxSize = 30;

typedef int ElementType;
// 栈
typedef struct SNode {
    ElementType data;
    struct SNode* next;
} SNode, *Stack;

Stack CreateStack();
bool IsStackEmpty(Stack S);
bool Push(Stack S, ElementType x);
bool Pop(Stack S, ElementType* x);
bool Top(Stack S, ElementType* x);

void Read(int pre[], int in[], int* n){
    int data;
    char opration[5];
    Stack S = CreateStack();
    scanf("%d", n);
    for(int i = 0, j = 0, k = 0;i < 2 * (*n); i++){
        scanf("%s", opration);
        if(!strcmp(opration, "Push")){
            scanf("%d", &data);
            Push(S, data);
            pre[j++] = data;
        } else if(!strcmp(opration, "Pop")){
            Pop(S, &data);
            in[k++] = data;
        }
    }
}

// 通过先序和中序得到后序
void GetPostOrder(int* pre, int prel, int prer,
                  int* in, int inl, int inr,
                  int* post, int postl, int postr){
    if(prel > prer){
        return;
    }
    // 根结点是先序的第一个元素
    int root = pre[prel];
    // 后序的最后一个元素是根结点
    post[postr] = root;
    // 在中序中找到根结点的位置
    int i;
    for(i = inl; i <= inr; i++){
        if(in[i] == root)
            break;
    }
    // 左子树的元素个数
    int leftTreeSize = i - inl;

    GetPostOrder(pre, prel + 1, prel + leftTreeSize,
                 in, inl, i - 1,
                 post, postl, postl + leftTreeSize - 1);
    GetPostOrder(pre, prel + leftTreeSize + 1, prer,
                 in, i + 1, inr,
                 post, postl + leftTreeSize, postr - 1);
}

int main(){
    int pre[MaxSize], in[MaxSize], post[MaxSize], n;
    Read(pre, in, &n);
    GetPostOrder(pre, 0, n - 1,
                 in, 0, n - 1,
                 post, 0, n - 1);
    for(int i = 0; i < n; i++){
        printf("%d", post[i]);
        if(i != n - 1){
            printf(" ");
        }
    }
    return 0;
}




// 栈初始化，创建头结点
Stack CreateStack(){
    Stack S = (Stack)malloc(sizeof(SNode));
    S->next = NULL;
    return S;
}

// 判栈空
bool IsStackEmpty(Stack S) {
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
    if (IsStackEmpty(S)) {
        return false;
    }
    SNode* temp = S->next;
    *x = temp->data;
    S->next = temp->next;
    free(temp);
    return true;
}

// 栈顶
bool Top(Stack S, ElementType* x){
    if(IsStackEmpty(S)){
        return false;
    }
    *x = S->next->data;
    return true;
}