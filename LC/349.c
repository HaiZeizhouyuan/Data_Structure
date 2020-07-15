/*************************************************************************
	> File Name: 349.c
	> Author: 
	> Mail: 
	> Created Time: Wed Jul 15 10:29:41 2020
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#define max_n 100
#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b), (b) = __temp;\
}

void sort_num(int *nums, int numsSize) {
    for (int i = 1; i < numsSize; i++) {
        for (int j = i; j > 0 && (nums[j] < nums[j - 1]); j--) {
            swap(nums[j], nums[j - 1]);
        }
    }
    return ;
}
int main () {
    int nums1[max_n + 5], nums2[max_n + 5];
    int nums1Size = 0, nums2Size = 0;
    for (int i = 0; i < 4; i++) {
        scanf("%d", nums1 + i);
        nums1Size += 1;
    }
    for (int i = 0; i < 5; i++) {
        scanf("%d", nums2 + i);
        nums2Size += 1;
    }
    printf("%d %d\n", nums1Size, nums2Size);
    sort_num(nums1, nums1Size);
    sort_num(nums2, nums2Size);
    for (int i = 0; i < nums1Size; i++) {
        printf("%d ", nums1[i]);
    }
    printf("\n");
    return 0;
}
