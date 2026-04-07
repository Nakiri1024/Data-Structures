#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int TreeElementType;


// 平衡二叉树（AVL树）
typedef struct AVLTNode{
    TreeElementType Data;
    struct AVLTNode* Left;
    struct AVLTNode* Right;
    int Height;
} *AVLTree, AVLTNode;
typedef AVLTree Position;

int GetHeight(AVLTree T);
int GetBalanceFactor(AVLTree T);
int max(int a, int b);
AVLTree RotateLeft(AVLTree T);
AVLTree RotateRight(AVLTree T);
AVLTree Insert(AVLTree T, TreeElementType X);


int main(){
    int N;
    scanf("%d", &N);
    AVLTree T = NULL;
    for(int i = 0; i < N; i++){
        TreeElementType value;
        scanf("%d", &value);
        T = Insert(T, value);
    }
    printf("%d\n", T->Data); // 输出AVL树的根结点值

    return 0;
}



// 平衡因子
int GetHeight(AVLTree T) {
    return T == NULL ? 0 : T->Height;
}
int GetBalanceFactor(AVLTree T) {
    return GetHeight(T->Left) - GetHeight(T->Right);
}
int max(int a, int b) {
    return a > b ? a : b;
}

// 调整
// RR、LL、RL、LR四种情况
// RR，左旋，LL，右旋，LR，先左旋再右旋，RL，先右旋再左旋
// 左旋
AVLTree RotateLeft(AVLTree T) {
    AVLTree newRoot = T->Right; // 新根结点为当前结点的右子结点
    T->Right = newRoot->Left; // 将新根结点的左子树转移到当前结点的右子树
    newRoot->Left = T; // 将当前结点转移到新根结点的左子树
    // 更新高度
    // 注意：先更新当前结点的高度，再更新新根结点的高度
    T->Height = 1 + max(GetHeight(T->Left), GetHeight(T->Right));
    newRoot->Height = 1 + max(GetHeight(newRoot->Left), GetHeight(newRoot->Right));
    return newRoot; // 返回新的根结点
}
// 右旋
AVLTree RotateRight(AVLTree T) {
    AVLTree newRoot = T->Left;
    T->Left = newRoot->Right;
    newRoot->Right = T;
    // 更新高度
    T->Height = 1 + max(GetHeight(T->Left), GetHeight(T->Right));
    newRoot->Height = 1 + max(GetHeight(newRoot->Left), GetHeight(newRoot->Right));
    return newRoot;
}


// 插入
AVLTree Insert(AVLTree T, TreeElementType X) {
    if (T == NULL) {
        // 创建新结点
        T = (AVLTree)malloc(sizeof(AVLTNode));
        T->Data = X;
        T->Left = T->Right = NULL;
        T->Height = 0; // 新结点高度为0
    } else if (X < T->Data) {
        T->Left = Insert(T->Left, X); // 在左子树中插入
    } else if (X > T->Data) {
        T->Right = Insert(T->Right, X); // 在右子树中插入
    } else {
        return T; // 不允许插入重复元素
    }
    // 更新高度
    T->Height = 1 + max(GetHeight(T->Left), GetHeight(T->Right));
    // 检查平衡因子并进行旋转调整
    int balanceFactor = GetBalanceFactor(T);
    if(balanceFactor > 1){
        if(X < T->Left->Data){ // LL情况
            return RotateRight(T);
        } else { // LR情况
            T->Left = RotateLeft(T->Left);
            return RotateRight(T);
        }
    } else if(balanceFactor < -1){
        if(X > T->Right->Data){ // RR情况
            return RotateLeft(T);
        } else { // RL情况
            T->Right = RotateRight(T->Right);
            return RotateLeft(T);
        }
    }
    return T; // 返回更新后的树根结点
}

