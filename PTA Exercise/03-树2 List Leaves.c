#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

const int MaxSize = 10;
#define null -1

typedef int Position;

// 二叉树
typedef struct TNode{
    Position Left;
    Position Right;
} BinTree;

typedef Position ElementType;
// 队列
typedef struct QNode {
    ElementType data;
    struct QNode* next;
} QNode, *QPosition;

typedef struct {
    QPosition front;  // 队头
    QPosition rear;   // 队尾
} *Queue, QueueStruct;

Queue CreateQueue();
bool IsQueueEmpty(Queue Q);
bool Enqueue(Queue Q, ElementType x);
bool Dequeue(Queue Q, ElementType* x);

//  层序遍历
void LevelOrderTraversal(BinTree BT[], Position root) {
    if (root == null) {
        return;
    }
    Queue Q = CreateQueue();
    Enqueue(Q, root); // 将根结点入队
    while (!IsQueueEmpty(Q)) {
        Position cur;
        Dequeue(Q, &cur); // 出队当前结点
        if(BT[cur].Left == null && BT[cur].Right == null){ // 叶子结点
            printf("%d", cur); // 访问当前结点
            if(!IsQueueEmpty(Q)){
                printf(" ");
            }
        }
        if (BT[cur].Left != null) {
            Enqueue(Q, BT[cur].Left); // 左子树入队
        }
        if (BT[cur].Right != null) {
            Enqueue(Q, BT[cur].Right); // 右子树入队
        }
    }
    printf("\n");
    free(Q); // 释放队列内存
}

Position BuildTree(BinTree BT[]){
    int n;
    Position root = null;
    scanf("%d", &n);
    // int count[MaxSize] = {0};
    int count[MaxSize];
    for(int i = 0; i < MaxSize; i++){
        count[i] = 0;
    }
    char left, right;
    for(int i = 0; i < n; i++){
        scanf("%*c%c %c", &left, &right);
        if(left != '-'){
            BT[i].Left = left - '0';
            count[BT[i].Left]++;
        } else {
            BT[i].Left = null;
        }
        if(right != '-'){
            BT[i].Right = right - '0';
            count[BT[i].Right]++;
        } else {
            BT[i].Right = null;
        }
    }
    for(int i = 0; i < n; i++){
        if(count[i] == 0){
            root = i;
            break; 
        }
    }
    return root;
}




int main(){
    BinTree BT[MaxSize];
    Position root = BuildTree(BT);
    LevelOrderTraversal(BT, root);


    return 0;
}


// 创建队列
Queue CreateQueue() {
    Queue Q = (Queue)malloc(sizeof(QueueStruct));
    Q->front = Q->rear = NULL;
    return Q;
}

// 判空
bool IsQueueEmpty(Queue Q) {
    return Q->front == NULL;
}

// 入队
bool Enqueue(Queue Q, ElementType x) {
    QNode* node = (QNode*)malloc(sizeof(QNode));
    node->data = x;
    node->next = NULL;
    if (IsQueueEmpty(Q)) {
        Q->front = Q->rear = node;
    } else {
        Q->rear->next = node;
        Q->rear = node;
    }
    return true;
}

// 出队
bool Dequeue(Queue Q, ElementType* x) {
    if (IsQueueEmpty(Q)) {
        return false;
    }
    QNode* temp = Q->front;
    *x = temp->data;
    if (Q->front == Q->rear) { // 只有一个元素，出队后队列变空
        Q->front = Q->rear = NULL;
    }else{
        Q->front = Q->front->next; // 更新队头指针
    }
    free(temp);
    return true;
}