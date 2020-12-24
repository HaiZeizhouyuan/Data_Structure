/*************************************************************************
	> File Name: 11.heap_protice1.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年09月13日 星期日 15时36分33秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
 
#define swap(a, b) {\
    __typeof(a) __tmp = (a);\
    (a) = (b), (b) = __tmp;\
}

typedef struct priority_queue {
    int *data;
    int cnt, size;
} priority_queue;

priority_queue *init(int size) {
    priority_queue *q = (priority_queue *)malloc(sizeof(priority_queue));
    q->data = (int *)malloc(sizeof(int) * size);
    q->cnt = 0;
    q->size = size;
    return q;
}

void expendqueue(priority_queue *q) {
    q->data = (int *)realloc(q->data, sizeof(int) * q->size * 2);
    q->size *= 2;
    return ;
}

int push(priority_queue *q, int val) {
    if (q == NULL) return 0;
    if (q->cnt >= q->size) {
        printf("queue no expend size is %d\n", q->size);
        expendqueue(q);
        printf("expend queue is success, queue size is %d\n", q->size);
    }
    q->data[++(q->cnt)] = val;
    int ind = q->cnt;
    while(ind >> 1 && q->data[ind] > q->data[ind >> 1]) {
        swap(q->data[ind], q->data[ind >> 1]);
        ind >>= 1;
    }
    return 1;
}

int empty(priority_queue *q) {
    return q->cnt == 0;
}

int front(priority_queue *q) {
    return q->data[1];
}

void downupdata(priority_queue *q, int ind, int n) {
    while((ind << 1) <= n) {
        int tmp = ind, l = ind << 1, r = ind << 1 | 1;
        if (l <= n && q->data[l] > q->data[tmp]) tmp = l;
        if (r <= n && q->data[r] > q->data[tmp]) tmp = r;
        if (tmp == ind) break;
        swap(q->data[tmp], q->data[ind]);
        ind = tmp;
    }
    return ;
}

int pop(priority_queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0;
    q->data[1] = q->data[q->cnt--];
    downupdata(q, 1, q->cnt);
    return 1;
}

void output(priority_queue *q) {
    for (int i = 1; i <= q->cnt; i++) {
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

void heap_sort(priority_queue *q) {
    for (int i = q->cnt; i > 1; i--) {
        swap(q->data[i], q->data[1]);
        downupdata(q, 1, i - 1);
    }
    return ;
}

int main() {
    srand(time(0));
    #define max_op 20
    priority_queue *q = init(max_op);
    for (int i = 0; i < max_op; i++) {
        int op = rand() % 2;
        int val = rand() % 100;
        if (op == 0) {
            int flag = push(q, val);
            printf("push %d to priority_queue is %s!\n", val, flag ? "success" : "failed");
        } else {
            int flag = pop(q);
            int f = front(q);
            printf("pop %d from priority_queue is %s!\n", f, flag ? "success" : "failed");
        }
    }
    output(q);
    heap_sort(q);
    output(q);
    clear(q);
    #undef max_op
    return 0;
}
