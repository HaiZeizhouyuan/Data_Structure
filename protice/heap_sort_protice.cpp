/*************************************************************************
	> File Name: heap_sort_protice.cpp
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

void downdate(int *arr, int ind, int n) {
    while ( (ind << 1) <= n ) {
        int temp = ind, l = ind << 1, r = ind << 1 | 1;
        if (l <= n && arr[l] > arr[temp]) temp = l;
        if (r <= n && arr[r] > arr[temp]) temp = r;
        if (temp == ind) break;
        swap(arr[ind], arr[temp]);
        ind = temp;
    }
    return ;
}


void heap_sort(int *arr, int n) {
    arr -= 1;
    for (int i = n >> 1; i >= 1; i--) downdate(arr, i, n);
    for (int i = n; i > 1; i--) {
        swap(arr[i], arr[1]);
        downdate(arr, 1, i - 1);
    }
    return ;
}

void output(int *arr, int n) {
    printf("heap : [");
    for (int i = 0; i < n; i++) {
        i && printf(",");
        printf("%d", arr[i]);
    }
    printf("]\n");
}

int main () {
    srand(time(0));
    #define max_op 20
    int *arr = (int *)malloc(sizeof(int) * max_op);
    for (int i = 0; i < max_op; i++) {
        arr[i] = rand () % 100;
    }
    output(arr, max_op);
    heap_sort(arr, max_op);
    output(arr, max_op);
    free(arr);
    return 0;
}

