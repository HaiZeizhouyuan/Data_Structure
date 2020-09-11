/*************************************************************************
	> File Name: 14.bublle_sort_protice1.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年09月11日 星期五 15时06分22秒
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

void bubble_sort(int *arr, int n) {
    int time = 1;
    for (int i = 1; i < n && time; i++ ) {
        time = 0;
        for (int j = 0; j < n - i; j++) {
            if (arr[j] <= arr[j + 1]) continue;
            swap(arr[j], arr[j + 1]);
            time = 1;
        }
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
    bubble_sort(arr, max_op);
    output(arr, max_op);
    free(arr);
    #undef max_op
    return 0;
}
