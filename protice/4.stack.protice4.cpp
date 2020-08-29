/*************************************************************************
	> File Name: 4.stack.protice4.cpp
	> Author: zhouyuan
	> Mail: 
	> Created Time: 2020年08月28日 星期五 10时11分28秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Queue {
    int *data;
    int size, head, tail, total;
}Queue;

Queue *getNewQueue (int size) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * size);
    q->total = q->head = q->tail = 0;
    q->size = size;
    return q;
}

int expend(Queue *q) {
    int extr_size = q->size;
    int *p;
    while(extr_size) {
        p = (int *)malloc(sizeof(int *) * (extr_size + q->size));
        if (p) break;
        extr_size >>= 1;
    }
    if (p == NULL) return 0; 
    for (int i = q->head, j = 0; j < q->size; j++) {
        p[j] = q->data[(i + j) % q->size];
    }
    free(q->data);
    q->data = p;
    q->size += extr_size;
    q->head = 0;
    q->tail = q->total;
    return 1;
}

int push(Queue *q, int val) {
    if (q == NULL) return 0;
    if (q->total == q->size) {
        if (!expend(q)) return 0;
        printf("\033[32mexpend Queue is success, and new size is %d\n\n\033[0m", q->size);
    }
    q->data[q->tail++] = val;
    q->total += 1;
    if (q->tail == q->size) q->tail -= q->size;
    return 1;
}

int front(Queue *q) {
    return q->data[q->head];
}

int empty(Queue *q) {
    return q->total == 0;
}

int pop(Queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0;
    q->head += 1;
    q->total -= 1;
    if (q->head == q->size) q->head -= q->size;
    return 1;
}

void output(Queue *q) {
    printf("Queue(%d) : [", q->size);
    for (int i = q->head, j = 0; j < q->total; j++) {
        j && printf(",");
        printf("%d", q->data[(i + j) % q->size]);
    }
    printf("]\n\n");
}

void clear(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

int main() {
    srand(time(0));
    #define max_op 20
    Queue *q = getNewQueue(10);
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        int op = rand() % 4;
        switch(op) {
            case 0:
            case 1:
            case 2:
            printf("push %d to Queue is %s \n", val, push(q, val) ? "success" : "failed");
                break;
            case 3:
                int f = front(q);
            printf("pop %d from Queue is %s\n", f, pop(q) ? "success" : "failed");
                break;
        }
        output(q);
    }
    clear(q);
    #undef max_op
 
    return 0;
}
