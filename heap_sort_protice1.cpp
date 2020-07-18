/*************************************************************************
	> File Name: heap_sort_protice1.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu Jul 16 20:20:23 2020
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
    int cnt, size;
} priority_queue;

priority_queue *init(int n) {
    priority_queue *q = (priority_queue *)malloc(sizeof(priority_queue));
    q->data = (int *)malloc(sizeof(int) * (n  + 1));
    q->cnt = 0;
    q->size = n;
    return q;
}

int empty(priority_queue *q) {
    return q->cnt == 0;
}

int top(priority_queue *q) {
    return q->data[1];
}

void downdate(priority_queue *q, int ind, int n) {
    while ((ind << 1) <= n) {
        int max = ind, l = ind << 1, r = ind << 1 | 1;
        if (l <= n && q->data[l] < q->data[max]) max = l;
        if (r <= n && q->data[r] < q->data[max]) max = r;
        if (max == ind) break;
        swap(q->data[ind], q->data[max]);
        ind = max;
    }
    return ;
}

void downdate1(int *arr, int ind, int n) {
    while ((ind << 1) <= n) {
        int max = ind, l = ind << 1, r = ind << 1 | 1;
        if (l <= n && arr[l] < arr[max]) max = l;
        if (r <= n && arr[r] < arr[max]) max = r;
        if (max == ind) break;
        swap(arr[ind], arr[max]);
        ind = max;
    }
    return ;
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
    while (ind >> 1 && q->data[ind] < q->data[ind >> 1]) {
        swap(q->data[ind], q->data[ind >> 1]);
        ind >>= 1;
    }
    return 1;
}

int pop(priority_queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0;
    q->data[1] = q->data[q->cnt--];
    downdate(q, 1, q->cnt);
    return 1;
}

void output(priority_queue *q) {
    for (int i = 1; i <= q->cnt; i++) {
        i - 1 && printf(" ");
        printf("%d", q->data[i]);
    }
    printf("\n");
}

void output1(int *arr, priority_queue *q) {
    for (int i = 1; i <= q->cnt; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void clear(priority_queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

void heap_sort(priority_queue *q, int *arr) {  
    for (int i = q->cnt; i > 1; i--) {
        swap(arr[i], arr[1]);
        downdate1(arr, 1, i - 1);
    }
    return ;
}

int main () {
    int val;
    srand(time(0));
    #define max_op 20
    priority_queue *q = init(max_op);
    int *arr = (int *)malloc((max_op + 1) * sizeof(int));
    for (int i = 0; i < 30; i++) {
        //scanf("%d", &val);
        int val = rand() % 100 - 50;
        int op = rand() % 10;
        if (op != 1) {
            int flag = push(q, val);
            printf("insert %d to the queue is %s\n", val, flag ? "success" : "failed");
        }
        if (op == 1) {
            int a = top(q);
            int flag =  pop(q);
            printf("pop %d from queue is %s\n", a, flag ? "success" : "failed");
        }
        printf("no sort queue : ");
        output(q);
        arr = (int *)calloc((q->cnt + 1), sizeof(int));
        for (int i = 1; i <= q->cnt; i++) {
            arr[i] = q->data[i]; 
        }
        printf("sort queue : ");
        heap_sort(q, arr);
        output1(arr, q);
        int k = rand() % q->cnt;
        printf("%dth large is %d\n", k, arr[k]);
        printf("\n");
    }
    clear(q);
    return 0;
}

