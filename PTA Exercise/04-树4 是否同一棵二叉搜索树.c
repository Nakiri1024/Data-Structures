#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int TreeElementType;


// 二叉树
typedef struct TNode{
    TreeElementType Data;
    struct TNode* Left;
    struct TNode* Right;
    bool visited;
} *BinTree, TNode;
typedef BinTree Position;

// 二叉搜索树

// 插入
BinTree Insert(BinTree BST, TreeElementType X) {
    if (BST == NULL) {
        // 创建新结点
        BST = (BinTree)malloc(sizeof(TNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    } else if (X < BST->Data) {
        BST->Left = Insert(BST->Left, X); // 在左子树中插入
    } else if (X > BST->Data) {
        BST->Right = Insert(BST->Right, X); // 在右子树中插入
    }
    return BST; // 返回更新后的树根结点
}


BinTree BuildTree(int N) {
    BinTree BST = NULL;
    for (int i = 0; i < N; i++) {
        TreeElementType value;
        scanf("%d", &value);
        BST = Insert(BST, value); // 插入结点
    }
    return BST;
}

bool Check(BinTree BST, TreeElementType value){
    if(BST->visited){
        if(value < BST->Data){
            return Check(BST->Left, value);
        }else if(value > BST->Data){
            return Check(BST->Right, value);
        }else{
            return false; // 已访问过的结点值相同，说明不是同一棵树
        }
    }else{
        if(BST->Data == value){
            BST->visited = true; // 标记结点为已访问
            return true;
        }else{
            return false; // 结点值不匹配，说明不是同一棵树
        }
    }
}

bool IsSameTree(BinTree BST, int N){
    TreeElementType root_value;
    bool flag = true;
    scanf("%d", &root_value);
    if(BST == NULL || BST->Data != root_value){
        flag = false;
    }else{
        BST->visited = true;
    }
    for(int i = 1; i < N; i++){
        TreeElementType value;
        scanf("%d", &value);
        if(flag && !Check(BST, value)){
            flag = false;
        }
    }
    return flag;
}

void ResetVisited(BinTree BST){
    if(BST != NULL){
        BST->visited = false;
        ResetVisited(BST->Left);
        ResetVisited(BST->Right);
    }
}

void FreeTree(BinTree BST){
    if(BST != NULL){
        FreeTree(BST->Left);
        FreeTree(BST->Right);
        free(BST);
    }
}

int main(){
    int N, L;
    scanf("%d", &N);
    while(N){
        scanf("%d", &L);
        BinTree BST = BuildTree(N);
        for(int i = 0; i < L; i++){
            if(IsSameTree(BST, N)){
                printf("Yes\n");
            }else{
                printf("No\n");
            }
            ResetVisited(BST); // 重置访问标记以便下一次检查
        }
        FreeTree(BST); // 释放树内存
        scanf("%d", &N);
    }
    return 0;
}