#include <stdio.h>

int MaxSubseqSum( int a[], int n){
    int maxS = 0, thisS = 0;
    for(int i = 0; i < n; i++){
        thisS += a[i];
        if(thisS > maxS)
            maxS = thisS;
        else if(thisS < 0) // 如果当前子列和小于0，则不可能使后面的部分和更大，抛弃之
            thisS = 0;
    }
    return maxS;
}

int main(){
    int n = 0;
    scanf("%d", &n);
    int a[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    printf("%d\n", MaxSubseqSum(a, n));
    return 0;
}