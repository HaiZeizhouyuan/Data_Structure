/*************************************************************************
	> File Name: 2.字符串统计.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月23日 星期六 16时33分20秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
 
#define BASE 26
#define MAX_N 20000
struct Node {
    int flag;
    int next[26], fail;
} tree[MAX_N * BASE + 5];
int root = 0, cnt = 1;
char str[100005];


int getNewNode() { return cnt++; }
void insert(const char *str) {
    int p = root;
    for (int i = 0; str[i]; i++){
        int ind = str[i] - 'a';
        if (tree[p].next[ind] = 0) tree[p].next[ind] = getNewNode();
        p = tree[p].next[ind];
    }
    tree[p].flag = 1;
    return ;
}



int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%s", str);
        insert(str);
    }
    scanf("%s", str);

 
 
    return 0;
}
