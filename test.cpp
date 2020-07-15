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
    int num[15];
    char str[15];
    for (int i = 0; i < 5; i++) {
        scanf("%d", num + i);
    }
    for (int i = 0; i < 5; i++) {
        printf("%d ", num[i]);
    }
    printf("\n");
    for (int i = 0; i < 5; i++) {
        sprintf(str + i, "%d", num[i]);
        printf("%c", str[i]);
    }
    return 0;
}
