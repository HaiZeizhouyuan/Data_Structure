/*************************************************************************
	> File Name: 3.queue.project.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue Jun 23 14:48:08 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Queue {
    int *data;
    int size, head, tail, uns;
} Queue;

Queue *init(int);
int push(Queue *, int);
int pop(Queue *);
int expend(Queue *);
int front(Queue *);
int empty(Queue *);
void clear(Queue *);
void output(Queue *);
int main() {
    #define max_op 20
    Queue *q = init(10);
    srand(time(0));
    for (int i = 0; i < max_op; i++) {
        int op = rand() % 4;
        int val = rand() % 100;
        switch(op) {
            case 0:
            case 1:
            case 2: {
                printf("push %d to Queue is %d\n", val, push(q, val));
            } break;
            case 3: {
                int f = front(q);
                printf("pop %d from Quue is %d\n",f , pop(q));
            } break;
        }
    output(q);
    }
    #undef max_op
    clear(q);
    return 0;
}

Queue *init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->size = n;
    q->head = q->tail = q->uns = 0;
    return q;
}


int expend(Queue *q) {
    int extr_size = q->size;
    int *p;
    while (extr_size) {
        p = (int *)malloc(sizeof(int) * (q->size + extr_size));
        if (p) break;
        extr_size >>= 1;
    }
    if (p == NULL) return 0;
    for (int i = q->head, j = 0; j < q->uns; j++) {
        p[j] = q->data[(i + j) % q->size];
    }
    
    free(q->data);
    q->data = p;
    q->size += extr_size;
    q->head = 0;
    q->tail = q->uns;
    return 1;
}

int empty(Queue *q) {
    return q->uns == 0;
}

int front (Queue *q) {
    return q->data[q->head];
}

int push(Queue *q, int val) {
    if(q == NULL) return 0;
    if (q->uns == q->size) {
        if (!expend(q)) return 0;
        else printf("\033[32mexpend is success! size is %d\n\n\033[0m", q->size);
    }
    q->data[q->tail++] = val;
    if (q->tail == q->size) q->tail -= q->size;
    q->uns += 1;
    return 1;
}

int pop(Queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0;
    q->head += 1;
    if(q->head == q->size) q->head -= q->size;
    q->uns -=1;
    return 1;
}

void output(Queue *q) {
    printf("Queue[%d] : [", q->uns);
    for (int i = q->head, j = 0; j < q->uns; j++) {
        j && printf(", ");
        printf("%d", q->data[(i + j) % q->size]);
    }
    printf("]\n\n");
    return ;
}
void clear(Queue *q) {
    if(q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}
