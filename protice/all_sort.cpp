/*************************************************************************
> File Name: all_sort.cpp
> Author: zhouyuan
> Mail: 3294207721@qq.com 
> Created Time: 2021年01月08日 星期五 21时27分30秒
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define swap(a, b) {\
                    __typeof(a) __temp = a;\
                    (a) = (b), (b) = __temp;\
                   }

void insert_sort(int *nums, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; i > 0; j--) {
            if (nums[j] < nums[j - 1]) {
                swap(nums[j],  nums[j - 1]);
            }
        }
    }
    return ;
}

void buble_sort(int *nums, int n) {
    int times = 1;
    for (int i = n - 1; i > 0 && times; i--) {
        times = 0;
        for (int j = 0; j < i; j++) {
            if (nums[j] <= nums[j + 1]) continue;
            swap(nums[j], nums[j + 1]);
            times = 1;
        }
    }
}


int main() {


    return 0;
}
