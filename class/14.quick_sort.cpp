/*************************************************************************
	> File Name: 14.quick_sort.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun Jul  5 18:12:38 2020
 ************************************************************************/

#include<stdio.h>
#define max_n 20

#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b, b = __temp;\
}

void quick_sort(int *num, int l, int r) {
    while (l < r) {
        int x = l, y = r, z = num[(l + r) >> 1];
        do {
            while (x <= y && num[x] < z) x++;
            while (x <= y && num[y] > z) y--;
            if (x <= y) {
                swap(num[x], num[y]);
                x++, y--;
            }
        } while(x <= y);
        quick_sort(num, x, r);
        r = y;
    }
    return ;
}

int arr[max_n];

void init_arr(int *num, int n) {
    for (int i = 0; i < n; i++) arr[i] = n - i;
    return ;
}

void output(int *num, int  n) {
    for (int i = 0; i < n; i++){
        printf("%d ", num[i]);
    }
    return ;
}

int main () {
    init_arr(arr, max_n);
    quick_sort(arr, 0, max_n - 1);
    output(arr, max_n);
    return 0;
}
