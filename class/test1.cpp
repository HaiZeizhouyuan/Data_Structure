/*************************************************************************
	> File Name: test1.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年09月11日 星期五 17时24分04秒
 ************************************************************************/

#include<iostream>
#include<algorithm>
#include<string>
#include "a.test"
using namespace std;
 
int main() {
    sort(str, str+ 5);
    for (int i = 0; i < 5; i++) {
        cout << str[i] << endl;
    }
    return 0;
}
