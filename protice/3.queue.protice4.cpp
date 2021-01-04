/*************************************************************************
	> File Name: 3.queue.protice4.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月04日 星期一 20时54分13秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
 
typedef struct Queue {
    int *data;
    int size, head, tail, cnt;
} Queue;

Queue *init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->size = n;
    q->head = q->tail = q->cnt = 0;
    return q;
}

int expend(Queue *q) {
    int extr_size = q->size;
    int *p;
    while(extr_size) {
        p = (int *)malloc(sizeof(int) * (q->size + extr_size));
        if (p) break;
        extr_size /= 2;
    }
    if (p == NULL) return 0;
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
        printf("\033[32mexpend successful!\033[0m""size = %d\n", q->size);
    }
    q->data[q->tail++] = val;
    if (q->tail == q->size) q->tail = 0;
    q->cnt += 1;
    return 1;
}

int front(Queue *q) {
    return q->data[q->head];
}

int empty(Queue *q) {
    return q->cnt == 0;
}

int pop(Queue *q) {
    if (q == NULL) return 0;
    if (!empty(q)) return 0;
    q->head++;
    if (q->head == q->size) q->head = 0;
    q->cnt -= 1;
    return 1;
}

void output(Queue *q) {
    int i = q->head;
    for (int j = 0; j < q->cnt; j++) {
        j && printf(", ");
        printf("%d", q->data[(i + j) % q->size]);
    }
    return ;
}

void clear(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

int main() {
 
 
    return 0;
}
