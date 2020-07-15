/*************************************************************************
	> File Name: 第一个没有出现的正数.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue Jul  7 16:09:12 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, temp;
    scanf("%d", &n);
    int *data = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &temp);
        if (temp > 0) data[temp] = 1; 
    }
    temp = n + 1;
    for (int i = 1; i <= n; i++) {
        if (!data[i]) {
            temp = i;
            break;
        }
    }
    printf("%d\n", temp);
    free(data);
    return 0;
}
