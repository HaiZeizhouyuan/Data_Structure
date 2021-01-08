/*************************************************************************
	> File Name: 10.priority_queue_protice3.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月08日 星期五 20时43分32秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define swap(a, b){\
    __typeof(a) __temp = (a);\
    (a) = (b), (b) = __temp;\
}


typedef struct priority_Queue {
    int *data;
    int size, cnt;
}priority_Queue;

priority_Queue *init(int n) {
    priority_Queue *q = (priority_Queue *)malloc(sizeof(priority_Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->size = n;
    q->cnt = 0;
    return q;
}

void update(priority_Queue *q, int ind) {
    while((ind << 1) <= q->cnt) {
        int temp = ind, l = ind << 1, r = ind << 1 | 1;
        if (l <= q->cnt && q->data[l] > q->data[temp]) temp = l;
        if (r <= q->cnt && q->data[r] > q->data[temp]) temp = r;
        if (temp == ind) break;
        swap(q->data[temp], q->data[ind]);
        ind = temp;
    }
}

int push(priority_Queue *q, int val) {
    if (q == NULL) return 0;
    if (q->cnt == q->size) return 0;
    q->data[++(q->cnt)] = val;
    int ind = q->cnt;
    while(ind << 1 & q->data[ind] > q->data[ind >> 1]) {
        swap(q->data[ind], q->data[ind >> 1]);
        ind >>= 1;
    }
    return 1;
}

int top(priority_Queue *q) {
    return q->data[1];
}


int empty(priority_Queue *q) {
    return q->cnt == 0;
}


int pop(priority_Queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0;
    q->data[1] = q->data[q->cnt--];
    update(q, 1);
    return 1;
}

void output(priority_Queue *q) {
    for (int i = 1; i <= q->cnt; i++) {
        (i - 1) && printf(", ");
        printf("%d", q->data[i]);
    }
    printf("\n");
}

void clear(priority_Queue *q) {
    if(q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}


int main() {
    priority_Queue *q = init(20);
    for (int i = 0; i < 20; i++) {
        printf("%d ", top(q));
        pop(q);
    }
    clear(q);
    return 0;
}
