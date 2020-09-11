/*************************************************************************
	> File Name: 13.insert_sort_protice1.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年09月11日 星期五 14时55分03秒
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

void insert_sort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        for(int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
            swap(arr[j], arr[j - 1]);
        }
    }
}

void output(int *arr, int n) {
    printf("arr[%d] : [", n);
    for (int i = 0; i < n; i++) {
        i && printf(" ");
        printf("%d", arr[i]);
    }
    printf("]\n");
}

int main() {
    srand(time(0));
    #define max_op 20
    int *arr = (int *)malloc(sizeof(int) * max_op);
    for (int i = 0; i < max_op; i++) {
        arr[i] = rand() % 100;
    }
    output(arr, max_op);
    insert_sort(arr, max_op);
    output(arr, max_op);
    #undef max_op
    return 0;
}
