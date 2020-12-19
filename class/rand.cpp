/*************************************************************************
	> File Name: rand.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年12月19日 星期六 10时52分38秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
 
int main() {
    srand(time(0));
    int op , val;
    #define MAX_OP 20
    for (int i = 0; i < MAX_OP; i++) {
        switch(rand() % 5) {
            case 0:printf("0 %d\n", rand() % 15); break;
            case 1:
            case 2:
            case 3:printf("1 %d\n", rand() % 15);break;
            case 4:printf("2 %d\n", rand() % 15);break;
        }
    }
    return 0;
}
