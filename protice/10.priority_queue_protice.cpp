/*************************************************************************
	> File Name: 10.priority_queue_protice.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu Jul 16 19:15:37 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b), (b) = __temp;\
}

typedef struct priority_queue {
    int *data;
    int size, cnt;
} priority_queue;

priority_queue *getQueue(int n) {
    priority_queue *p = (priority_queue *)malloc(sizeof(priority_queue));
    p->data = (int *)malloc(sizeof(int) * (n + 1));
    p->cnt = 0;
    p->size = n;
    return p;
}

int empty(priority_queue *p) {
    return p->cnt == 0;
}

int top(priority_queue *p) {
    return p->data[1];
}

int push(priority_queue *p, int val) {
    if (p == NULL) return 0;
    if (p->cnt == p->size) return 0;
    p->data[++(p->cnt)] = val;
    int ind = p->cnt;
    while(ind >> 1 && p->data[ind] > p->data[ind >> 1]) {
        swap(p->data[ind],p->data[ind >> 1]);
        ind >>= 1;
    }
    return 1;
}

void updata(priority_queue *p, int ind) {
    while ((ind << 1) <= p->cnt) {
        int max = ind, l = ind << 1, r = ind << 1 | 1;
        if (l < p->cnt && p->data[max] < p->data[l]) max = l;
        if (r < p->cnt && p->data[max] < p->data[r]) max = r;
        if (max == ind) break;
        swap(p->data[max], p->data[ind]);
        ind = max;
    }
    return ;
}

int pop(priority_queue *p) {
    if (p == NULL) return 0;
    if (empty(p)) return 0;
    p->data[1] = p->data[p->cnt--];
    updata(p, 1);
    return 1;
}

void clear(priority_queue *p) {
    if (p == NULL) return ;
    free(p->data);
    free(p);
    return ;
}

void output(priority_queue *p) {
    for (int i = 1; i <= p->cnt; i++) {
        i - 1 && printf(" ");
        printf("%d", p->data[i]);
    }
    printf("\n");
    return ;
}

int main() {
    srand(time(0));
    #define max_op 20
    priority_queue *p = getQueue(max_op);
    for (int i = 0; i < 10; i++) {
        int val = rand() % 100;
        int flag = push(p, val);
        printf("insert %d to priority_queue = %s\n", val, flag ? "success" : "failed");
    }
    output(p);
    clear(p);
    return 0;
}
