#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int TreeElementType;
typedef TNode ElementType;

// 二叉树
typedef struct TNode{
    TreeElementType Data;
    struct TNode* Left;
    struct TNode* Right;
} *BinTree, TNode;

// 栈
typedef struct SNode {
    ElementType data;
    struct SNode* next;
} SNode, *Stack;

// 队列
typedef struct QNode {
    ElementType data;
    struct QNode* next;
} QNode, *Position;

typedef struct {
    Position front;  // 队头
    Position rear;   // 队尾
} *Queue, QueueStruct;

// 栈操作函数声明
Stack CreateStack();
bool IsStackEmpty(Stack S);
bool Push(Stack S, ElementType x);
bool Pop(Stack S, ElementType* x);
bool Top(Stack S, ElementType* x);
// 队列操作函数声明
Queue CreateQueue();
bool IsQueueEmpty(Queue Q);
bool Enqueue(Queue Q, ElementType x);
bool Dequeue(Queue Q, ElementType* x);


// 二叉树遍历
// 1. 先序遍历
// 递归实现
void PreOrderTraversal(BinTree BT) {
    if (BT != NULL) {
        printf("%d ", BT->Data); // 访问根结点
        PreOrderTraversal(BT->Left); // 遍历左子树
        PreOrderTraversal(BT->Right); // 遍历右子树
    }
}
// 非递归实现
void PreOrderTraversalNonRecursive(BinTree BT) {
    Stack S = CreateStack();
    BinTree cur = BT;
    while (cur != NULL || !IsStackEmpty(S)) {
        while (cur != NULL) {
            printf("%d ", cur->Data); // 访问根结点
            Push(S, cur); // 将当前结点入栈
            cur = cur->Left; // 继续遍历左子树
        }
        if (!IsStackEmpty(S)) {
            Pop(S, &cur); // 弹出栈顶结点
            cur = cur->Right; // 转向右子树
        }
    }
    free(S); // 释放栈内存
}

// 2. 中序遍历
// 递归实现
void InOrderTraversal(BinTree BT) {
    if (BT != NULL) {
        InOrderTraversal(BT->Left); // 遍历左子树
        printf("%d ", BT->Data); // 访问根结点
        InOrderTraversal(BT->Right); // 遍历右子树
    }
}
// 非递归实现
void InOrderTraversalNonRecursive(BinTree BT) {
    Stack S = CreateStack();
    BinTree cur = BT;
    while (cur != NULL || !IsStackEmpty(S)) {
        while (cur != NULL) {
            Push(S, cur); // 将当前结点入栈
            cur = cur->Left; // 继续遍历左子树
        }
        if (!IsStackEmpty(S)) {
            Pop(S, &cur); // 弹出栈顶结点
            printf("%d ", cur->Data); // 访问根结点
            cur = cur->Right; // 转向右子树
        }
    }
    free(S);
}

// 3. 后序遍历
// 递归实现
void PostOrderTraversal(BinTree BT) {
    if (BT != NULL) {
        PostOrderTraversal(BT->Left); // 遍历左子树
        PostOrderTraversal(BT->Right); // 遍历右子树
        printf("%d ", BT->Data); // 访问根结点
    }
}
// 非递归实现（方法一，使用辅助指针记录上次访问的结点）
void PostOrderTraversalNonRecursive(BinTree BT) {
    Stack S = CreateStack();
    BinTree cur = BT, pre = NULL;
    while (cur != NULL || !IsStackEmpty(S)) {
        while (cur != NULL) {
            Push(S, cur); // 将当前结点入栈
            cur = cur->Left; // 继续遍历左子树
        }
        if (!IsStackEmpty(S)) {
            Top(S, &cur); // 获取栈顶结点但不弹出
            if (cur->Right == NULL || cur->Right == pre) {  // 如果右子树为空或已经访问过，实现后序访问
                printf("%d ", cur->Data); // 访问根结点
                Pop(S, &cur); // 弹出栈顶结点
                pre = cur; // 更新上次访问的结点
                cur = NULL; // 设置当前结点为NULL以继续处理栈顶结点
            } else {
                cur = cur->Right; // 转向右子树
            }
        }
    }
    free(S);
}
// 非递归实现（方法二，使用两个栈））
void PostOrderTraversalNonRecursiveTwoStacks(BinTree BT) {
    if (BT == NULL) {
        return;
    }
    Stack S1 = CreateStack();
    Stack S2 = CreateStack();
    Push(S1, BT); // 将根结点入栈S1
    while (!IsStackEmpty(S1)) {
        BinTree cur;
        Pop(S1, &cur); // 弹出S1栈顶结点
        Push(S2, cur); // 将该结点入栈S2，S2栈中结点的顺序为根-右-左（逆序）
        if (cur->Left != NULL) {
            Push(S1, cur->Left); // 左子树入栈S1
        }
        if (cur->Right != NULL) {
            Push(S1, cur->Right); // 右子树入栈S1
        }
    }
    // S2栈中结点的访问顺序即为后序遍历顺序
    while (!IsStackEmpty(S2)) {
        BinTree node;
        Pop(S2, &node);
        printf("%d ", node->Data); // 访问结点
    }
    free(S1);
    free(S2);
}


// 4. 层序遍历
void LevelOrderTraversal(BinTree BT) {
    if (BT == NULL) {
        return;
    }
    Queue Q = CreateQueue();
    Enqueue(Q, BT); // 将根结点入队
    while (!IsQueueEmpty(Q)) {
        BinTree cur;
        Dequeue(Q, &cur); // 出队当前结点
        printf("%d ", cur->Data); // 访问当前结点
        if (cur->Left != NULL) {
            Enqueue(Q, cur->Left); // 左子树入队
        }
        if (cur->Right != NULL) {
            Enqueue(Q, cur->Right); // 右子树入队
        }
    }
    free(Q); // 释放队列内存
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
    if (IsEmpty(S)) {
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
    if(IsEmpty(S)){
        return false;
    }
    *x = S->next->data;
    return true;
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