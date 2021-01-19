/*************************************************************************
	> File Name: 20.all_sort.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年12月25日 星期五 16时13分23秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;

#define swap(a, b){\
    __typeof(a) __temp = (a);\
    (a) = (b), (b) = __temp;\
}

int insert_sort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
            swap(arr[j - 1], arr[j]);
        }
    }
}


void bubble_sort(int *nums, int n) {
    int times = 1;
    for (int i = 1; i < n && times; i++) {
        times = 0;
        for (int j = 0; j < n - i; j++) {
            if (nums[j] > nums[j + 1]) {
                swap(nums[j], nums[j + 1]);
                times = 1;
            }
        }
    }
    return ;
}

void merge_sort(int *arr, int l, int r) {
    if (r - l <= 1) {
        if (r - l == 1 && arr[l] > arr[r]) swap(arr[l], arr[r]);
        return ;
    }

    int mid = (l + r) >> 1;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);
    int *temp = (int *)malloc(sizeof(int) * (r - l + 1));
    int x = l, y = mid + 1, loc = 0;
    while(x <= mid && y <= r) {
        if (x <= mid && (y > r || arr[x] <= arr[y])) {
            temp[loc++] = arr[x++];
        } else {
            temp[loc++] = arr[y++];
        }
    }
    memcpy(arr + l, temp, sizeof(int) * (r - l + 1));
    free(temp);
    return ;
}

void select_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int ind = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[ind]) ind = j;
        }
        swap(arr[ind], arr[i])
    }
    return ;
}

void quick_sort(int *arr, int l, int r) {
    while(l <= r) {
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

int main() {
 
 
    return 0;
}
