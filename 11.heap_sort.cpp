/*************************************************************************
	> File Name: 11.heap_sort.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat Jul  4 18:41:02 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b), (b) = __temp;\
}

void downUpdata(int *arr, int ind, int n) {
    while ((ind << 1) <= n) {
        int temp = ind, l = ind << 1, r = ind << 1 | 1;
        if (r <= n && arr[l] > arr[temp]) temp = l;
        if (r <= n && arr[r] > arr[temp]) temp =r;
        if (temp == ind) break;
        swap(arr[temp], arr[ind]);
        ind = temp;
    }
    return ;
}

void heap_sort(int *arr, int n) {
    arr -= 1;
    for (int i = n >> 1; i >= 1;  i--) {
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

int main () {
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

