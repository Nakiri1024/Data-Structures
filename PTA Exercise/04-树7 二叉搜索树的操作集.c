#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal( BinTree BT );  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}
/* 你的代码将被嵌在这里 */
// 查找(非递归法)
Position Find(BinTree BST, ElementType X) {
    while (BST != NULL && BST->Data != X) {
        if (X < BST->Data) {
            BST = BST->Left; // 转向左子树
        } else {
            BST = BST->Right; // 转向右子树
        }
    }
    return BST; // 找到结点或没有找到结点
}

// 插入
BinTree Insert(BinTree BST, ElementType X) {
    if (BST == NULL) {
        // 创建新结点
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    } else if (X < BST->Data) {
        BST->Left = Insert(BST->Left, X); // 在左子树中插入
    } else if (X > BST->Data) {
        BST->Right = Insert(BST->Right, X); // 在右子树中插入
    }
    return BST; // 返回更新后的树根结点
}

// 查找最小结点
Position FindMin(BinTree BST) {
    if (BST == NULL) {
        return NULL; // 树为空
    }
    while (BST->Left != NULL) {
        BST = BST->Left; // 转向左子树
    }
    return BST; // 返回最小结点
}
// 查找最大结点
Position FindMax(BinTree BST) {
    if (BST == NULL) {
        return NULL; // 树为空
    }
    while (BST->Right != NULL) {
        BST = BST->Right; // 转向右子树
    }
    return BST; // 返回最大结点
}

// 删除
BinTree Delete(BinTree BST, ElementType X) {
    if (BST == NULL) { // 树为空， 没有结点可删除
        printf("Not Found\n");
        return NULL;
    }
    if (X < BST->Data) {
        BST->Left = Delete(BST->Left, X); // 在左子树中删除
    } else if (X > BST->Data) {
        BST->Right = Delete(BST->Right, X); // 在右子树中删除
    } else { // 找到要删除的结点
        if (BST->Left != NULL && BST->Right != NULL) { // 有两个子结点
            // 找到右子树中的最小结点替换当前结点的值，并删除右子树中的最小结点
            // 也可以选择左子树中的最大结点进行替换，方法类似
            Position minNode = FindMin(BST->Right); // 找到右子树中的最小结点
            BST->Data = minNode->Data; // 用最小结点的值替换当前结点的值
            BST->Right = Delete(BST->Right, minNode->Data); // 删除右子树中的最小结点
        } else { // 只有一个子结点或没有子结点
            Position temp = BST;
            if (BST->Left != NULL) {
                BST = BST->Left; // 转向左子树
            } else {
                BST = BST->Right; // 转向右子树
            }
            free(temp); // 释放被删除结点的内存
        }
    }
    return BST; // 返回更新后的树根结点
}