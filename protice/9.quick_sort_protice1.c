/*************************************************************************
	> File Name: 9.quick_sort_protice1.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年09月11日 星期五 15时52分53秒
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

void quick_sort(int *arr, int l, int r) {
    while(l < r) {
        int x = l, y = r, z = arr[(l + r) >> 1];
        do { 
            while (x <= y && arr[x] < z) x++;
            while (x <= y && arr[y] > z) y--;
            if (x <= y) {
                swap(arr[x], arr[y]);
                x++, y--;
            }
        }while(x <= y);
        quick_sort(arr, x, r);
        r = y;
    }
    return ;
}

void output(int *arr, int n) {
    printf("arr[%d] : [", n);
    for (int i = 0; i < n; i++) {
        i && printf(" ");
        printf("%d", arr[i]);
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
    quick_sort(arr, 0, max_op - 1);
    output(arr, max_op);
    free(arr);
    #undef max_op
    return 0;
}
