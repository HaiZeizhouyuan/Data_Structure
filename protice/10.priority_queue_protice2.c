/*************************************************************************
	> File Name: 10.priority_queue_protice2.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年09月09日 星期三 15时41分25秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
//#include<time.h>
#include<unistd.h>
 
#define swap(a,b){\
    __typeof(a) __tmp = (a);\
    (a) = (b), (b) = __tmp;\
}

typedef struct priority_queue{
    int *data;
    int size, cnt;
}priority_queue;

priority_queue *init(int n) {
    priority_queue *q = (priority_queue *)malloc(sizeof(priority_queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->cnt = 0;
    q->size = n;
    return q;
}

int push(priority_queue *q,int val) {
    if (q == NULL) return 0;
    if (q->cnt > q->size) return 0;
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

int top(priority_queue *q) {
    return q->data[1];
}

void updata(priority_queue *q, int ind) {
    while(ind << 1 <= q->cnt) {
        int max = ind, l = ind << 1, r = ind << 1 | 1;
        if (l < q->cnt && q->data[l] > q->data[max]) max = l;
        if (r < q->cnt && q->data[r] > q->data[max]) max = r;
        if (max == ind) break;
        swap(q->data[max], q->data[ind]);
        ind = max;
    }
    return ;
}

int pop(priority_queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0;
    q->data[1] = q->data[q->cnt--];
    updata(q, 1);
    return 1;
}
#include<time.h>
void clear(priority_queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

int main() {
    srand(time(0));
    #define max_op 20
    priority_queue *q = init(max_op);
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        push(q, val);
        printf("insert %d to priority_queue!\n", val);
    }

    for (int i = 0; i < max_op; i++) {
        printf("%d ", top(q));
        pop(q);
    }
    printf("\n");
    clear(q);
    #undef max_op
    return 0;
}
