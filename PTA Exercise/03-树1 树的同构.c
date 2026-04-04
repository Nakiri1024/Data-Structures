#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

const int MaxSize = 10;
#define null -1

typedef char TreeElementType;
typedef int Position;

// 二叉树
typedef struct TNode{
    TreeElementType Data;
    Position Left;
    Position Right;
} BinTree;


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
        scanf("\n%c %c %c", &BT[i].Data, &left, &right);
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

bool JudgeSameStructure(BinTree BT1[], BinTree BT2[], Position root1, Position root2){
    // 两棵树都为空
    if(root1 == null && root2 == null){
        return true;
    }
    // 一棵树为空，另一棵树不为空
    if(root1 == null || root2 == null){
        return false;
    }
    // 两棵树根不同
    if(BT1[root1].Data != BT2[root2].Data){
        return false;
    }
    // 递归比较左右子树
    // 结构相同：左子树与左子树相同，右子树与右子树相同
    // 结构镜像：左子树与右子树相同，右子树与左子树相同
    return (JudgeSameStructure(BT1, BT2, BT1[root1].Left, BT2[root2].Left) &&
            JudgeSameStructure(BT1, BT2, BT1[root1].Right, BT2[root2].Right)) ||
           (JudgeSameStructure(BT1, BT2, BT1[root1].Left, BT2[root2].Right) &&
            JudgeSameStructure(BT1, BT2, BT1[root1].Right, BT2[root2].Left));
}


int main(){
    BinTree BT1[MaxSize], BT2[MaxSize];
    Position root1 = BuildTree(BT1);
    Position root2 = BuildTree(BT2);

    if(JudgeSameStructure(BT1, BT2, root1, root2)){
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}