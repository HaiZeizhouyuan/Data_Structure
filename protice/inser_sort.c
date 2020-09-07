/*************************************************************************
	> File Name: inser_sort.c
	> Author: zhouyuan
	> Mail: 
	> Created Time: 2020年09月07日 星期一 10时46分29秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>


#define swap(a, b){\
    __typeof(a) __tmp = (a);\
    (a) = (b), (b) = __tmp;\
}

//单增
void merge_sort(int *data, int l, int r) {
    if (l - r <= 1) {
        if (r - l == 1 && data[l] > data[r]) {
            swap(data[l], data[r]);
        }
        return ;
    }

    int mid = (l + r) >> 1;
    merge_sort(data, l, mid);
    
}

int main() {
 
    return 0;
}
