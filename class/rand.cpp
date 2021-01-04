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
    int arr[26], sum = 0;
    for (int i = 0; i < 26; i++) {
        arr[i] = rand() % 1000;
        sum += arr[i];
    }
    cout << 26 << endl;
    for (int i = 0; i < 26; i++) {
        printf("%c %lf\n", i + 'A', 1.0 * arr[i] / sum);
    }
    return 0;
}
