/*************************************************************************
	> File Name: 3.queue.protice3.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri Jul 24 19:01:24 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Queue {
    int *data;
    int size, cnt, head, tail;
} Queue;

Queue *getNewQueue (int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->size = n;
    q->cnt = q->head = q->tail = 0;
    return q;
} 

int front (Queue *q) {
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
    if (!extr_size) return 0;
    for (int i = q->head, j = 0; j < q->cnt; j++) {
        p[j] = q->data[(i + j) % q->size];
    }
    free(q->data);
    q->data = p;
    q->size += extr_size;
    q->head = 0;
    q->tail = q->cnt;
    return 1;
}

int push(Queue *q, int val) {
    if (q == NULL) return 0;
    if (q->cnt == q->size) {
        if (!expend(q)) return 0;
        printf("\033[34mexpend the queue is success! and the new size is %d\n\033[0m", q->size);
    }
    q->data[(q->tail)++] = val;
    if (q->tail == q->size) q->tail -= q->size;
    q->cnt += 1;
    return 1;
}

int pop(Queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0;
    q->head += 1;
    if (q->head == q->size) q->head -= q->size;
    q->cnt -= 1;
    return 1;
}


void output(Queue *q) {
    printf("Queue :[");
    for (int i = q->head, j = 0; j < q->cnt; j++) {
        j && printf(",");
        printf("%d", q->data[(i + j) % q->size]);
    }
    printf("]\n\n");
    return ;
}

void clear(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

int main () {
    srand(time(0));
    #define max_op 20
    Queue *q = getNewQueue(max_op);
    for (int i = 0; i < 40; i++) {
        int val = rand() % 100;
        int op = rand() % 4;
        switch(op) {
            case 0:
            case 1:
            case 2:{
                printf("push %d to Queue is %s\n", val, push(q, val) ? "success" : "failed");}
                break;
            case 3:{
                int f = front(q);
                printf("pop %d from Queue is %s\n", f, pop(q) ? "success" : "failed");
                } break;
        }
        output(q);
    }
    #undef max_op
    clear(q);
    return 0;
}
