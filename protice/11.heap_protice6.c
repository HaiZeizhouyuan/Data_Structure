/*************************************************************************
	> File Name: 11.heap_protice6.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月07日 星期四 21时10分38秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#define swap(a, b){\
    __typeof(a) __temp = (a);\
    (a) = (b), (b) = __temp;\
}

void downUpdate(int *nums, int ind, int n) {
    while((ind << 1) <= n) {
        int temp = ind, l = ind << 1, r = ind << 1 | 1;
        if (l <= n && nums[l] > nums[temp]) temp = l;
        if (r <= n && nums[r] > nums[temp]) temp = r;
        if (temp == ind) continue;
        swap(nums[temp], nums[ind]);
        ind = temp;
    }
}

void heap_sort(int *nums, int n) {
    nums -= 1;
    for (int i = n >> 1; i >= 1; i--) {
        downUpdate(nums, i, n);
    }
    for (int i = n; i > 1; i--) {
        swap(nums[i], nums[1]);
        downUpdate(nums, 1, i - 1);
    }
    return ;

}

int main() {
 
    return 0;
}
