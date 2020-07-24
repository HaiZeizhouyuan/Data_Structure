/*************************************************************************
	> File Name: 3.queue.protice1.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue Jul 21 16:32:23 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Queue {
    int *data;
    int cnt, size, head, tail;
} Queue;

Queue *getNewQueue(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->size = n;
    q->head = q->tail = q->cnt = 0;
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
    if (extr_size == 0) return 0;
    int i = q->head;
    for (int j = 0; j < q->cnt; j++) p[j] = q->data[(i + j) % q->size];
    free(q->data);
    q->data = p;
    q->head = 0;
    q->size += extr_size;
    q->tail = q->cnt;
    return 1;
}

int push(Queue *q, int loc, int val) {
    if (q == NULL) return 0;
    if (q->cnt = q->size) {
        expend(q);
    }
}

void clear(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}
