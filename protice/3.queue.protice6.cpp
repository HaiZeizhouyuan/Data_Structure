/*************************************************************************
	> File Name: 3.queue.protice6.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月05日 星期二 17时14分36秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;

typedef struct Queue{
    int *data;
    int head, tail, cnt, size;
}Queue;

Queue *getNewQue(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->head = q->tail = q->cnt = 0;
    q->size = n;
    return q;
}

int expend(Queue *q) {
    int extr_size = q->size;
    int *p;
    while(extr_size) {
        p = (int *)malloc(sizeof(int) * (extr_size + q->size));
        if(p) break;
        extr_size /= 2;
    }
    if (p == NULL) return 0;
    int i = q->head;
    for (int j = 0; j < q->cnt; j++) {
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
        printf("expend Queueu is success!");
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
    q->head += 1;
    if (q->head == q->size) q->head = 0;
    q->cnt -= 1;
    return 1;
}

void output(Queue *q) {
    int i = q->head;
    for (int j = 0; j < q->cnt; j++) {
        printf("%d", q->data[(i + j) % q->size]);
    }
    printf("\n");
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
