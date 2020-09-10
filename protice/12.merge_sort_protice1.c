/*************************************************************************
	> File Name: 12.merge_sort_protice1.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年09月10日 星期四 11时45分36秒
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

void merge_sort(int *data, int l, int r) {
    if (r - l <= 1) {
        if (r - l == 1 && data[l] > data[r]) {
            swap(data[l], data[r]);
        }
        return ;
    }
    int mid = (l + r) >> 1;
    merge_sort(data, l,  mid);
    merge_sort(data, mid + 1, r);
    int *tmp = (int *)malloc(sizeof(int) * (r - l + 1));
    int x = l, y = mid + 1, loc = 0;
    while(x <= mid || y <= r) {
        if (y > r || (x <= mid &&  data[x] <= data[y])) {
            tmp[loc++] = data[x++];
        } else {
            tmp[loc++] = data[y++];
        }
    }
    memcpy(data + l, tmp, sizeof(int) * (r - l + 1));
    free(tmp);
    return ;
}

void output(int *arr, int n) {
    printf("arr[%d] : [", n);
    for (int i = 0; i < n; i++){
        i && printf(" ");
        printf("%d",arr[i]);
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
    merge_sort(arr, 0, max_op - 1);
    output(arr, max_op);
    free(arr);
    #undef max_op
    return 0;
}
