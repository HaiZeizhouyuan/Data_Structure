/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat Jun 27 11:42:19 2020
 ************************************************************************/

/*************************************************************************
	> File Name: 2.list.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun Jun  7 18:57:04 2020
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int num[10][10];
int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d ", &num[i][j]);
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", num[i][j]);
        }
        printf("\n");
    }
    return 0;
}
