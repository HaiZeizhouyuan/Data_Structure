/*************************************************************************
	> File Name: 11.heap_sort_protice5.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月08日 星期五 21时17分19秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define swap(a, b){\
    __typeof(a) __temp = (a);\
    (a) = (b), (b) = __temp;\
}

void update(int *nums, int ind, int n) {
    while((ind << 1) <= n) {
        int temp = ind, l = ind << 1, r = ind << 1 | 1;
        if (l <= n && nums[l] > nums[temp]) temp = l;
        if (r <= n && nums[r] > nums[temp]) temp = r;
        if (temp == ind) break;
        swap(nums[ind], nums[temp]);
        ind = temp;
    }
}


void heap_sort(int *nums, int n) {
    nums -= 1;
    for (int i = n >> 1; i >= 1; i--) {
        update(nums, i, n);
    }
    for (int i = n; i > 1; i--) {
        swap(nums[i], nums[1]);
        update(nums, 1, i - 1);
    }
    return ;
}

int main() {
 
 
    return 0;
}
