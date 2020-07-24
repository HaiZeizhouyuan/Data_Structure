/*************************************************************************
	> File Name: 3.queue.protice2.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu Jul 23 17:58:22 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct queue {
    int *data;
    int size, cnt, head, tail;
} Queue;

Queue *getNewQueue(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->size = n;
    q->cnt = q->head = q->tail = 0;
    return q;
}

int front(Queue *q) {
    return q->data[q->head];
}

int empty(Queue *q) {
    return q->cnt == 0;
}

int expend(Queue *q) {
    int extr_size = q->size;
    int *p;
    while (extr_size) {
        p = (int *)malloc(sizeof(int) * (extr_size + q->size));
        if (p) break;
        extr_size >>= 1;
    }
    if (!p) break;

}

int push(Queue *q, int val) {
    if (q == NULL) return 0;
}

void clear(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
}

int main () {
    return 0;
}
