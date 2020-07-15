/*************************************************************************
	> File Name: diguishanchu.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun Jul 12 21:15:17 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main (){
    char str[35], ch;
    int ind = 0;
    while (scanf("%c", &ch)) {
        if (ch == '\n') break;
        str[ind++] = ch;
    }
    return 0;
}
