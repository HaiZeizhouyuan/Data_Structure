/*************************************************************************
	> File Name: 11.heap_sort_protice1.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年09月09日 星期三 19时04分31秒
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

void downUpdata(int *arr, int ind, int n) {
    while((ind << 1) <= n) {
        int tmp = ind, l = ind << 1, r = ind << 1 | 1;
        if (l <= n && arr[l] > arr[tmp]) tmp = l;
        if (r <= n && arr[r] > arr[tmp]) tmp = r;
        if (tmp == ind) break;
        swap(arr[tmp], arr[ind]);
        ind = tmp;
    }
    return ;
}

void heap_sort(int *arr, int n) {
    arr -= 1;
    for (int i = n >> 1; i >= 1; i--) {
        downUpdata(arr, i, n);
    }
    for (int i = n; i > 1; i--) {
        swap(arr[i], arr[1]);
        downUpdata(arr, 1, i - 1);
    }
    return ;
}

void output(int *arr, int n) {
    printf("arr(%d) = [", n);
    for (int i = 0; i < n; i++) {
        printf(" %d", arr[i]);
    }
    printf("]\n");
    return ;
}


int main() {
    srand(time(0));
    #define max_op 20
    int *arr = (int *)malloc(sizeof(int) * max_op);
    for (int i = 0; i < max_op; i++) {
        arr[i] = rand() % 100;
    }

    output(arr, max_op);
    heap_sort(arr, max_op);
    output(arr, max_op);
    free(arr);
    return 0;
}
