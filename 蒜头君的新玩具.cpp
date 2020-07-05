/*************************************************************************
	> File Name: 9.Heap.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri Jul  3 11:38:37 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b), (b) = __temp;\
}

typedef struct Heap {
    double *data;
    int size,length;
} Heap;

Heap *init(int n) {
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->data = (double *)malloc(sizeof(double) * n);
    h->size = 0;
    h->length = n;
    return h;
}

void push(Heap *h, double value) { 
    if (h->size  >= h->length) return ;
    h->data[h->size] = value;
    int current = h->size;
    int father = (current - 1) / 2;
    while (h->data[current] > h->data[father]) {
        swap(h->data[current], h->data[father]);
        current = father;
        father = (current - 1) / 2;
    }
    h->size++;
    return ;
}

double top(Heap *h) {
    return h->data[0];
}

void update(Heap *h, int pos, int n) {
    int lchild = 2 * pos + 1, rchild = 2 * pos + 2;
    int max_value = pos;
    if (lchild < n && h->data[lchild] > h->data[max_value]) {
        max_value = lchild;
    }
    if (rchild < n && h->data[rchild] > h->data[max_value]) {
        max_value = rchild;
    }
    if (max_value != pos) {
        swap(h->data[pos], h->data[max_value]);
        update(h, max_value, n);
    }
}

void pop(Heap *h) {
    if (h->size == 0) return ;
    swap(h->data[0], h->data[h->size - 1]);
    h->size--;
    update(h, 0, h->size);
}

int heap_size(Heap *h) {
    return h->size;
}

void clear(Heap *h) {
    if (h == NULL) return ;
    free(h->data);
    free(h);
    return ;
}

int main() {
    int n;
    double value;
    scanf("%d", &n);
    Heap *heap = init(n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &value);
        push(heap, value);
    }
    while (heap_size(heap) > 1) {
        double a = top(heap);
        pop(heap);
        double b = top(heap);
        pop(heap);
        double v = pow(a , 1.0 / 3.0) * pow(b, 2.0 / 3.0);
        push(heap, v);        
    }
    printf("%.12lf\n", top(heap));
    clear(heap);
    return 0;
}
