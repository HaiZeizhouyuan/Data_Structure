/*************************************************************************
	> File Name: 21.all_sort2.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年11月27日 星期五 12时45分33秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;

//快排
int res = 0;
void quick_sort(vector<int> &num, int l, int r, int k) {
    if (l >= r) return ;
    int x = l, y = r, z = num[l];
    while (x < y) {
        while (x < y && num[y] >= z) y--;
        if (x < y) {
            num.insert(num.begin() + x, num[y]);
            x++;
        }
        while (x < y && num[x] <= z ) x++;
        if (x < y) {
            num.insert(num.begin() + y, num[x]); 
            y--;
        }
    }
    num.erase(num.begin() + x);
    num.insert(num.begin() + x, z);
    quick_sort(num, l, x - 1, k);
    quick_sort(num, x + 1, r, k);
    return ;
}

int main() {
    int k;
    cin >> k;
    srand(time(0));
    vector<int> num;
    for (int i = 0; i < 10; i++) {
        int x;
        cin >> x;
        num.push_back(x);;
    }

    for (int i = 0;  i < 10; i++) {
        cout << num[i] << " ";
    }
    cout << endl;
    quick_sort(num, 0, 9, k);
    for (auto i : num) {
        cout << i << " ";
    }
    cout << endl;
    cout << num[10 - k] << endl;

 
    return 0;
}
