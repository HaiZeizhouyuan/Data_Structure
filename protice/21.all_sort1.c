/*************************************************************************
	> File Name: 21.all_sort1.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年09月12日 星期六 10时42分21秒
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

int ans = 0;

#define test(arr, n, func, args...){\
    int *nums = (int *)malloc(sizeof(int) * n);\
    memcpy(nums, arr, sizeof(int) * n);\
    printf("arr[%d] : ", n);\
    output(nums, n);\
    printf("%d %s", ++ans, #func );\
    func(args);\
    output(nums, n);\
    free(nums);\
}

void insert_sort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
            swap(arr[j - 1], arr[j]);
        }
    }
    return ;
}

void bubble_sort(int *arr, int n) {
    int times = 1;
    for (int i = 1; i < n && times; i++) {
        times = 0;
        for (int j = 0; j < n - i; j++) {
            if(arr[j] <= arr[j + 1]) continue;
            swap(arr[j], arr[j + 1]);
            times = 1;
        }
    }
    return ;
}

void merge_sort(int *arr, int l, int r) {
    if (r - l <= 1) {
        if (r - l == 1 && arr[l] > arr[r]) {
            swap(arr[l], arr[r]);
        }
        return ;
    }
    int mid = (r + l) >> 1;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);
    int *tmp = (int *)malloc(sizeof(int) * (r - l + 1));
    int x = l, y = mid + 1, loc = 0;
    while(x <= mid || y <= r) {
        if (x <= mid && (y > r || arr[x] <= arr[y])) tmp[loc++] = arr[x++];
        else tmp[loc++] = arr[y++];
    }
    memcpy(arr + l, tmp, sizeof(int) * (r - l + 1));
    free(tmp);
    return ;
}

void select_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int ind = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[ind]) ind = j;
        }
        swap(arr[ind] , arr[i]);
    }
    return ;
}

void quick_sort(int *arr, int l, int r) {
    while(l < r) {
        int x = l, y = r, z = arr[(l + r) >> 1];
        do {
            while(x <= y && arr[x] < z) x++;
            while(x <= y && arr[y] > z) y--;
            if (x <= y) {
                swap(arr[x], arr[y]);
                x++, y--;
            }
        } while(x <= y);
        quick_sort(arr, x, r);
        r = y;
    }
    return ;
}

void updata(int *arr, int ind, int n) {
    while((ind << 1) <= n) {
        int tmp = ind, l = ind << 1, r = ind << 1 | 1;
        if (l <= n && arr[l] > arr[tmp]) tmp = l;
        if (r <= n && arr[r] > arr[tmp]) tmp = r;
        if (tmp == ind) break;
        swap(arr[tmp], arr[ind]);
        ind = tmp;
    }
    return ;
}

void heap_sort(int *arr, int n) {
    arr -= 1;
    for (int i = n >> 1; i > 0; i--) {
        updata(arr, i, n);
    }
    for (int i = n; i > 1; i--) {
        swap(arr[1], arr[i]);
        updata(arr, 1, i - 1);
    }
    return ;

}

void output(int *arr, int n) {
    printf("[");
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
    for (int i = 0; i < max_op; i++) arr[i] = rand() % 100;
    test(arr, max_op, insert_sort, nums, max_op);
    test(arr, max_op, bubble_sort, nums, max_op);
    test(arr, max_op, merge_sort, nums, 0, max_op - 1);
    test(arr, max_op, select_sort, nums, max_op);
    test(arr, max_op, quick_sort, nums, 0, max_op - 1);
    test(arr, max_op, heap_sort, nums, max_op);
    free(arr);
    #undef max_op
    return 0;
}
