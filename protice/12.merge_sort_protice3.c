/*************************************************************************
	> File Name: 12.merge_sort_protice3.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年09月11日 星期五 14时29分56秒
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

void merge_sort(int *arr, int l, int r) {
    if (r - l <= 1) {
        if (r - l == 1 && arr[l] > arr[r]) {
            swap(arr[l], arr[r]);
        }
        return ;
    }
    int mid = (l + r) >> 1;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);
    int *tmp = (int *)malloc(sizeof(int) * (r - l + 1));
    int x = l, y = mid + 1, loc = 0;
    while (x <= mid || y <= r) {
        if (x <= mid && (y > r || arr[x] <= arr[y])) {
            tmp[loc++] = arr[x++];
        } else {
            tmp[loc++] = arr[y++];
        }
    }
    memcpy(arr + l, tmp, sizeof(int) * (r - l + 1));
    free(tmp);
    return ;
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
    merge_sort(arr, 0, max_op - 1);
    output(arr, max_op);
    free(arr);
    #undef max_op
    return 0;
}
