#include <stdio.h>

int MaxSubseqSum( int a[], int n, int *left, int *right){
    int maxS = -1, thisS = 0;
    int tmpl = 0;
    for(int i = 0; i < n; i++){
        thisS += a[i];
        if(thisS > maxS){
            maxS = thisS;
            *right = i;
            *left = tmpl;
        }
        else if(thisS < 0){ // 如果当前子列和小于0，则不可能使后面的部分和更大，抛弃之
            thisS = 0;
            tmpl = i + 1;
        }
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


    int left = 0, right = n - 1;
    int maxS = MaxSubseqSum(a, n, &left, &right);


    if(maxS >= 0)
        printf("%d %d %d\n", maxS, a[left], a[right]);
    else
        printf("0 %d %d\n", a[0], a[n - 1]);
    return 0;
}