/*************************************************************************
	> File Name: 10.priority_queue.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat Jul  4 15:24:21 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b), (b) = __temp;\
}

typedef struct priority_queue {
    int *data;
    int cnt, size;
} priority_queue;

priority_queue *init(int n) {
    priority_queue *q = (priority_queue *)malloc(sizeof(priority_queue));
    q->data = (int *)malloc(sizeof(int) * (n  + 1));
    q->cnt = 0;
    q->size = n;
    return q;
}

int empty(priority_queue *q) {
    return q->cnt == 0;
}

int top(priority_queue *q) {
    return q->data[1];
}

int push(priority_queue *q, int val) {
    if (q == NULL) return 0;
    if (q->cnt >= q->size) return 0;
    q->data[++(q->cnt)] = val;
    int ind = q->cnt;
    while (ind >> 1 && q->data[ind] > q->data[ind >> 1]) {
        swap(q->data[ind], q->data[ind >> 1]);
        ind >>= 1;
    }
    return 1;
}

void update(priority_queue *q, int ind) {
    while ((ind << 1) <= q->cnt) {
        int max = ind, l = ind << 1, r = ind << 1 | 1;
        if (l < q->cnt && q->data[l] > q->data[max]) max = l;
        if (l < q->cnt && q->data[r] > q->data[max]) max = r;
        if (max == ind) break;
        swap(q->data[ind], q->data[max]);
        ind = max;
    }
    return ;
}

int pop(priority_queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0;
    q->data[1] = q->data[q->cnt--];
    update(q, 1);
    return 1;
}

void output(priority_queue *q) {
    for (int i = 1; i < q->cnt; i++) {
        i - 1 && printf(" ");
        printf("%d", q->data[i]);
    }
    printf("\n");
}

void clear(priority_queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

int main () {
    srand (time(0));
    #define max_op 20
    priority_queue *q = init(max_op);
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        push(q, val);
        printf("insert %d to priority_queue\n", val);
    }
    output(q);
    clear(q);
    return 0;
}
