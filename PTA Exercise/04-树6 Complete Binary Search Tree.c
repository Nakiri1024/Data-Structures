#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef int ElementType;
typedef int Position;
const int MaxSize = 1001;

ElementType compare(const void *a, const void *b){
    return *(ElementType*)a - *(ElementType*)b;
}


// 计算n个结点的完全二叉树的左子树结点个数
int GetLeftSubtreeSize(int n) {
    int h = (int)log2(n) + 1;// 完全二叉树的高度
    int maxNodesAtLastLevel = (int)pow(2, h - 1); // 最后一层的最大结点数
    int nodesBeforeLastLevel = (int)pow(2, h - 1) - 1; // 最后一层之前的结点数
    int nodesInLastLevel = n - nodesBeforeLastLevel; // 最后一层实际结点数
    return nodesInLastLevel >= maxNodesAtLastLevel / 2 ?
              nodesBeforeLastLevel : // 最后一层结点数超过一半，左子树满
              nodesBeforeLastLevel / 2 + nodesInLastLevel; // 最后一层结点数不超过一半，左子树不满
}

void BuildCBST(ElementType Value[], ElementType CBST[], Position root, Position start, Position end){
    if(start > end){
        return; // 递归终止条件
    }
    int leftSize = GetLeftSubtreeSize(end - start + 1); // 左子树结点个数
    CBST[root] = Value[start + leftSize]; // 根结点
    BuildCBST(Value, CBST, 2 * root, start, start + leftSize - 1); // 构建左子树
    BuildCBST(Value, CBST, 2 * root + 1, start + leftSize + 1, end); // 构建右子树
}


int main(){
    ElementType Value[MaxSize], CBST[MaxSize];
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &Value[i]);
    }
    // 升序排序
    qsort(Value, N, sizeof(ElementType), compare);

    // 构建完全二叉搜索树
    BuildCBST(Value, CBST, 1, 0, N - 1);
    // 输出层序遍历结果
    for(int i = 1; i <= N; i++){
        printf("%d", CBST[i]);
        if(i != N){
            printf(" ");
        }
    }

    return 0;
}