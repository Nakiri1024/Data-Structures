
// 算法1，暴力枚举，时间复杂度 O(n^3)
int MaxSubseqSum1( int a[], int n){
    int maxS = 0;
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            int sum = 0;
            for(int k = i; k <= j; k++)
                sum += a[k];
            if(sum > maxS)
                maxS = sum;
        }
    }
    return maxS;
}

// 算法2，改进的暴力枚举，时间复杂度 O(n^2)
int MaxSubseqSum2( int a[], int n){
    int maxS = 0;
    for(int i = 0; i < n; i++){
        int sum = 0;
        for(int j = i; j < n; j++){
            sum += a[j];
            if(sum > maxS)
                maxS = sum;
        }
    }
    return maxS;
}

// 算法3，分治法，时间复杂度 O(nlogn)
// 返回三个数中的最大值(左右最大子列和，跨界最大子列和)
int max3(int a, int b, int c){
    int max = a > b ? a : b;
    return max > c ? max : c;
}

// 分而治之，递归
int DivideAndConquer( int a[], int left, int right){
    // 只有一个元素时，如果它是正数，返回它，否则返回0
    if(left == right)
        return a[left] > 0 ? a[left] : 0;
    
    // 分，求得左右两边的最大子序列和
    int center = (left + right) / 2;
    int maxLeftSum = DivideAndConquer(a, left, center);
    int maxRightSum = DivideAndConquer(a, center + 1, right);

    // 计算跨越中心的最大子序列和
    // 从中心向左扫描，求得左边的最大子列和
    int maxLeftBorderSum = 0, leftBorderSum = 0;
    for(int i = center; i >= left; i--){
        leftBorderSum += a[i];
        if(leftBorderSum > maxLeftBorderSum)
            maxLeftBorderSum = leftBorderSum;
    }
    // 从中心向右扫描，求得右边的最大子列和
    int maxRightBorderSum = 0, rightBorderSum = 0;
    for(int i = center + 1; i <= right; i++){
        rightBorderSum += a[i];
        if(rightBorderSum > maxRightBorderSum)
            maxRightBorderSum = rightBorderSum;
    }
    // 治
    return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}
int MaxSubseqSum3( int a[], int n){
    return DivideAndConquer(a, 0, n - 1);
}

// 算法4，在线处理，时间复杂度 O(n)
int MaxSubseqSum4( int a[], int n){
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
