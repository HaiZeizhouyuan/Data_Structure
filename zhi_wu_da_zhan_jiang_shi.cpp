/*************************************************************************
	> File Name: zhi_wu_da_zhan_jiang_shi.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri Jul  3 19:55:31 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define max_n 500
#define max_m 100
#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b), (b) = __temp;\
}

typedef struct Node {
    int ind, f, s;
} Node;

typedef struct Heap {
    double *data;
    int size, length;   
} Heap;

Heap *init(int n) {
    Heap *h = (Heap *)calloc(n, sizeof(Heap));
    h->data = (double *)calloc(n, sizeof(double) * n);
    h->size = n;
    h->length = 0;
    return h;
}

void push(Heap *h, double val) {
    if (h == NULL) return ;
    if (h->length >= h->size) return ;
    h->data[h->length] = val;
    int cur = h->length;
    int father = (cur - 1) / 2;
    while (h->data[cur] > h->data[father]) {
        swap(h->data[cur], h->data[father]);
        cur = father;
        father = (cur - 1) / 2;
    }
    h->length += 1;
    return ;
}

double top(Heap *h) {
    return h->data[0];
}

int empty(Heap *h) {
    return h->length == 0;
}

void updata(Heap *h, int pos, int n){
    int lchild = pos * 2 + 1 , rchild = pos * 2 + 2, max = pos;
    if (lchild < n && h->data[lchild] > h->data[max]) max = lchild;
    if (rchild < n && h->data[rchild] > h->data[max]) max = rchild;
    if (max - pos) {
        swap(pos, max);
        updata(h, max, n);
    }
    return ;
}

void pop(Heap *h) {
    if (h == NULL) return ;
    if (h->length == 0) return ;
    swap(h->data[0], h->data[h->length - 1]);
    h->length -= 1;
    updata(h, 0, h->length);
    return ;
}

void clear(Heap *h) {
    if (h == NULL) return ;
    free(h->data);
    free(h);
    return ;
}

int main() {
    int t, n, f, s;
    scanf("%d", &t);
    Node node[t + 5];
    for (int i = 1; i <= t; i++) {
        scanf("%d", &n);
        Heap *h = init(n);
        for (int j = 0; j < n; j++) {
            scanf("%d%d", &node[j].f, &node[j].s);
            node.ind = j + 1;
            printf("Case #%d:\n", i);
            push(h, );
        }
    }
    clear(h);
    return 0;
}
