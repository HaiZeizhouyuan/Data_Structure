/*************************************************************************
	> File Name: 15.binary_search.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun Jul  5 19:21:40 2020
 ************************************************************************/

#include<stdio.h>
#define P(func, args...){\
    printf("%s = %d\n", #func, func(args));\
} 


// 1 3 5 7 9 10

int bineary_search(int *num, int n, int x) {
    int head = 0,  tail = n - 1, mid;
    while (head <= tail) {
        mid = (head +tail) >> 1;
        if (num[mid] == x) return mid;
        if( num[mid] < x) head = mid + 1;
        else tail = mid -1;
    }
    return -1;
}

// 111111111110000000
//

int search_last1(int *num, int n) {
    int head = -1, tail = n - 1, mid;
    while (head < tail) {
        mid = (head + tail + 1) >> 1;
        if (num[mid] == 1) head = mid;
        else tail = mid - 1;
    }
    return head;
}

// 0000000000111111111


int search_first1(int *num, int n) {
    int head =  0, tail = n, mid;
    while (head < tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == 1) tail = mid;
        else head = mid + 1;
    }
    return head == n ? -1 :head;
}



int main(){
    int arr1[10] = {1, 2, 3, 5, 7, 9, 10, 11, 12, 13};
    int arr2[10] = {1, 1, 1, 1, 1, 0, 0, 0 ,0 ,0};
    int arr3[10] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
    P(bineary_search, arr1, 10, 3);
    P(search_last1, arr2, 10);
    P(search_first1, arr3, 10);
    return 0;
}
