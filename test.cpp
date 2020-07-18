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

int main() {
    int i = 0, n = 1;
    int *num = (int *)malloc(n * sizeof(int));
    char str[15];
    do {
        scanf("%d", num + i);
        num = (int *)realloc(num, (++n) * sizeof(int));
    } while(getchar() != '\n');
    for (int i = 0; i < n - 1; i++) {
        printf("%d ", num[i]);
    }
    printf("\n");
    /*for (int i = 0; i < 5; i++) {
        sprintf(str + i, "%d", num[i]);
        printf("%c", str[i]);
    }*/
    return 0;
}
