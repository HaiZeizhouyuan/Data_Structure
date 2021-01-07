/*************************************************************************
	> File Name: 11.heap_protice5.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月07日 星期四 20时58分44秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>

#define swap(a, b) {\
    typeof(a) __temp = (a);\
    (a) = (b), (b) = __temp;\
}

void downUpdate(int *arr, int ind, int n) {
    while((ind << 1) <= n) {
        int temp = ind, l = ind << 1, r = ind << 1 | 1;
        if (l <= n && arr[l] > arr[temp]) temp = l;
        if (r <= n && arr[r] > arr[temp]) temp = r;
        if (temp == ind) break;
        swap(arr[temp], arr[ind]);
        ind = temp;
    }
    return ;
}

void heap_sort(int *arr, int n) {
    arr -= 1;
    for (int i = n >> 1; i >= 1; i--) {
        downUpdate(arr, i, n);
    }

    for (int i = n; i > 1; i--) {
        swap(arr[i], arr[1]);
        downUpdate(arr, 1, i - 1);
    }
    return ;
}


int main() {
 
    return 0;
}
