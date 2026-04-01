#include <stdio.h>

#define MAX_ADDR 100000

typedef struct {
    int data;
    int next;
    int exist;
} Node;

void Reverse(int arr[], int l, int r) {
    while (l < r) {
        int t = arr[l];
        arr[l] = arr[r];
        arr[r] = t;
        l++;
        r--;
    }
}

int main() {
    int head, n, k;
    Node nodes[MAX_ADDR] = {0}; // 地址表
    int order[MAX_ADDR]; // 存储链表节点地址的数组
    int len = 0;

    scanf("%d %d %d", &head, &n, &k);

    for (int i = 0; i < n; i++) {
        int addr, data, next;
        scanf("%d %d %d", &addr, &data, &next);
        nodes[addr].data = data;
        nodes[addr].next = next;
        nodes[addr].exist = 1;
    }

    // 按可达路径重建顺序
    for (int p = head; p != -1 && nodes[p].exist; p = nodes[p].next) {
        order[len++] = p;
    }

    // 反转每 k 个节点
    for (int i = 0; i + k <= len; i += k) {
        Reverseq(order, i, i + k - 1);
    }

    for (int i = 0; i < len; i++) {
        int addr = order[i];
        int next = (i == len - 1) ? -1 : order[i + 1];
        if (next == -1) {
            printf("%05d %d -1\n", addr, nodes[addr].data);
        } else {
            printf("%05d %d %05d\n", addr, nodes[addr].data, next);
        }
    }

    return 0;
}