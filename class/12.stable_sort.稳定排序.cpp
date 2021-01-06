/*************************************************************************
	> File Name: sort.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun Jul  5 10:13:42 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b), (b) = __temp;\
}

#define TEST(arr, n, func, args...) {\
    int *data = (int *)malloc(sizeof(int) * n);\
    memcpy(data, arr, sizeof(int) * n);\
    output(data, n);\
    printf("%s = ", #func);\
    func(args);\
    output(data, n);\
    free(data);\
}

//归并排序
void merge_sort(int *data, int l, int r) {
    if(r - l <= 1) {
        if (r - l == 1 && data[l] > data[r]) {
            swap(data[l], data[r]);
        }
        return ;
    }
    int mid = (l + r) >> 1;
    merge_sort(data, l, mid);
    merge_sort(data, mid + 1, r);
    int *temp = (int *)malloc(sizeof(int) * (r - l + 1));
    int x = l, y = mid + 1, loc = 0;
    while (x <= mid || y <= r) {
        if (x <= mid && (y > r || data[x] <= data[y])) {
            temp[loc++] = data[x++];
        } else {
            temp[loc++] = data[y++];
        }
    }
    memcpy(data + l, temp, sizeof(int) * (r - l + 1));
    free(temp);
}

// 插入排序
void insert_sort(int *data, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && (data[j] < data[j - 1]); j--) {
            swap(data[j], data[j - 1]);
        }
    }
    return ;
}
//冒泡排序
void bubble_sort (int *data, int n) {
    int times = 1;
    for (int i = n - 1; i >= 1 && times; i--) {
        int times = 0;
        for (int j = 0; j < i; j++) {
            if (data[j] <= data[j + 1]) continue;
            swap(data[j], data[j + 1]);
            times += 1;
        }
    }
    return ;
}

void randint(int *data, int n){
    for (int i = 0; i < n; i++) {
        int val = rand() % 100;
        data[i] = val;
    }
    return ;
}

void output(int *data, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        i && printf(" ");
        printf("%d", data[i]);
    }
    printf("]\n");
}

int main() {
    srand(time(0));
    #define max_op 20
    int arr[max_op];
    randint(arr, max_op);
   //insert_sort(data, max_op);
    TEST(arr, max_op, insert_sort, data, max_op);
    TEST(arr, max_op, bubble_sort, data, max_op);
    TEST(arr, max_op, merge_sort, data, 0, max_op - 1);
    #undef max_op
    return 0;
}
