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
#define ope(a, sr, b) (a) sr (b) 

int main() {
    int a = 1, b = 2;
    char sr = '*';
    int c = ope(a,sr,b);
    printf("%d\n", c);
    return 0;
}