/*************************************************************************
	> File Name: 15.select_sort_protice1.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年09月11日 星期五 15时33分08秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>

#define swap(a, b){\
    __typeof(a) __tmp = (a);\
    (a) = (b), (b) = __tmp;\
}

void select_sort(int *arr, int n) {
    for (int i = 0;  i < n - 1; i++) {
        int ind = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[ind]) ind = j;
        }
        swap(arr[ind], arr[i]);
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
    select_sort(arr, max_op);
    output(arr, max_op);
    free(arr);
    #undef max_op
    return 0;
}
