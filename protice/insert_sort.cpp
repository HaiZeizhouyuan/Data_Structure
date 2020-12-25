/*************************************************************************
> File Name: insert_sort.cpp
> Author: zhouyuan
> Mail: 3294207721@qq.com 
> Created Time: 2020年12月25日 星期五 16时17分51秒
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
//
void insert_sort(int *nums, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && nums[j - 1] > nums[j]; j--) {
            swap(nums[j - 1], nums[j]);
        }
    }
    return ;
}

void bubble_sort(int *nums, int n) {
    for (int i = 1; i < n; i++) {
        int times = 0;
        for (int j = 0; j < n - i; j++) {
            if (nums[j] > nums[j + 1]) {
                swap(nums[j], nums[j + 1]);
                times = 1;
            }
        }
        if (times == 0) break;
    }
    return ;
}

void merge_sort(int *nums, int l, int r) {
    if (r - l <= 1) {
        if ((r - l == 1) && (nums[l] > nums[r])) {
            swap(nums[l], nums[r]);
        }
        return ;
    }

    int mid = (l + r) >> 1;
    merge_sort(nums, l, mid);
    merge_sort(nums, mid + 1, r);
    int *temp = (int *)malloc(sizeof(int) * (l - r + 1));
    int x = l, y = mid + 1, loc = 0;
    while(x <= mid && y <= r) {
        if ((x <= mid) && (y > r || nums[x] <= nums[y])) {
            temp[loc++] = nums[x++];
        } else {
            temp[loc++] = nums[y++];
        }
    }
    memcpy(nums + l, temp, sizeof(int) * (r - l + 1));
    free(temp);
    return ;
}

void select_sort(int *nums, int n) {
    for (int i = 0; i < n - 1; i++) {
        int ind  = i;
        for (int j = i + 1; j < n; j++) {
            if (nums[j] < nums[ind]) ind = j;
        }
        swap(nums[ind], nums[i]);
    }
    return ;
}

void quick_sort(int *nums, int l, int r) {
    while(l <= r) {
        int x = l, y = r, z = nums[(l + r) >> 1];
        do {
            while(x <= y && nums[x] < z) x++;
            while(x <= y && nums[y] > z) y--;
            if(x <= y) {
                swap(nums[x], nums[y]);
                x++, y--;
            }
        } while(x <= y);
        quick_sort(nums, x, r);
        r = y;
    }
    return ;
}

int main() {


    return 0;
}
