/*************************************************************************
	> File Name: 两数之和.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun Jul  5 14:09:26 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main () {
    int n, m, temp;
    scanf("%d", &n);
    int *a = (int *)malloc(sizeof(int) * (n + 1));
    int *b = (int *)calloc(1005, sizeof(int));
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        b[a[i]] = i;
    }
    scanf("%d", &m);
    for (int i = 1; i <= n; i++) {
        if (a[i] <= m && b[m - a[i]]) {
            printf("%d %d\n", i, b[m - a[i]]);
            break;
        }
    }
    free(a);
    free(b);
    return 0;
}
