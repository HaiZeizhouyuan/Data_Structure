/*************************************************************************
	> File Name: 报数游戏.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue Jul  7 10:45:37 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b, b = __temp;\
}

void quick_sort(int *data, int l, int r) {
    while (l < r) {
        int x = l, y = r, z = data[(l + r) >> 1];
        do {
            while (x <= y && data[x] < z) x++;
            while (x <= y && data[y] > z) y--;
            if (x <= y){
                swap(data[x], data[y]);
                x += 1, y -= 1;
            }
        } while(x <= y);
        quick_sort(data, x, r);
        r = y;
    }
    return ;
}

int search(int *data, int n, int value) {
    int l = 0, r = n -1, mid;
    while (l < r) {
        mid = (r + l + 1) >> 1;
        if (data[mid] == value) return mid;
        else if (data[mid] < value) l = mid; 
        else r = mid - 1;
    }
    return l;
}

int main () {
    int n, m, temp;
    scanf("%d %d", &n, &m);
    int *data = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) scanf("%d", data + i);
    quick_sort(data, 0, n - 1);
    while (m--) {
        scanf("%d", &temp);
        if (temp <= data[0]) printf("%d", data[0]);           
        else printf("%d", data[search(data, n, temp)]);
        m && printf(" ");
    }
    printf("\n");
    free(data);
    return 0;
}
